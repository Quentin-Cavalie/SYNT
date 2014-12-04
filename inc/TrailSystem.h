#include <vector>
#include "TrailEffect.h"
#include "PivotCamera.h"
#include "TrailEmitter.h"
#include "ParticleSystemPCH.h"

class TrailSystem
{
	public:
		TrailSystem(int numTrails, glm::vec3 origin);
		~TrailSystem();

		void setCamera(PivotCamera *camera);
		void setTrails();
		void addTrails();
		bool Active();
		void Render();
		void Update(float fDeltaTime);
		void BuildVertexBuffer();

	private:
		std::vector<std::pair<TrailEffect, TrailEmitter> > TrailVector;
		PivotCamera *camera;
		glm::vec3 origin;
		int numTrails;
		float Speed;
		float LifeTime;
		float Age;
		float MinimumRadius;
		float MaximumRadius;

		bool isActive;
};