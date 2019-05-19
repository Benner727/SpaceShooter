#ifndef PHYSICSHELPER_H
#define PHYSICSHELPER_H

#include "CircleCollider.h"
#include "BoxCollider.h"
#include "MathHelper.h"

inline bool CircleCircleCollision(CircleCollider* c1, CircleCollider* c2)
{
	return (((c1->Pos(GameEntity::world) - c2->Pos(GameEntity::world)).Magnitude()) < (c1->Radius() + c2->Radius()));
}

inline bool BoxBoxCollision(BoxCollider* b1, BoxCollider* b2)
{
	std::vector<Vector2> axis1 = b1->Axis();
	std::vector<Vector2> axis2 = b2->Axis();

	for (int i = 0; i < axis1.size(); i++)
	{
		Vector2 p1 = b1->Projection(axis1[i]);
		Vector2 p2 = b2->Projection(axis1[i]);

		if (!Overlap(p1, p2))
			return false;
	}

	for (int i = 0; i < axis2.size(); i++)
	{
		Vector2 p1 = b1->Projection(axis2[i]);
		Vector2 p2 = b2->Projection(axis2[i]);

		if (!Overlap(p1, p2))
			return false;
	}

	return true;
}

inline bool BoxCircleCollision(BoxCollider* b1, CircleCollider* c1)
{
	for (int i = 0; i < 4; i++)
	{
		Vector2 closest = ClosestPoint(b1->Corner(i), b1->Corner(i + 1 == 4 ? 0 : i + 1), c1->Pos());
		Vector2 dist = c1->Pos() - closest;

		if (dist.Magnitude() < c1->Radius())
			return true;
	}

	return false;

	/*
	if ((b1->Pos(GameEntity::world) - c1->Pos(GameEntity::world)).Magnitude() < c1->Radius())
		return true;

	for (int i = 0; i < 4; i++)
	{
		if ((b1->Corner(i) - c1->Pos(GameEntity::world)).Magnitude() < c1->Radius())
			return true;
	}
	
	return false;
	*/
}

inline bool ColliderColliderCheck(Collider* c1, Collider* c2)
{
	if (c1->GetType() == Collider::ColliderType::Circle && c2->GetType() == Collider::ColliderType::Circle)
		return CircleCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
	else if (c1->GetType() == Collider::ColliderType::Box && c2->GetType() == Collider::ColliderType::Circle)
		return BoxCircleCollision(static_cast<BoxCollider*>(c1), static_cast<CircleCollider*>(c2));
	else if (c1->GetType() == Collider::ColliderType::Circle && c2->GetType() == Collider::ColliderType::Box)
		return BoxCircleCollision(static_cast<BoxCollider*>(c2), static_cast<CircleCollider*>(c1));
	else if (c1->GetType() == Collider::ColliderType::Box && c2->GetType() == Collider::ColliderType::Box)
		return BoxBoxCollision(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
	else
		return false;
}

inline bool ColliderColliderCheck(std::vector<Collider*> c1, std::vector<Collider*> c2)
{
	for (int i = 0; i < c1.size(); i++)
	{
		for (int j = 0; j < c2.size(); j++)
		{
			if (c1[i]->GetType() == Collider::ColliderType::Box && c2[j]->GetType() == Collider::ColliderType::Box)
			{
				if (BoxBoxCollision(static_cast<BoxCollider*>(c1[i]), static_cast<BoxCollider*>(c2[j])))
					return true;
			}
			else if (c1[i]->GetType() == Collider::ColliderType::Box && c2[j]->GetType() == Collider::ColliderType::Circle)
			{
				if (BoxCircleCollision(static_cast<BoxCollider*>(c1[i]), static_cast<CircleCollider*>(c2[j])))
					return true;
			}
			else if (c1[i]->GetType() == Collider::ColliderType::Circle && c2[j]->GetType() == Collider::ColliderType::Box)
			{
				if (BoxCircleCollision(static_cast<BoxCollider*>(c2[j]), static_cast<CircleCollider*>(c1[i])))
					return true;
			}
			else if (c1[i]->GetType() == Collider::ColliderType::Circle && c2[j]->GetType() == Collider::ColliderType::Circle)
			{
				if (CircleCircleCollision(static_cast<CircleCollider*>(c1[i]), static_cast<CircleCollider*>(c2[j])))
					return true;
			}
		}
	}

	return false;
}

#endif