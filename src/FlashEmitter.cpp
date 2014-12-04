#include "ParticleSystemPCH.h"
#include "Random.h"
#include "FlashEmitter.h"

FlashEmitter::FlashEmitter()
: MinimumRadius(-1.5)
, MaximumRadius(1.5)
, MinInclination(0)
, MaxInclination(360)
, MinAzimuth(0)
, MaxAzimuth(180)
, MinSpeed(12)
, MaxSpeed(20)
, MinLifetime(0.015)
, MaxLifetime(0.015)
, Origin(0)
{}


void FlashEmitter::setOrigin(glm::vec3 origin)
{
    this->Origin = origin;
}

void FlashEmitter::EmitParticle( Particle& particle )
{
    float inclination = glm::radians( RandRange( MinInclination, MaxInclination ) );
    float azimuth = glm::radians( RandRange( MinAzimuth, MaxAzimuth ) );

    float radius = RandRange( MinimumRadius, MaximumRadius );
    float speed = RandRange( MinSpeed, MaxSpeed );
    float lifetime = RandRange( MinLifetime, MaxLifetime );

    float sInclination = sinf( inclination );

    float X = sInclination * cosf( azimuth );
    float Y = sInclination * sinf( azimuth );
    float Z = cosf( inclination );

    glm::vec3 vector( X, Y, Z );

    particle.m_Position = ( vector * radius ) + Origin;
    particle.m_Velocity = RandFlashUnitVec() * speed;

    particle.m_fLifeTime = lifetime;
    particle.m_fAge = 0;

    float f = RandRange(1.0f, 2.0f);
        if (f > 1.5f)
            particle.m_ClockRot = 1;
        else
            particle.m_ClockRot = -1;


}

void FlashEmitter::RenderSphere( glm::vec4 color, float fRadius )
{
    float X, Y, Z, inc, azi;

    glColor4fv( glm::value_ptr(color) );

    glPointSize(2.0f);
    glBegin( GL_POINTS );

    for ( float azimuth = MinAzimuth; azimuth < MaxAzimuth; azimuth += 5.0f )
    {
        for ( float inclination = MinInclination; inclination < MaxInclination; inclination += 5.0f )
        {
            inc = glm::radians(inclination);
            azi = glm::radians(azimuth);

            X = fRadius * sinf( inc ) * cosf( azi );
            Y = fRadius * sinf( inc ) * sinf( azi );
            Z = fRadius * cosf( inc );

            glVertex3f(X, Y, Z );
        }

        inc = glm::radians(MaxInclination);
        azi = glm::radians(azimuth);

        X = fRadius * sinf( inc ) * cosf( azi );
        Y = fRadius * sinf( inc ) * sinf( azi );
        Z = fRadius * cosf( inc );

        glVertex3f(X, Y, Z );
    }

    inc = glm::radians(MaxInclination);
    azi = glm::radians(MaxAzimuth);

    X = MaximumRadius * sinf( inc ) * cosf( azi );
    Y = MaximumRadius * sinf( inc ) * sinf( azi );
    Z = MaximumRadius * cosf( inc );

    glVertex3f(X, Y, Z );

    glEnd();
}

void FlashEmitter::DebugRender()
{
    glTranslatef( Origin.x, Origin.y, Origin.z );

    // RenderSphere( glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), MinimumRadius );
     RenderSphere( glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), MaximumRadius );

    glTranslatef( -Origin.x, -Origin.y, -Origin.z );
}
