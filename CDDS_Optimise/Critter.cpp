#include "Critter.h"
#include "raylib.h"
#include "raymath.h"
#include <random>

Critter::Critter()
{
	m_position = Vector2{ 0, 0 };
	m_velocity = Vector2{ 0, 0 };
	m_isLoaded = false;
}

Critter::~Critter()
{
	m_texture = nullptr;
	m_isLoaded = false;
}

void Critter::Init(Vector2 position, Vector2 velocity)
{
	m_position = position;
	m_velocity = velocity;
	m_isLoaded = true;
}

void Critter::Spawn(const int screenWidth, const int screenHeight, const int MAX_VELOCITY) //Randomly spawn on the screen.
{
	//Create a direction vector of MAX_VELOCITY rotated by a random amount.
	float r = (float)(rand() % 360); //The rotation in degrees (which is a random number from 0-360).
	Vector2 velocity = { (MAX_VELOCITY * cos(r)), (MAX_VELOCITY * sin(r)) }; //Math for a vector of (MAX_VELOCITY,0) being rotated by r. Everything normally multiplied by zero is removed.

	//Spawn randomly within the screen bounds.
	float spawnX = (float)(5 + (rand() % screenWidth - 10));
	float spawnY = (float)(5 + (rand() % screenHeight - 10));

	Init({ spawnX , spawnY }, velocity);
}

void Critter::SetTexture(const Texture2D* texture)
{
	m_texture = texture;
	m_hWidth = (m_texture->width / 2);
	m_hHeight = (m_texture->height / 2);
}

void Critter::Destroy()
{
	/*UnloadTexture(m_texture);*/ //Keep texture while respawning.
	m_isLoaded = false;
}

void Critter::Update(float dt)
{
	if (m_isLoaded == false)
		return;

	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;

	m_isDirty = false;
}

void Critter::WallBounce(const int screenWidth, const int screenHeight) //Bounce off the edges of the screen.
{
	if (GetX() < GetHWidth()) {
		SetX(GetHWidth());
		SetVelocity(Vector2{ -GetVelocity().x, GetVelocity().y });
		SetDirty();
	}
	else if (GetX() > (float)screenWidth - GetHWidth()) {
		SetX((float)screenWidth - GetHWidth());
		SetVelocity(Vector2{ -GetVelocity().x, GetVelocity().y });
		SetDirty();
	}
	else if (GetY() < GetHHeight()) {
		SetY(GetHHeight());
		SetVelocity(Vector2{ GetVelocity().x, -GetVelocity().y });
		SetDirty();
	}
	else if (GetY() > (float)screenHeight - GetHHeight()) {
		SetY((float)screenHeight - GetHHeight());
		SetVelocity(Vector2{ GetVelocity().x, -GetVelocity().y });
		SetDirty();
	}
}

void Critter::Draw()
{
	if (m_isLoaded) { DrawTexture(*m_texture, (int)m_position.x - m_hWidth, (int)m_position.y - m_hHeight, WHITE); }
}


bool Critter::Collides(Critter& other) //Unused
{
	/*float x_dist = abs(GetX() - other.GetX());
	float y_dist = abs(GetY() - other.GetY());
	float x_collide = GetHWidth() + other.GetHWidth();
	float y_collide = GetHHeight() + other.GetHHeight();
	return (x_dist < x_collide) && (y_dist < y_collide);*/

	float dist = Vector2Distance(GetPosition(), other.GetPosition());
	return (dist < GetHWidth() + other.GetHWidth());
}