#include "Globals.h"
#include "Game.h"
#include "Interpolations.h"
#include "Timer.h"
#include "Debug.h"
#include "Array.h"

#ifdef _DEBUG
bool debugDraw = true;
bool debugSpring1 = true;
bool debugSpring2 = true;
#else
bool debugDraw = false;
bool debugSpring1 = false;
bool debugSpring2 = false;
#endif

void Ship::DrawShip(void)
{
	glPushMatrix();
	glTranslatef(m_position.x,m_position.y,0.0f);
	glRotatef(m_orientation / (float)M_PI * 180.0f,0.0f,0.0f,1.0f);

	glPushAttrib(GL_CURRENT_BIT);

	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.25f,0.25f);
		glVertex2f(0.75f,-0.02f);
		glVertex2f(0.75f,-0.2f);
		glVertex2f(-0.25f,-0.2f);
		glVertex2f(-0.75f,0.05f);
		glVertex2f(-1.5f,0.15f);
		glVertex2f(-1.5f,0.25f);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(-0.25f,0.25f);
		glVertex2f(0.0f,0.0f);

		glVertex2f(0.0f,0.0f);
		glVertex2f(0.75f,-0.05f);

		glVertex2f(-1.45f,0.25f);
		glVertex2f(-1.65f,0.4f);

		glVertex2f(-1.65f,0.4f);
		glVertex2f(-1.4f,0.4f);
		
		glVertex2f(-1.4f,0.4f);
		glVertex2f(-1.1f,0.25f);
	glEnd();

	if(debugDraw)
	{
		Vector2 point[] = {Vector2(0.75f,-0.2f),Vector2(-1.5f,0.15f)};
		Matrix2 orientation(m_orientation);
		Matrix2 orientationInverse(-m_orientation);

		glBegin(GL_LINES);
			glColor3f(1.0f,0.0f,0.0f);
			glVertex2fv(point[0]);
			glVertex2fv(point[0] - GetBodyVelocity(m_position + point[0] * orientation) * orientationInverse * 10.0f);
			glVertex2fv(point[1]);
			glVertex2fv(point[1] - GetBodyVelocity(m_position + point[1] * orientation) * orientationInverse * 10.0f);
		glEnd();
	}

	glPushMatrix();
	glTranslatef(m_rearEnginePosition.x,m_rearEnginePosition.y,0.0f);
	glRotatef(m_rearEngineOrientation / (float)M_PI * 180.0f + 90.0f,0.0f,0.0f,1.0f);

	glColor3f(0.0f,1.0f,1.0f);

	// Rear engine
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.08f,0.0f);
		glVertex2f(-0.1f,0.05f);
		glVertex2f(0.08f,0.05f);
		glVertex2f(0.1f,0.0f);
		glVertex2f(0.08f,-0.05f);
		glVertex2f(-0.1f,-0.05f);
	glEnd();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(m_mainEnginePosition.x,m_mainEnginePosition.y,0.0f);
	glScalef(2.0f,2.0f,1.0f);
	glRotatef(m_mainEngineOrientation / (float)M_PI * 180.0f + 90.0f,0.0f,0.0f,1.0f);

	// Main engine
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.08f,0.0f);
		glVertex2f(-0.1f,0.05f);
		glVertex2f(0.08f,0.05f);
		glVertex2f(0.1f,0.0f);
		glVertex2f(0.08f,-0.05f);
		glVertex2f(-0.1f,-0.05f);
	glEnd();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(m_frontEnginePosition.x,m_frontEnginePosition.y,0.0f);
	glRotatef(m_frontEngineOrientation / (float)M_PI * 180.0f + 90.0f,0.0f,0.0f,1.0f);

	// Front engine
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.08f,0.0f);
		glVertex2f(-0.1f,0.05f);
		glVertex2f(0.08f,0.05f);
		glVertex2f(0.1f,0.0f);
		glVertex2f(0.08f,-0.05f);
		glVertex2f(-0.1f,-0.05f);
	glEnd();

	glPopMatrix();

	glPopAttrib();

	glPopMatrix();
}

