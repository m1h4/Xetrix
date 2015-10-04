#pragma once

#include "Vector.h"
#include "Matrix.h"

class Particle
{
public:
	Particle(void) {}
	virtual ~Particle(void) {}

public:
	Vector2 m_position;
	Vector2 m_velocity;
};

typedef Particle* ParticlePtr;

class Emitter
{
public:
	Emitter(void) { for(unsigned long i = 0; i < _countof(m_particles); ++i) m_particles[i].m_position = m_particles[i].m_velocity = Vector2(0.0f,0.0f); }
	virtual ~Emitter(void) {}

	void AddParticle(const Vector2& velocity,const Vector2& position);

	void DrawParticles(void);
	void UpdateParticles(void);

public:
	Particle m_particles[2048];
};

typedef Emitter* EmitterPtr;

class Body
{
public:
	Body(void) {}
	virtual ~Body(void) {}

	void InitializeBody(float mass = 4.0f,float inertia = 0.5f);

	void AddBodyForce(const Vector2& force);	// Center of mass
	void AddBodyForce(const Vector2& force,const Vector2& point);

	Vector2 GetBodyVelocity(void) { return m_linearVelocity; }	// Center of mass
	Vector2 GetBodyVelocity(const Vector2& point);

	bool IsUnmovable(void) const { return m_mass == 0.0f; }

	void UpdateBody(void);

public:
	Vector2	m_position;
	Vector2	m_linearVelocity;
	Vector2	m_force;

	float	m_orientation;
	float	m_angularVelocity;
	float	m_torque;

	float	m_mass;
	float	m_inertia;

	float	m_inverseMass;
	float	m_inverseInertia;

	float	m_linearDamping;
	float	m_angularDamping;
};

typedef Body* BodyPtr;

class Ship : public Body
{
public:
	Ship(void) {}
	virtual ~Ship(void) {}

	void InitializeShip(void) { InitializeBody(4.0f,2.0f); m_rearEngineOrientation = 0.0f; m_rearEnginePosition = Vector2(-1.4f,0.2f); m_mainEngineOrientation = 0.0f; m_mainEnginePosition = Vector2(-0.35f,0.1f); m_frontEngineOrientation = 0.0f; m_frontEnginePosition = Vector2(0.575f,-0.12f); }

	void DrawShip(void);

public:
	Vector2 m_rearEnginePosition;
	Vector2 m_mainEnginePosition;
	Vector2 m_frontEnginePosition;

	float m_rearEngineOrientation;
	float m_mainEngineOrientation;
	float m_frontEngineOrientation;
};

typedef Ship* ShipPtr;

class Missle : public Body
{
public:
	Missle(void) : m_spring(NULL) {}
	~Missle(void) {}

	void InitializeMissle(const Vector2& target) { InitializeBody(); m_target = target; m_life = 0.0f; m_engines[0] = Vector2(-0.07f,-0.2f); m_engines[1] = Vector2(0.07f,-0.2f); }

	void DrawMissle(void);

public:
	Vector2 m_engines[2];
	Vector2	m_target;
	float	m_life;

	Vector2* m_spring;
};

typedef Missle* MisslePtr;

bool InitializeGame(void);
void KillGame(void);

bool UpdateGame(void);
bool KeyboardGame(LPARAM lParam,WPARAM wParam);
bool MouseGame(LPARAM lParam,WPARAM wParam);

bool DrawGame(void);