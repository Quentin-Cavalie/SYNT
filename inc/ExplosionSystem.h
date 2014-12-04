#include "BurstEffect.h"
#include "FlashEffect.h"
#include "ExplosionSparksEffect.h"
#include "DebrisEffect.h"
#include "MistEffect.h"
#include "ShockwaveEffect.h"
#include "BurstEmitter.h"
#include "FlashEmitter.h"
#include "ExplosionSparksEmitter.h"
#include "DebrisEmitter.h"
#include "MistEmitter.h"
#include "ShockwaveEmitter.h"
#include "TrailSystem.h"
#include "ParticleSystemPCH.h"

#include <vector>

class ExplosionSystem
{
public:
	ExplosionSystem();
	~ExplosionSystem();


	void setCamera(PivotCamera *camera);
	void Render();
	void Update(float fDeltaTime);
	void BuildVertexBuffer();

	void addExplosion(glm::vec3 origin);

	void setExplosion();

	void setMist();
	void setBurst();
	void setShockwave();
   	void setFlash();
   	void setTrails();
   	void setExplosionSparks();
    void setDebris();

private:
	std::vector<std::pair<ShockwaveEffect, ShockwaveEmitter> > ShockwaveVector;
	std::vector<std::pair<FlashEffect, FlashEmitter> > FlashVector;
	std::vector<std::pair<BurstEffect, BurstEmitter> > BurstVector;
	std::vector<std::pair<ExplosionSparksEffect, ExplosionSparksEmitter> > SparksVector;
	std::vector<std::pair<DebrisEffect, DebrisEmitter> > DebrisVector;
	std::vector<std::pair<MistEffect, MistEmitter> > MistVector;
	std::vector<TrailSystem> TrailSystemVector;

	PivotCamera *camera;
};