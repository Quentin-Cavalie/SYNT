#include "ParticleSystemPCH.h"
#include "Random.h"
#include "TrailEmitter.h"

TrailEmitter::TrailEmitter()
: MinimumRadius(0)
, MaximumRadius(1)
, MinInclination(0)
, MaxInclination(360)
, MinAzimuth(0)
, MaxAzimuth(360)
, MinSpeed(42)
, MaxSpeed(50)
, MinLifetime(0.009)
, MaxLifetime(0.009)
, Origin(0)
, Velocity(0)
, Position(0)
, Speed(200)
, EmitterLife(0.01)
, Age(0)
, isActive(true)
{
   // Rotate = RandRange(0,180);
}


bool TrailEmitter::Active()
{
    return isActive;
}

void TrailEmitter::setOrigin(glm::vec3 origin)
{
    this->Origin = origin;
    this->Position = origin;
}

void TrailEmitter::setVelocity(glm::vec3 velocity)
{
	this->Velocity = velocity;
}

float TrailEmitter::getMaxLife()
{
	return EmitterLife;
}

float TrailEmitter::getAge()
{
	return Age;
}

void TrailEmitter::Update(float fDeltaTime)
{
	Age += fDeltaTime;

	if (Age >= EmitterLife)
		isActive = false;
	
	Position += Velocity * fDeltaTime;
}

void TrailEmitter::EmitParticle( Particle& particle )
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

    // particle.m_Position = ( vector * radius ) + Origin;
    particle.m_Position = Position;

    particle.m_Velocity = glm::vec3(0, 0, 0);
    // particle.m_Velocity = RandTrailUnitVec() * speed;

    particle.m_fLifeTime = lifetime;
    particle.m_fAge = 0;

    particle.m_fRotate = (RandRange(40,180));

}

void TrailEmitter::RenderSphere( glm::vec4 color, float fRadius )
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

void TrailEmitter::DebugRender()
{
    glTranslatef( Origin.x, Origin.y, Origin.z );

    // RenderSphere( glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), MinimumRadius );
     RenderSphere( glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), MaximumRadius );

    glTranslatef( -Origin.x, -Origin.y, -Origin.z );
}