void Body::InitializeBody(float mass,float inertia)
{
	m_position = m_linearVelocity = m_force = Vector2(0.0f,0.0f);
	m_orientation = m_angularVelocity = m_torque = 0.0f;

	// Use a simple fixed constant damping factor
	m_angularDamping = m_linearDamping = 0.02f;

	m_mass = mass;
	m_inertia = inertia;

	m_inverseMass = (m_mass > 0.0f) ? 1.0f / m_mass : 0.0f;
	m_inverseInertia = (m_inertia > 0.0f) ? 1.0f / m_inertia : 0.0f;
}

void Body::AddBodyForce(const Vector2& force)
{
	if(IsUnmovable())
		return;

	m_force += force;
}

void Body::AddBodyForce(const Vector2& force,const Vector2& point)
{
	if(IsUnmovable())
		return;

	m_force += force;
	m_torque += (point - m_position) ^ force;
}

Vector2 Body::GetBodyVelocity(const Vector2& point)
{
	if(IsUnmovable())
		return Vector2(0.0f,0.0f);

	return m_linearVelocity + Vector2Perpendicular(point - m_position) * m_angularVelocity;	// TODO Could be wrong
}

void Body::UpdateBody(void)
{
	if(IsUnmovable())
	{
		m_linearVelocity = Vector2(0.0f,0.0f);
		m_angularVelocity = 0.0f;
		return;
	}

	float elapsedTime = GetElapsedTime();

	// Apply damping
	m_linearVelocity -= m_linearVelocity * m_linearDamping * elapsedTime;
	m_angularVelocity -= m_angularVelocity * m_angularDamping * elapsedTime;

	// Apply damping forces
	//m_force -= m_linearVelocity * m_linearDamping * elapsedTime;
	//m_torque -= m_angularVelocity * m_angularDamping * elapsedTime;

	// Euler (First Order Taylor Expansion)
	// Integrate position
	//m_position += m_linearVelocity * elapsedTime;
	//m_orientation += m_angularVelocity * elapsedTime;

	// Integrate velocity
	//m_linearVelocity += m_force * (m_inverseMass * elapsedTime);
	//m_angularVelocity += m_torque * (m_inverseInertia * elapsedTime);

	// Second Order Taylor Expansion
	// Integrate position
	m_position += m_linearVelocity * GetElapsedTime() + 0.5f * m_force * m_inverseMass * elapsedTime * elapsedTime;
	m_orientation += m_angularVelocity * GetElapsedTime() + 0.5f * m_torque * m_inverseInertia * elapsedTime * elapsedTime;

	// Remove accumulated rotation
	while(m_orientation > M_PI*2)
		m_orientation -= M_PI*2;

	// Integrate velocity
	m_linearVelocity += m_force * m_inverseMass * elapsedTime;
	m_angularVelocity += m_torque * m_inverseInertia * elapsedTime;

	// Clear forces
	m_force.SetEmpty();
	m_torque = 0.0f;

	// Integrator stability test
	//Sleep(rand() % 40);
}

void Emitter::DrawParticles(void)
{
	glPushAttrib(GL_CURRENT_BIT);

	glBegin(GL_LINES);
		for(unsigned long i = 0; i < sizeof(m_particles)/sizeof(m_particles[0]); ++i)
		{
			float l = m_particles[i].m_velocity.GetLength();

			if(l < 0.0001f)
				continue;

			glColor4f(0.5f,1.0f,0.0f,l * 100.0f < 1.0f ? l * 100.0f : 1.0f);
			glVertex2fv(m_particles[i].m_position);
			glVertex2fv(m_particles[i].m_position - m_particles[i].m_velocity);
		}
	glEnd();

	glPopAttrib();
}

void Emitter::UpdateParticles(void)
{
	static const float linearDamping = 0.2f;

	for(unsigned long i = 0; i < _countof(m_particles); ++i)
	{
		if(m_particles[i].m_velocity.GetLength() < 0.0001f)
			continue;

		// Linear Taylor Expansion
		m_particles[i].m_position += m_particles[i].m_velocity * GetElapsedTime();

		// Simple velocity damping
		m_particles[i].m_velocity -= m_particles[i].m_velocity * linearDamping * GetElapsedTime();
	}
}

