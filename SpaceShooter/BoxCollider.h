#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"
#include <vector>

class BoxCollider : public Collider
{
private:
	static const int MAX_VERTS = 4;
	GameEntity* mVerts[MAX_VERTS];

	void AddVert(int index, Vector2 pos);

public:
	BoxCollider(Vector2 size, float rotation = 0.0f);
	~BoxCollider();

	Vector2 Corner(int index);
	std::vector<Vector2> Axis();
	Vector2 Projection(Vector2 axis);

	float Width();
	float Height();

	Vector2 GetFurthestPoint() override;

	/*
	void Render() override
	{
		for (int i = 0; i < MAX_VERTS; i++)
		{
			Graphics::Instance()->DrawLine(Corner(i), Corner(i + 1 == MAX_VERTS ? 0 : i + 1));
		}
	}
	*/
};

#endif