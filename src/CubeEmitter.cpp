#define GLM_FORCE_RADIANS

#include "ParticleSystemPCH.h"
#include "Random.h"
#include "CubeEmitter.h"

CubeEmitter::CubeEmitter()
: MinWidth(-0.01)
, MaxWidth(0.01)
, MinHeight(-0.01)
, MaxHeight(0.01)
, MinDepth(-0.01)
, MaxDepth(0.01)
, MinSpeed(10)
, MaxSpeed(20)
, MinLifetime(0)
, MaxLifetime(0)
, Origin(0)
{}

void CubeEmitter::EmitParticle( Particle& particle )
{
    float X = RandRange( MinWidth, MaxWidth );
    float Y = RandRange( MinHeight, MaxHeight );
    float Z = RandRange( MinDepth, MaxDepth );

    float lifetime = RandRange( MinLifetime, MaxLifetime );
    float speed = RandRange( MinSpeed, MaxSpeed );

    glm::vec3 vector( X, Y, Z );

    particle.m_Position = vector + Origin;
    particle.m_Velocity = glm::normalize(vector) * speed;

    lifetime = lifetime;

    particle.m_fLifeTime = 0;
    particle.m_fAge = 0;
}

void CubeEmitter::DebugRender()
{
    glTranslatef( Origin.x, Origin.y, Origin.z );

    glColor4f( 1.0f, 0.0f, 1.0f, 1.0f );
    
    glutWireCube( MaxWidth * 2 );

    glTranslatef( -Origin.x, -Origin.y, -Origin.z );
}
