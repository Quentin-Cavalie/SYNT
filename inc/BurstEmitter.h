#include "ParticleEmitter.h"

class BurstEmitter : public ParticleEmitter
{
public:
    BurstEmitter();
    void setOrigin(glm::vec3 origin);
    virtual void EmitParticle(Particle& particle);
    virtual void DebugRender();
    virtual float getMaxLife() {return 0;}
    virtual float getAge() {return 0;}

    float MinimumRadius;
    float MaximumRadius;

    float MinInclination;
    float MaxInclination;

    float MinAzimuth;
    float MaxAzimuth;

    float MinSpeed;
    float MaxSpeed;

    float MinLifetime;
    float MaxLifetime;

    glm::vec3 Origin;
    
private: 
    void RenderSphere(glm::vec4 color, float fRadius);
};
