#include "PhysEntity.h"
#include "PhysicsHelper.h"
#include "PhysicsManager.h"

PhysEntity::PhysEntity()
{
	mBroadPhaseCollider = nullptr;
	mId = 0;
	mCollisionLayer = CollisionLayers::MaxLayers;
}

PhysEntity::~PhysEntity()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		delete mColliders[i];
		mColliders[i] = nullptr;
	}
	mColliders.clear();

	delete mBroadPhaseCollider;
	mBroadPhaseCollider = nullptr;

	if (mId != 0)
	{
		PhysicsManager::Instance()->UnregisterEntity(mId);
	}
}

unsigned long PhysEntity::Id()
{
	return mId;
}

PhysEntity::CollisionLayers PhysEntity::CollisionLayer()
{
	return mCollisionLayer;
}

bool PhysEntity::CheckCollision(PhysEntity* other)
{
	if (IgnoreCollisions() || other->IgnoreCollisions())
		return false;
	
	if (ColliderColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider))
		return (ColliderColliderCheck(mColliders, other->mColliders));
	
	return false;
}

void PhysEntity::Hit(PhysEntity* other)
{
	
}

bool PhysEntity::IgnoreCollisions()
{
	return false;
}

void PhysEntity::AddCollider(Collider* collider, Vector2 localPos)
{
	collider->Parent(this);
	collider->Pos(localPos);
	mColliders.push_back(collider);

	float furthestDist = mColliders[0]->GetFurthestPoint().Magnitude();
	float dist = 0.0f;

	for (int i = 1; i < mColliders.size(); i++)
	{
		dist = mColliders[i]->GetFurthestPoint().Magnitude();

		if (dist > furthestDist)
			furthestDist = dist;
	}

	delete mBroadPhaseCollider;
	mBroadPhaseCollider = new CircleCollider(furthestDist, true);
	mBroadPhaseCollider->Parent(this);
	mBroadPhaseCollider->Pos(VEC2_ZERO);
}

void PhysEntity::Render()
{
	for (int i = 0; i < mColliders.size(); i++)
		mColliders[i]->Render();

	mBroadPhaseCollider->Render();
}