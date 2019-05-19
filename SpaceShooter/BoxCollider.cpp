#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 size, float rotation)
	: Collider(ColliderType::Box)
{
	AddVert(0, RotateVector(Vector2(-0.5f * size.x, -0.5f * size.y), rotation)); //Top left
	AddVert(1, RotateVector(Vector2( 0.5f * size.x, -0.5f * size.y), rotation)); //Top right
	AddVert(2, RotateVector(Vector2( 0.5f * size.x,  0.5f * size.y), rotation)); //Bottom right
	AddVert(3, RotateVector(Vector2(-0.5f * size.x,  0.5f * size.y), rotation)); //Bottom left

	if (DEBUG_COLLIDERS)
	{
		SetDebugTexture(new Texture("BoxCollider.png"));
		mDebugTexture->Scale(size / 100.0f);
		mDebugTexture->Rotation(rotation);
	}
}

BoxCollider::~BoxCollider()
{
	for (int i = 0; i < MAX_VERTS; i++)
	{
		delete mVerts[i];
		mVerts[i] = nullptr;
	}
}

Vector2 BoxCollider::Corner(int index)
{
	Vector2 temp = mVerts[index]->Pos() - Pos();
	temp = RotateVector(temp, Rotation());
	temp += Pos();
	return temp;
}

std::vector<Vector2> BoxCollider::Axis()
{
	std::vector<Vector2> axis;

	for (int i = 0; i < MAX_VERTS; i++)
	{
		axis.push_back(Corner(i) - Corner(i + 1 == MAX_VERTS ? 0 : i + 1));
		axis[i] = Perp(axis[i]);
		axis[i] = axis[i].Normalize();
	}

	return axis;
}

Vector2 BoxCollider::Projection(Vector2 axis)
{
	float min = Dot(axis, Corner(0));
	float max = min;

	for (int i = 1; i < MAX_VERTS; i++)
	{
		float current = Dot(axis, Corner(i));

		if (current < min)
			min = current;
		else if (current > max)
			max = current;
	}

	return Vector2(min, max);
}

float BoxCollider::Width()
{
	return (mVerts[0]->Pos() - mVerts[1]->Pos()).Magnitude();
}

float BoxCollider::Height()
{
	return (mVerts[0]->Pos() - mVerts[3]->Pos()).Magnitude();
}

Vector2 BoxCollider::GetFurthestPoint()
{
	Vector2 localPos = Pos(GameEntity::local);

	int furthestIndex = 0;
	float dist = (localPos + mVerts[0]->Pos(GameEntity::local)).MagnitudeSqr();
	float otherDist = 0.0f;

	for (int i = 1; i < MAX_VERTS; i++)
	{
		otherDist = (localPos + mVerts[i]->Pos(GameEntity::local)).MagnitudeSqr();
		
		if (otherDist > dist)
		{
			furthestIndex = i;
			dist = otherDist;
		}
	}

	return (localPos + mVerts[furthestIndex]->Pos(GameEntity::local));
}

void BoxCollider::AddVert(int index, Vector2 pos)
{
	mVerts[index] = new GameEntity(pos);
	mVerts[index]->Parent(this);
}