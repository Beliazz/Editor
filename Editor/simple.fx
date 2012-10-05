matrix matProj;
matrix matView;
matrix matWorld;


#define MAX_BONES 100

matrix matBonePallet[MAX_BONES];

float4	f4EmmisionColor;
float4	f4AmbientColor;
float4	f4DiffuseColor;
float4	f4SpecularColor;

float   fDiffuseIntensity = 1.0f;
float   fSpecularIntensity = 1.0f;

float	fShininess;
float	fReflectivity;
float	fTransparency;

float3	f3CameraPosition = float3( 0.0f, 10.0f, -10.0f );
float3	f3LightDirection = float3(-0.577f, 0.577f, -0.577f);

Texture2D    txDiffuse;
Texture2D    txSpecular;
Texture2D    txNormalMap;
SamplerState samLinear;


struct PSINPUT
{
	float4 position : SV_POSITION;
	float4 worldPos : POS1;
	float3 normal   : NORMAL0;
	float2 texCoord : TEXCOORD0;
	float4 color    : COLOR1;
	float3 CameraView : CAMERAVIEW0;
};

struct simplePSINPUT
{
	float4 position : SV_POSITION;
};

//--------------------------------------------------------------------------------------
// States
//--------------------------------------------------------------------------------------
DepthStencilState EnableDepth
{
    DepthEnable = TRUE;
    DepthWriteMask = ALL;
    DepthFunc = LESS_EQUAL;
};

DepthStencilState DisableDepth
{
    DepthEnable = FALSE;
    DepthWriteMask = 0;
    DepthFunc = LESS_EQUAL;
};

BlendState DisableBlending
{
    BlendEnable[0] = TRUE;
};

BlendState SrcAlphaBlend
{
   BlendEnable[0]           = TRUE;
   SrcBlend                 = SRC_ALPHA;
   DestBlend                = INV_SRC_ALPHA;
   BlendOp                  = ADD;
   SrcBlendAlpha            = ONE;
   DestBlendAlpha           = ONE;
   BlendOpAlpha             = ADD;
   RenderTargetWriteMask[0] = 0x0F;
};

RasterizerState CullNone
{
    CullMode = NONE;
};

RasterizerState CullBack
{
    CullMode = BACK;
};

RasterizerState CullFront
{
    CullMode = FRONT;
};



//////////////////////////////////////////////////////////////////
//                        VertexShader                          //
//////////////////////////////////////////////////////////////////
PSINPUT simpleVertexShader(float3 position : POSITION0, float2 tex : TEXCOORD0, float4 weights : BONEWEIGHTS0, uint4 boneIndices : BONEINDICES0  )
{
	PSINPUT output = (PSINPUT)0;

	float4x4 skinTransform = 0;
  	skinTransform += matBonePallet[boneIndices.x] * weights.x;
  	skinTransform += matBonePallet[boneIndices.y] * weights.y;
  	skinTransform += matBonePallet[boneIndices.z] * weights.z;
  	skinTransform += matBonePallet[boneIndices.w] * weights.w;
 	skinTransform = mul(skinTransform,matWorld);

	
	float4 worldPosition = mul(float4( position, 1.0f ), skinTransform);
	float4 viewPosition  = mul(worldPosition, matView);
	output.worldPos		 = worldPosition;
	output.position      = mul(viewPosition, matProj);

	output.normal = float3(1.0f,1.0f,1.0f);

	output.CameraView = f3CameraPosition - mul( float4( position, 1.0f ), skinTransform );

	output.texCoord = tex;

	return output;
}

//////////////////////////////////////////////////////////////////
//                        VertexShader                          //
//////////////////////////////////////////////////////////////////
simplePSINPUT simpleVertexShaderPosOnly(float3 position : POSITION0 )
{
	simplePSINPUT output = (simplePSINPUT)0;

	float4 worldPosition = mul(float4( position, 1.0f ), matWorld);
	float4 viewPosition  = mul(worldPosition, matView);
	output.position      = mul(viewPosition, matProj);

	return output;
}


//////////////////////////////////////////////////////////////////
//                        PixelShader                           //
//////////////////////////////////////////////////////////////////
float4 simplePS(simplePSINPUT input) : SV_Target
{
    return float4(0.0f,1.0f,0.0f,1.0f);
}









//////////////////////////////////////////////////////////////////
//                        VertexShader                          //
//////////////////////////////////////////////////////////////////
PSINPUT simpleVertexShader_Static(float3 position : POSITION0, float2 tex : TEXCOORD0 )
{
	PSINPUT output = (PSINPUT)0;

	output.normal = float3(1.0f,1.0f,1.0f);


	float4 worldPosition = mul(float4( position, 1.0f ), matWorld);
	float4 viewPosition  = mul(worldPosition, matView);
	output.position      = mul(viewPosition, matProj);
	output.worldPos		 = worldPosition;

	output.CameraView = f3CameraPosition - mul( float4( position, 1.0f ), matWorld );

	output.texCoord = tex;

	return output;
}

