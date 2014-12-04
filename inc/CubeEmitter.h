#include "ParticleEmitter.h"

class CubeEmitter : public ParticleEmitter
{
public:
    CubeEmitter();

    virtual void EmitParticle(Particle& particle);
    virtual void DebugRender();
    virtual float getMaxLife() {return 0;}
    virtual float getAge() {return 0;}

    float MinWidth;
    float MaxWidth;

    float MinHeight;
    float MaxHeight;

    float MinDepth;
    float MaxDepth;

    float MinSpeed;
    float MaxSpeed;

    float MinLifetime;
    float MaxLifetime;

    glm::vec3 Origin;
};