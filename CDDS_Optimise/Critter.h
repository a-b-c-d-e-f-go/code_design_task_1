#pragma once

#include "AL.h"
#include "raylib.h"
#include "raymath.h"
#include <random>
#include <iostream>
using namespace std;

class Critter
{
protected:	
	Vector2 m_position;
	Vector2 m_velocity;

	const Texture2D* m_texture;

	bool m_isLoaded;
	bool m_isDirty;		// indicates if we've already processed a collision response for this critter

	int m_hWidth = 0;
	int m_hHeight = 0;
	
public:
	Critter();
	~Critter();

	void Init(Vector2 position, Vector2 velocity);
	void Spawn();
	virtual void SetTexture(const Texture2D* texture);
	void Destroy();
	void WallBounce();
	void Update(float dt);
	void Draw(Color c = WHITE);

	bool Collides(Critter* other);
	virtual void OnCollide(Critter* other);

	const float GetX() const { return m_position.x; }
	const float GetY() const { return m_position.y; }
	void SetX(float x) { m_position.x = x; }
	void SetY(float y) { m_position.y = y; }

	const Vector2 GetPosition() const { return m_position; }
	void SetPosition(Vector2 position) { m_position = position; }

	const Vector2 GetVelocity() const { return m_velocity; }
	void SetVelocity(Vector2 velocity) { m_velocity = velocity; }

	const float GetHWidth() const { return (float)m_hWidth; }
	const float GetHHeight() const { return (float)m_hHeight; }

	const bool IsDirty() const { return m_isDirty; }
	void SetDirty() { m_isDirty = true; }

	const bool IsDead() const { return m_isLoaded == false; }

	friend ostream& operator<<(ostream& os, const Critter& b) //Print as (x,y).
	{
		os << "(" << b.GetX() << "," << b.GetY() << ")";
		return os;
	};
};