void Emitter::AddParticle(const Vector2& velocity,const Vector2& position)
{
	for(unsigned long i = 0; i < _countof(m_particles); ++i)
	{
		if(m_particles[i].m_velocity.GetLength() > 0.0001f)
			continue;

		m_particles[i].m_position = position;
		m_particles[i].m_velocity = velocity;

		return;
	}
}

void Missle::DrawMissle(void)
{
	glPushMatrix();
	glTranslatef(m_position.x,m_position.y,0.0f);
	glRotatef(m_orientation / (float)M_PI * 180.0f,0.0f,0.0f,1.0f);

	glPushAttrib(GL_CURRENT_BIT);

	glBegin(GL_LINE_LOOP);

		glVertex2f(-0.05f,-0.2f);
		glVertex2f( 0.05f,-0.2f);
		glVertex2f( 0.06f, 0.2f);
		glVertex2f( 0.00f, 0.3f);
		glVertex2f(-0.06f, 0.2f);

	glEnd();

	glBegin(GL_LINES);

		glVertex2f(-0.07f,-0.2f);
		glVertex2f(-0.07f,-0.14f);
		glVertex2f( 0.07f,-0.2f);
		glVertex2f( 0.07f,-0.14f);

	glEnd();

	glPopMatrix();

	glColor3f(0.0f,0.0f,1.0f);
	glBegin(GL_LINES);

		glVertex2f(m_target.x - 0.1f,m_target.y - 0.1f);
		glVertex2f(m_target.x + 0.1f,m_target.y + 0.1f);

		glVertex2f(m_target.x + 0.1f,m_target.y - 0.1f);
		glVertex2f(m_target.x - 0.1f,m_target.y + 0.1f);

	glEnd();

	glPopAttrib();
}

Ship gameShip;
Emitter gameEmitter;
Array<MisslePtr> gameMissles;

bool InitializeGame(void)
{
	gameShip.InitializeShip();

	return true;
}

void KillGame(void)
{
}

inline float randf(void)
{
	return (rand() - RAND_MAX / 2) / (float)(RAND_MAX / 2);
}

bool KeyboardGame(LPARAM /*lParam*/,WPARAM wParam)
{
	switch(wParam)
	{
	case VK_SPACE:
		break;

	case VK_F2:
		debugDraw = !debugDraw;
		break;

	case VK_F3:
		debugSpring1 = !debugSpring1;
		break;

	case VK_F4:
		debugSpring2 = !debugSpring2;
		break;
	}

	return true;
}

Vector2 gameAnchor1(0.75f,-0.2f);
Vector2 gameSpring1(0,2);
Vector2 gameAnchor2(-1.5f,0.15f);
Vector2 gameSpring2(1,2);

bool MouseGame(LPARAM lParam,WPARAM /*wParam*/)
{
	double model[16],projection[16];
	int viewport[4];

	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,model);
	glGetDoublev(GL_PROJECTION_MATRIX,projection);

	double x0,y0,z0;
	double x1,y1,z1;

	gluUnProject(LOWORD(lParam),viewport[3] - HIWORD(lParam),0.0f,model,projection,viewport,&x0,&y0,&z0);
	gluUnProject(LOWORD(lParam),viewport[3] - HIWORD(lParam),1.0f,model,projection,viewport,&x1,&y1,&z1);

	x1 -= x0;
	y1 -= y0;
	z1 -= z0;

	// Find the intersection with xOy
	double k = -z0 / z1;

	Vector2 hit(x0 + k * x1,y0 + k * y1);

	//emitter.AddParticle(Vector2(0.01f,0.01f),hit);

#ifdef _DEBUG
	for(unsigned long i = 0; i < gameMissles.GetSize(); ++i)
	{
		if((gameMissles[i]->m_position - hit).GetLength() < 0.4f)
		{
			if(gameMissles[i]->m_spring)
				gameMissles[i]->m_spring = NULL;
			else
				gameMissles[i]->m_spring = &gameSpring1;

			return true;
		}
	}
