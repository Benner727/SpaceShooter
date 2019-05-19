#ifndef PHYSICSMANAGER_H
#define PHSYCICSMANAGER_H

#include "PhysEntity.h"
#include <bitset>

class PhysicsManager
{
private:
	static PhysicsManager* sInstance;

	std::vector<PhysEntity*> mCollisionLayers[static_cast<unsigned int>(PhysEntity::CollisionLayers::MaxLayers)];
	std::bitset<static_cast<unsigned int>(PhysEntity::CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(PhysEntity::CollisionLayers::MaxLayers)];

	unsigned long mLastId;

	PhysicsManager();
	~PhysicsManager();

public:
	static PhysicsManager* Instance();
	static void Release();

	void SetLayerCollisionMask(PhysEntity::CollisionLayers layer, PhysEntity::CollisionFlags flags);

	unsigned long RegisterEntity(PhysEntity* entity, PhysEntity::CollisionLayers layer);
	void UnregisterEntity(unsigned long id);

	void Update();
};

#endif