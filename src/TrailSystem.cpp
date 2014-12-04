#include "TrailSystem.h"
#include "Random.h"

TrailSystem::TrailSystem(int numTrails, glm::vec3 origin)
: Speed (3000)
, LifeTime(0.1)
, Age(0)
, MinimumRadius(0)
, MaximumRadius(0)
{
	this->numTrails = numTrails;
	this->origin = origin;
}

TrailSystem::~TrailSystem()
{

}

bool TrailSystem::Active()
{
	isActive = false;

	for (auto it = TrailVector.begin(); it != TrailVector.end(); it++)
	{
		if (it->second.Active())
			isActive = true; 
	}

	return isActive;
}

void TrailSystem::setCamera(PivotCamera *camera)
{
	this->camera = camera;
}

void TrailSystem::addTrails()
{
	for (int i = 0; i < numTrails; ++i)
	{
		TrailEffect *tE = new TrailEffect(1);
		TrailEmitter *tEm = new TrailEmitter();

		float radius = RandRange(MinimumRadius, MaximumRadius);

		glm::vec3 velocity = RandTrailUnitVec();

		tEm->setOrigin((velocity * radius) + origin);
		velocity *= Speed;
		tEm->setVelocity(velocity);


		std::pair<TrailEffect, TrailEmitter> p (*tE, *tEm);
		TrailVector.push_back(p);
	}
}

void TrailSystem::setTrails()
{
	for (auto it = TrailVector.begin(); it != TrailVector.end(); it++)
	{
		it->first.LoadTexture("./Textures/fire/fire2.png");

    	TrailEffect::ColorInterpolator trailColors;

    	trailColors.AddValue(0.0f, glm::vec4(0.94, 0.91, 0.66, 0.3));
    	trailColors.AddValue(0.1f, glm::vec4(1, 0.84, 0.0, 0.5));
    	trailColors.AddValue(0.15f, glm::vec4(1, 0.55, 0.0, 0.5));
    	trailColors.AddValue(0.75f, glm::vec4(0.1, 0.1, 0.1, 0.0));

    	it->first.SetColorInterplator(trailColors);
    	it->first.SetParticleEmitter(&it->second);
    	it->first.EmitParticles();
    	it->first.SetCamera(camera); 
	}
}

void TrailSystem::Render()
{
	for(auto it = TrailVector.begin(); it != TrailVector.end(); it++)
		it->first.Render();
}

void TrailSystem::Update(float fDeltaTime)
{
	int i = 0;

	for (auto it = TrailVector.begin(); it != TrailVector.end();)
	{

		if (it->second.Active())
		{
			it->second.Update(fDeltaTime);
			it->first.Update(fDeltaTime);
			it++;
			i++;
		}
		else
			TrailVector.erase(TrailVector.begin() + i);
	}
}

void TrailSystem::BuildVertexBuffer()
{
	for (auto it = TrailVector.begin(); it != TrailVector.end(); it++)
		it->first.BuildVertexBuffer();
}