#endif

	MisslePtr missle = new Missle;

	missle->InitializeMissle(hit);
	
	missle->m_position = gameShip.m_position + Matrix2(gameShip.m_orientation) * Vector2(0.0f,-0.25f);
	missle->m_orientation = gameShip.m_orientation - M_PI_2;
	missle->m_linearVelocity = gameShip.m_linearVelocity + Matrix2(gameShip.m_orientation) * Vector2(0.0f,-0.01f);
	missle->m_angularVelocity = gameShip.m_angularVelocity;

	gameMissles.InsertBack(missle);

	return true;
}

bool UpdateGame(void)
{
	Matrix2 orientation(gameShip.m_orientation);

	Vector2 gravity(0.0f,-0.004f);

	//gameShip.AddBodyForce(gravity);

	float k = 0.001f;

	if(debugSpring1)
	{
		Vector2 force = gameSpring1 - (gameShip.m_position + orientation * gameAnchor1);
		gameShip.AddBodyForce(force * k,gameShip.m_position + orientation * gameAnchor1);
	}
	
	if(debugSpring2)
	{
		Vector2 force = gameSpring2 - (gameShip.m_position + orientation * gameAnchor2);
		gameShip.AddBodyForce(force * k,gameShip.m_position + orientation * gameAnchor2);
	}

	if(HIWORD(GetAsyncKeyState(VK_LEFT)))
	{
		gameShip.m_rearEngineOrientation += GetElapsedTime() / 50.0f;
		gameShip.m_frontEngineOrientation += GetElapsedTime() / 50.0f;
	}

	if(HIWORD(GetAsyncKeyState(VK_RIGHT)))
	{
		gameShip.m_rearEngineOrientation -= GetElapsedTime() / 50.0f;
		gameShip.m_frontEngineOrientation -= GetElapsedTime() / 50.0f;
	}

	if(HIWORD(GetAsyncKeyState('B')))
	{
		gameShip.m_mainEngineOrientation += GetElapsedTime() / 50.0f;
	}

	if(HIWORD(GetAsyncKeyState('N')))
	{
		gameShip.m_mainEngineOrientation -= GetElapsedTime() / 50.0f;
	}

	if(HIWORD(GetAsyncKeyState(VK_UP)))
	{
		Matrix2 rotation(gameShip.m_frontEngineOrientation + gameShip.m_orientation);
		gameShip.AddBodyForce(rotation * Vector2(0.0f,0.002f),gameShip.m_position + orientation * gameShip.m_frontEnginePosition);
		gameEmitter.AddParticle(rotation * -Vector2(randf() / 60.0f,0.1f),gameShip.m_position + Vector2(randf(),randf())/50.0f + orientation * gameShip.m_frontEnginePosition);
	}

	if(HIWORD(GetAsyncKeyState(VK_SPACE)))
	{
		Matrix2 rotation(gameShip.m_mainEngineOrientation + gameShip.m_orientation);
		gameShip.AddBodyForce(rotation * Vector2(0.0f,0.004f),gameShip.m_position + orientation * gameShip.m_mainEnginePosition);
		gameEmitter.AddParticle(rotation * -Vector2(randf() / 60.0f,0.1f),gameShip.m_position + Vector2(randf(),randf())/50.0f + orientation * gameShip.m_mainEnginePosition);
		gameEmitter.AddParticle(rotation * -Vector2(randf() / 60.0f,0.1f),gameShip.m_position + Vector2(randf(),randf())/50.0f + orientation * gameShip.m_mainEnginePosition);
	}

	if(HIWORD(GetAsyncKeyState(VK_UP)))
	{
		Matrix2 rotation(gameShip.m_rearEngineOrientation + gameShip.m_orientation);
		gameShip.AddBodyForce(rotation * Vector2(0.0f,0.001f),gameShip.m_position + orientation * gameShip.m_rearEnginePosition);
		gameEmitter.AddParticle(rotation * -Vector2(randf() / 60.0f,0.1f),gameShip.m_position + Vector2(randf(),randf())/50.0f + orientation * gameShip.m_rearEnginePosition);
	}
	
	gameShip.UpdateBody();
	gameEmitter.UpdateParticles();

	for(unsigned long i = 0; i < gameMissles.GetSize(); ++i)
	{
		Matrix2 orientation(gameMissles[i]->m_orientation);

		gameMissles[i]->AddBodyForce(gravity);

		Vector2 target = Matrix2(-gameMissles[i]->m_orientation) * (gameMissles[i]->m_target - gameMissles[i]->m_position);

		bool left = false,right = false;

		if(gameMissles[i]->m_life > 50.0f)
		{
			if(target.x > -0.1f && target.x < 0.1f && target.y > 0)
				left = right = true;
			else if(target.x < 0)
				right = true;
			else
				left = true;
		}
		
		if(left)
		{
			gameMissles[i]->AddBodyForce(orientation * Vector2(0.0f,0.008f),gameMissles[i]->m_position + orientation * gameMissles[i]->m_engines[0]);
			gameEmitter.AddParticle(orientation * -Vector2(randf() / 60.0f,0.1f),gameMissles[i]->m_position + Vector2(randf(),randf())/50.0f + orientation * gameMissles[i]->m_engines[0]);
			gameEmitter.AddParticle(orientation * -Vector2(randf() / 60.0f,0.1f),gameMissles[i]->m_position + Vector2(randf(),randf())/50.0f + orientation * gameMissles[i]->m_engines[0]);
		}

		if(right)
		{
			gameMissles[i]->AddBodyForce(orientation * Vector2(0.0f,0.008f),gameMissles[i]->m_position + orientation * gameMissles[i]->m_engines[1]);
			gameEmitter.AddParticle(orientation * -Vector2(randf() / 60.0f,0.1f),gameMissles[i]->m_position + Vector2(randf(),randf())/50.0f + orientation * gameMissles[i]->m_engines[1]);
			gameEmitter.AddParticle(orientation * -Vector2(randf() / 60.0f,0.1f),gameMissles[i]->m_position + Vector2(randf(),randf())/50.0f + orientation * gameMissles[i]->m_engines[1]);
		}

		gameMissles[i]->UpdateBody();
		gameMissles[i]->m_life += GetElapsedTime();

		if(gameMissles[i]->m_spring)
		{
			Vector2 force = *gameMissles[i]->m_spring - gameMissles[i]->m_position;
			gameMissles[i]->AddBodyForce(force * k);
		}

		if(gameMissles[i]->m_life > 1500.0f || target.GetLength() < 0.4f)
		{
			for(unsigned long j = 0; j < 256; ++j)
				gameEmitter.AddParticle(Vector2Normalize(Vector2(randf(),randf())) * randf() / 6.0f,gameMissles[i]->m_position);

			delete gameMissles[i];
			gameMissles.Erase(i);

			--i;
		}
	}

	return true;
}

