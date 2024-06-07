#pragma once

#include "raylib.h"
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
	bool m_isDirty; //Already processed a collision response.
	int m_prevTick;

	int m_hWidth = 0;
	int m_hHeight = 0;
	
	
public:
	Critter();
	~Critter();

	void Init(Vector2 position, Vector2 velocity);
	void Spawn(const int screenWidth, const int screenHeight, const int MAX_VELOCITY);
	virtual void SetTexture(const Texture2D* texture);
	void Destroy();
	void Update(const float& dt, const int& tick);
	void WallBounce(const int screenWidth, const int screenHeight);
	void Draw(Color c = WHITE);

	bool Collides(Critter* other);
	virtual void OnCollide(Critter* other, const int MAX_VELOCITY);
	virtual char Type() { return 'c'; }

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

	friend ostream& operator<<(ostream& os, const Critter& b)
	{
		os << "(" << b.GetX() << "," << b.GetY() << ")";
		return os;
	};
};