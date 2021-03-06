/*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <string>
#include <map>
#include <vector>

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>

#include "Components/DiscreteAssetRuntime.h"
#include "Math/Transform.h"
#include "PhysicsTasks.h"

namespace octronic::dream
{
    class PhysicsMotionState;
    class PhysicsObjectDefinition;
    class PhysicsComponent;
    class ModelRuntime;
    class EntityRuntime;

    class PhysicsObjectRuntime : public DiscreteAssetRuntime
    {
    public:
        PhysicsObjectRuntime(ProjectRuntime*, PhysicsObjectDefinition*,EntityRuntime*);
        ~PhysicsObjectRuntime() override;
        bool loadFromDefinition() override;
        btCollisionShape* createCollisionShape(PhysicsObjectDefinition*);
        btCollisionShape* getCollisionShape();
        btRigidBody* getRigidBody();
        void getWorldTransform(btTransform&);
        btCollisionObject* getCollisionObject();

        vec3 getCenterOfMassPosition();
        void applyCentralImpulse(const vec3&);
        void applyTorqueImpulse(const vec3&);
        void applyForce(const vec3&);
        void applyTorque(const vec3&);
        void clearForces();

        void setCenterOfMassTransformTx(Transform& tx);
        void setCenterOfMassTransform3fv(const vec3& tx);
        void setCenterOfMassTransform3f(float x, float y, float z);
        void setCenterOfMassTransformMat4(mat4 tx);

        void setWorldTransform(Transform& tx);

        vec3 getLinearVelocity();
        void setLinearVelocity(vec3);

        bool isInPhysicsWorld();
        void setInPhysicsWorld(bool inPhysicsWorld);

        void setLinearFactor(vec3);

        void setAngularFactor(vec3);
        void setAngularVelocity(vec3);

        float getRestitution() const;
        void setRestitution(float r);

        float getFriction() const;
        void setFriction(float friction);

        float getMass() const;
        void setMass(float mass);

        void  setCcdSweptSphereRadius(float);
        float getCcdSweptSphereRadius();
        void setCameraControllableCharacter();
        void setKinematic(bool setKenematic);

        shared_ptr<PhysicsAddObjectTask> getAddObjectTask();
        void pushTasks() override;

    private:
        PhysicsObjectDefinition* getAssetDefinitionByUuid(UuidType);
        btCollisionShape* createTriangleMeshShape(ModelRuntime*);
	private:
        btCollisionShape* mCollisionShape;
        btMotionState* mMotionState;
        btRigidBody* mRigidBody;
        btRigidBody::btRigidBodyConstructionInfo* mRigidBodyConstructionInfo;
        bool mInPhysicsWorld;
        shared_ptr<PhysicsAddObjectTask> mAddObjectTask;
    };
}
