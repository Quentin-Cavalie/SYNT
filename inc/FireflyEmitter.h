#include "ParticleEmitter.h"

class FireflyEmitter : public ParticleEmitter
{
public:
    FireflyEmitter();
    bool Active();
    void setOrigin(glm::vec3 origin);
    void setVelocity(glm::vec3 velocity);
    void Update(float fDelaTime);
    glm::vec3 getPos();
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
    glm::vec3 Force;

    float Speed;
    float ForceTime;
    float Age;
    bool isActive;
    float SphereRadius;
    bool Collided;
    int CollisionTime;
    bool newForce;

private: 
    void RenderSphere(glm::vec4 color, float fRadius);
};