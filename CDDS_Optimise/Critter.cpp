#include "Critter.h"
#include "raylib.h"
#include "raymath.h"
#include <random>

Critter::Critter()
{
	m_position = Vector2{ 0, 0 };
	m_velocity = Vector2{ 0, 0 };
	m_isLoaded = false;
	m_isDirty = true;
	m_prevTick = 0;
	m_texture = nullptr;
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
	float spawnX = (float)(rand() % screenWidth);
	float spawnY = (float)(rand() % screenHeight);

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

void Critter::Update(const float& dt, const int& tick)
{
	if (tick == m_prevTick || !m_isLoaded)
		return;

	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;
	WallBounce(800, 450);

	m_isDirty = false;
	m_prevTick = tick;
}

void Critter::WallBounce(const int screenWidth, const int screenHeight) //Bounce off the edges of the screen.
{
	if (m_position.x < 0) { //Left Wall
		m_position.x = 0; //Clamp x position.
		m_velocity.x *= -1; //Invert x velocity.
		m_isDirty = true; //Set dirty.
	}
	else if (m_position.x > (float)screenWidth) { //Right Wall
		m_position.x = (float)screenWidth; //Clamp x position.
		m_velocity.x *= -1; //Invert x velocity.
		m_isDirty = true; //Set dirty.
	}
	else if (m_position.y < 0) { //Top Wall
		m_position.y = 0; //Clamp y position.
		m_velocity.y *= -1; //Invert y velocity.
		m_isDirty = true; //Set dirty.
	}
	else if (m_position.y > (float)screenHeight) { //Bottom Wall
		m_position.y = (float)screenHeight; //Clamp y position
		m_velocity.y *= -1; //Invert y velocity.
		m_isDirty = true; //Set dirty.
	}
}

void Critter::Draw(Color c)
{
	if (m_isLoaded) { DrawTexture(*m_texture, (int)m_position.x - m_hWidth, (int)m_position.y - m_hHeight, c); }
}


bool Critter::Collides(Critter* other)
{
	//AABB Collision (Apparently slower???)
	/*float x_dist = abs(m_position.x - other.m_position.x);
	float y_dist = abs(m_position.y - other.m_position.y);
	float x_collide = m_hWidth + other.m_hWidth;
	float y_collide = m_hHeight + other.m_hHeight;
	return (x_dist < x_collide) && (y_dist < y_collide);*/

	float dist = Vector2Distance(m_position, other->m_position);
	return (dist < m_hWidth + other->m_hWidth);
}

void Critter::OnCollide(Critter* other, const int MAX_VELOCITY)
{
	if (Type() == other->Type())
	{
		// collision!
		// do math to get critters bouncing
		Vector2 normal = Vector2Normalize(Vector2Subtract(other->GetPosition(), GetPosition()));

		// not even close to real physics, but fine for our needs
		SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));
		// set the critter to *dirty* so we know not to process any more collisions on it
		SetDirty();

		// we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
		// to make sure the other critter is clean before we do the collision response
		if (!other->IsDirty()) {
			other->SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
			other->SetDirty();
		}
	}
}