#pragma once
#include "raylib.h"

class IEntity
{
public:
	virtual void Init(Vector2 position, Vector2 velocity) = 0;
	virtual void Spawn(const int screenWidth, const int screenHeight, const int MAX_VELOCITY) = 0;
	virtual void SetTexture(const Texture2D* texture) = 0;
	virtual void Destroy() = 0;
	virtual void Update(float dt) = 0;
	virtual void WallBounce(const int screenWidth, const int screenHeight) = 0;
	virtual void Draw() = 0;

	virtual bool Collides(IEntity* other) = 0;
	virtual void OnCollide(IEntity* other, const int MAX_VELOCITY) = 0;
	virtual char Type() = 0;

	virtual const float GetX() const = 0;
	virtual const float GetY() const = 0;
	virtual void SetX(float x) = 0;
	virtual void SetY(float y) = 0;

	virtual const Vector2 GetPosition() const = 0;
	virtual void SetPosition(Vector2 position) = 0;

	virtual const Vector2 GetVelocity() const = 0;
	virtual void SetVelocity(Vector2 velocity) = 0;

	virtual const float GetHWidth() const = 0;
	virtual const float GetHHeight() const = 0;

	virtual const bool IsDirty() const = 0;
	virtual void SetDirty() = 0;

	virtual const bool IsDead() const = 0;
};