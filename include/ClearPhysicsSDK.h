#ifndef ClearPhysicsSDK_H__
#define ClearPhysicsSDK_H__

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#ifdef CLEARPHYSICSSDK_EXPORTS
	#define CLEAR_PHYSICS_API __declspec(dllexport)
#else
	#define CLEAR_PHYSICS_API __declspec(dllimport)
#endif

#pragma warning (disable: 4005)
#pragma warning (disable: 4275)

// STL
#include <string>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <fstream>
#include <iostream>

using namespace std;

// bullet
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactShape.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>
#include <Bullet-C-Api.h>

#pragma comment(lib, "BulletCollision_Debug.lib")
#pragma comment(lib, "BulletDynamics_Debug.lib")
#pragma comment(lib, "LinearMath_Debug.lib")


#include <cgl.h>
#pragma comment(lib, "ClearGraphicsLibrary.lib")

#include <ClearEventManager.h>
#pragma comment(lib, "ClearEventManager.lib")

#include "PhyEvents.h"

#include "DebugDrawer.h"

#include "Constants.h"
#include "MathConversion.h"
#include "NullPhysics.h"
#include "BulletPhysics.h"
#include "PhysicsEventListener.h"

#endif