//////////////////////////////////////////////////////////////////
//                        VertexShader                          //
//////////////////////////////////////////////////////////////////
PSINPUT simpleVertexShader_Normals(float3 position : POSITION0, float3 normal : NORMAL0, float2 tex : TEXCOORD0 )
{
	PSINPUT output = (PSINPUT)0;

	output.normal = normalize(mul(normal, matWorld));


	float4 worldPosition = mul(float4( position, 1.0f ), matWorld);
	float4 viewPosition  = mul(worldPosition, matView);
	output.position      = mul(viewPosition, matProj);

	output.CameraView = f3CameraPosition - mul( float4( position, 1.0f ), matWorld );

	output.texCoord = tex;

	return output;
}








//////////////////////////////////////////////////////////////////
//                        PixelShader                           //
//////////////////////////////////////////////////////////////////
float4 simplePixelShader(PSINPUT input) : SV_Target
{
// 	 float4 finalColor = 0;
//     
//     finalColor = saturate( dot( float3(-0.577f, 0.577f, -0.577f),input.normal) * f4AmbientColor );
// 
//     finalColor.a = 1;
//     return finalColor;
    float4 DiffuseColor = (fDiffuseIntensity * f4DiffuseColor)  * saturate(dot(f3LightDirection,input.normal));
	float3 Half = normalize(f3LightDirection + normalize(input.CameraView));

	float specular = pow(saturate(dot(input.normal,Half)),25);


    float4 textureColor = txDiffuse.Sample( samLinear, input.texCoord );
    textureColor.a = 1;
 
    return textureColor;// + saturate((f4AmbientColor + DiffuseColor) + ((f4SpecularColor * fSpecularIntensity) * specular));

}
  











//--------------------------------------------------------------------------------------
// Creates a grid pattern in 3D
// This is a relatively cheap grid technique.  LineWidth determines the width of the grid
// lines.  Hardness controls the hard look or "fuzziness" of the lines.
//--------------------------------------------------------------------------------------
float Grid( float3 WorldPos, float3 LineWidth, float Hardness )
{
    // Assume the world is full of axis aligned planes at integer values
    // Find the 6 planes nearest the World point
    float3 NearPlanes1 = ceil(WorldPos);
    float3 NearPlanes2 = floor(WorldPos);
    
    // Find the distance to each of these planes
    float3 Delta1 = abs(WorldPos - NearPlanes1);
    float3 Delta2 = abs(WorldPos - NearPlanes2);
    
    // Clamp to within the line width of the planes
    float3 Intermediate1 = saturate(LineWidth - Delta1);
    float3 Intermediate2 = saturate(LineWidth - Delta2);
    
    // This is basically squaring the distances to the planes together and summing them all up
    float retval = 0;
    retval += dot( Intermediate1, Intermediate1 );
    retval += dot( Intermediate2, Intermediate2 );

    // Multiplying by hardness will change how much of the value actually goes above 1
    // This effectively changes the hardness look of the lines
    return saturate(retval*Hardness);
}

//--------------------------------------------------------------------------------------
// Creates a grid pattern in 3D where some of the blocks are staggered based on the masks.
// LineWidth determines the width of the grid
// lines.  Hardness controls the hard look or "fuzziness" of the lines.
//--------------------------------------------------------------------------------------
float StaggeredGrid( float3 WorldPos, float3 LineWidth, float Hardness, float3 StaggerOnMask, float3 StaggerByMask )
{
    // Shift some of the coordinates by applying the stagger masks.
    // StaggerOnMask squishes the world position based upon the mask.
    // StaggerByMask moves the position in increments of hole units.
    float3 Test = abs( floor( ( WorldPos * StaggerOnMask ) ) );
    uint3 IntTest = (uint3)Test;
    uint3 Mod2s = IntTest & 1;
    float MaxMod = ( Mod2s.x + Mod2s.y + Mod2s.z );
    WorldPos += float3( 0.5, 0.5, 0.5 ) * MaxMod * StaggerByMask;
        
    // Just call Grid on the shifted coordinates
    return Grid( WorldPos, LineWidth, Hardness );
}







 float4 GridTest( PSINPUT Input ) : SV_TARGET
{
    float3 GridIn = (Input.worldPos) ;
    float GridHard = 500;
    float GridOut = 1 - Grid( GridIn, float3( 0.03, 0.03, 0.03 ), GridHard );
    
	return GridOut.rrrr;
}








//////////////////////////////////////////////////////////////////
//                        Technique                           //
//////////////////////////////////////////////////////////////////
technique11 skinned
{
	pass
	{
		SetVertexShader( CompileShader( vs_4_0, simpleVertexShader() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, simplePixelShader() ) );
	}
}

technique11 normal
{
	pass
	{
		SetVertexShader( CompileShader( vs_4_0, simpleVertexShader_Static() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, simplePixelShader() ) );
	}
}

technique11 simple
{
	pass
	{
		SetVertexShader( CompileShader( vs_4_0, simpleVertexShaderPosOnly() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, simplePS() ) );
	}
}