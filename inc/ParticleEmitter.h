#pragma once

#include "Particle.h"

class ParticleEmitter
{
public:
    virtual ~ParticleEmitter() {}
    virtual void EmitParticle( Particle& particle ) = 0;
    virtual float getMaxLife() {return 0;}
    virtual float getAge() {return 0;}

    virtual void DebugRender() {}
};