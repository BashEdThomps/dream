#ifndef PhysicsObjectInstance_h
#define PhysicsObjectInstance_h

#include "../../../AssetInstance.h"
#include <btBulletDynamicsCommon.h>

#define COLLISION_SHAPE_SPHERE                   "btShpereShape"
#define COLLISION_SHAPE_BOX                      "btBoxShape"
#define COLLISION_SHAPE_CYLINDER                 "btCylinderShape"
#define COLLISION_SHAPE_CAPSULE                  "btCapsuleShape"
#define COLLISION_SHAPE_CONE                     "btConeShape"
#define COLLISION_SHAPE_MULTI_SPHERE             "btMultiSphereShape"
#define COLLISION_SHAPE_CONVEX_HULL              "btConvexHullShape"
#define COLLISION_SHAPE_CONVEX_TRIANGLE_MESH     "btConvexTriangleMeshShape"
#define COLLISION_SHAPE_CONVEX_BVH_TRIANGLE_MESH "btBvhTriangleMeshShape"
#define COLLISION_SHAPE_HEIGHTFIELD_TERRAIN      "btHeightfieldTerrainShape"
#define COLLISION_SHAPE_STATIC_PLANE             "btStaticPlaneShape"
#define COLLISION_SHAPE_COMPOUND                 "btCompoundShape"

namespace Dream     {
namespace Asset     {
namespace Instances {
namespace Physics   {
namespace Bullet    {
	
	class PhysicsObjectInstance : public Asset::AssetInstance {
	private:
		btCollisionShape                         *mCollisionShape;
		btDefaultMotionState                     *mMotionState;
		btRigidBody                              *mRigidBody;
		btRigidBody::btRigidBodyConstructionInfo *mRigidBodyConstructionInfo;
	public:
		PhysicsObjectInstance(AssetDefinition*);
		~PhysicsObjectInstance();
		bool load(std::string);
		bool createCollisionShape();
		btCollisionShape* getCollisionShape();
		btRigidBody*      getRigidBody();
		void              getWorldTransform(btTransform&);
	}; // End of PhysicsObjectInstance
	
} // End of Bullet
} // End of Physics
} // End of Instances
} // End of Assets
} // End of Dream

#endif /* PhysicsObjectInstance_h */