bool DrawGame(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(0.0f,0.0f,-8.0f);
	gluLookAt(0.0f,0.0f,18.0,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);

	glPushAttrib(GL_CURRENT_BIT);

	glBegin(GL_LINES);
		Matrix2 orientation(gameShip.m_orientation);

#ifdef _DEBUG
		if(debugDraw)
		{
			glColor3f(1.0f,0.0f,0.0f);

			glVertex2f(0.0f,0.0f);
			glVertex2f(1.0f,0.0f);

			glColor3f(0.0f,1.0f,0.0f);

			glVertex2f(0.0f,0.0f);
			glVertex2f(0.0f,1.0f);
		}
#endif

		glColor3f(0.0f,0.0f,1.0f);

		if(debugSpring1)
		{
			glVertex2fv(gameSpring1);
			glVertex2fv(gameShip.m_position + orientation * gameAnchor1);
		}

		if(debugSpring2)
		{
			glVertex2fv(gameSpring2);
			glVertex2fv(gameShip.m_position + orientation * gameAnchor2);
		}

		for(unsigned long i = 0; i < gameMissles.GetSize(); ++i)
		{
			if(gameMissles[i]->m_spring)
			{
				glVertex2fv(*gameMissles[i]->m_spring);
				glVertex2fv(gameMissles[i]->m_position);
			}
		}
	glEnd();

	glPopAttrib();

	gameShip.DrawShip();
	gameEmitter.DrawParticles();

	for(unsigned long i = 0; i < gameMissles.GetSize(); ++i)
		gameMissles[i]->DrawMissle();

	return true;
}