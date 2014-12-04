#include "ParticleEmitter.h"

class TrailEmitter : public ParticleEmitter
{
public:
    TrailEmitter();
    bool Active();
    void setOrigin(glm::vec3 origin);
    void setVelocity(glm::vec3 velocity);
    void Update(float fDelaTime);
    virtual void EmitParticle(Particle& particle);
    virtual void DebugRender();
    virtual float getMaxLife();
    virtual float getAge();


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
    glm::vec3 Velocity;
    glm::vec3 Position;
    float Speed;
    float EmitterLife;
    float Age;
    bool isActive;

private: 
    void RenderSphere(glm::vec4 color, float fRadius);
};
