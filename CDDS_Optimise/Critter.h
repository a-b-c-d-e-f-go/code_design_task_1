#pragma once

#include "raylib.h"
#include "IEntity.h"
#include <random>

class Critter: public IEntity
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

	virtual void Init(Vector2 position, Vector2 velocity) override sealed;
	virtual void Spawn(const int screenWidth, const int screenHeight, const int MAX_VELOCITY) override sealed;
	virtual void SetTexture(const Texture2D* texture) override sealed;
	virtual void Destroy() override sealed;
	virtual void Update(float dt) override sealed;
	virtual void WallBounce(const int screenWidth, const int screenHeight) override sealed;
	virtual void Draw() override sealed;

	virtual bool Collides(IEntity* other) override sealed;
	virtual void OnCollide(IEntity* other, const int MAX_VELOCITY) override;
	virtual char Type() override { return 'c'; }

	virtual const float GetX() const override sealed { return m_position.x; }
	virtual const float GetY() const override sealed { return m_position.y; }
	virtual void SetX(float x) override sealed { m_position.x = x; }
	virtual void SetY(float y) override sealed { m_position.y = y; }

	virtual const Vector2 GetPosition() const override sealed { return m_position; }
	virtual void SetPosition(Vector2 position) override sealed { m_position = position; }

	virtual const Vector2 GetVelocity() const override sealed { return m_velocity; }
	virtual void SetVelocity(Vector2 velocity) override sealed { m_velocity = velocity; }

	virtual const float GetHWidth() const override sealed { return (float)m_hWidth; }
	virtual const float GetHHeight() const override sealed { return (float)m_hHeight; }

	virtual const bool IsDirty() const override sealed { return m_isDirty; }
	virtual void SetDirty() override sealed { m_isDirty = true; }

	virtual const bool IsDead() const override sealed { return m_isLoaded == false; }

};

