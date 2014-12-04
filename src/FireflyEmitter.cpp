#include "ParticleSystemPCH.h"
#include "Random.h"
#include "FireflyEmitter.h"

FireflyEmitter::FireflyEmitter()
: MinimumRadius(0)
, MaximumRadius(0.6)
, MinInclination(180)
, MaxInclination(360)
, MinAzimuth(180)
, MaxAzimuth(360)
, MinSpeed(42)
, MaxSpeed(50)
, MinLifetime(0.14)
, MaxLifetime(0.14)
, Origin(0)
, Velocity(0)
, Position(0)
, Force(0)
, Speed(200)
, ForceTime(0.02)
, Age(0)
, isActive(true)
, SphereRadius(20)
, Collided(false)
, CollisionTime(0)
, newForce(true)
{
   // Rotate = RandRange(0,180);
}


bool FireflyEmitter::Active()
{
    return isActive;
}

void FireflyEmitter::setOrigin(glm::vec3 origin)
{
    this->Origin = origin;
    this->Position = origin;
}

void FireflyEmitter::setVelocity(glm::vec3 velocity)
{
	this->Velocity = velocity;
}

glm::vec3 FireflyEmitter::getPos()
{
    return Position;
}

float FireflyEmitter::getMaxLife()
{
	return 0;
}

float FireflyEmitter::getAge()
{
	return Age;
}

void FireflyEmitter::Update(float fDeltaTime)
{
	Age += fDeltaTime;

	if (Age >= ForceTime)
    {
        if (Collided)
            CollisionTime++;

        if (CollisionTime == 1)
            Collided = false;

        Age = 0;

        if (!Collided)
        {
            Force = RandomNewForce();
            Velocity.x /= 4;
            Velocity.y /= 4;
            Velocity.z /= 4;
            CollisionTime = 0;
            Collided = false;
        }
    }

    float Pos = sqrt(pow(Position.x, 2) + pow(Position.y, 2) + pow(Position.z, 2));

    if (Pos > SphereRadius)
    {
        Collided = true;
        Velocity = -Position * RandRange(50, 75);
        // Force = -Position * RandRange(2000, 3000);
    }
	
    Velocity += Force * fDeltaTime;
	Position += Velocity * fDeltaTime;

    // Position = glm::vec3(0, 0, 0);
}

void FireflyEmitter::EmitParticle( Particle& particle )
{
    float inclination = glm::radians( RandRange( MinInclination, MaxInclination ) );
    float azimuth = glm::radians( RandRange( MinAzimuth, MaxAzimuth ) );

    float radius = RandRange( MinimumRadius, MaximumRadius );
    //float speed = RandRange( MinSpeed, MaxSpeed );
    float lifetime = RandRange( MinLifetime, MaxLifetime );

    float sInclination = sinf( inclination );

    float X = sInclination * cosf( azimuth );
    float Y = sInclination * sinf( azimuth );
    float Z = cosf( inclination );

    glm::vec3 vector( X, Y, Z );

    // particle.m_Position = ( vector * radius ) + Origin;
    particle.m_Position = (vector * radius ) + Position;

    particle.m_Velocity = glm::vec3(0, 0, 0);
    // particle.m_Velocity = RandFireflyUnitVec() * speed;

    particle.m_fLifeTime = lifetime;
    particle.m_fAge = 0;

    particle.m_fRotate = (RandRange(40,180));

}

void FireflyEmitter::RenderSphere( glm::vec4 color, float fRadius )
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

void FireflyEmitter::DebugRender()
{
    glTranslatef( Origin.x, Origin.y, Origin.z );

    // RenderSphere( glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), MinimumRadius );
     RenderSphere( glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), MaximumRadius );

    glTranslatef( -Origin.x, -Origin.y, -Origin.z );
}
