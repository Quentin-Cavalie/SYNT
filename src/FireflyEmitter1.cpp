#include "ParticleSystemPCH.h"
#include "Random.h"
#include "FireflyEmitter1.h"

FireflyEmitter1::FireflyEmitter1()
: MinimumRadius(0)
, MaximumRadius(0.6)
, MinInclination(0)
, MaxInclination(360)
, MinAzimuth(0)
, MaxAzimuth(360)
, MinSpeed(42)
, MaxSpeed(50)
, MinLifetime(0.14)
, MaxLifetime(0.14)
, Origin(0)
, Velocity(0)
, Position(glm::vec3(2, 0, 2))
, Force(0)
, Speed(200)
, ForceTime(0.02)
, Age(0)
, isActive(true)
, SphereRadius(30)
, Collided(false)
, CollisionTime(0)
, newForce(true)
, Angle(0)
{
   // Rotate = RandRange(0,180);
}


bool FireflyEmitter1::Active()
{
    return isActive;
}

void FireflyEmitter1::setOrigin(glm::vec3 origin)
{
    this->Origin = origin;
    this->Position = origin;
}

void FireflyEmitter1::setVelocity(glm::vec3 velocity)
{
	this->Velocity = velocity;
}

float FireflyEmitter1::getMaxLife()
{
	return 0;
}

float FireflyEmitter1::getAge()
{
	return Age;
}

void FireflyEmitter1::Update(glm::vec3 rotCenter, float fDeltaTime)
{
    Angle += 7 % 360;

    float radian = glm::radians(Angle);
    float radius = glm::distance(Position, rotCenter);
    radius = 2.5;

    // std::cout << radius << std::endl;

    float x = rotCenter.x + (radius * cosf(radian));
    float z = rotCenter.z + (radius * sinf(radian));

    Position = glm::vec3(x, rotCenter.y, z);
}

void FireflyEmitter1::EmitParticle( Particle& particle )
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
    // particle.m_Velocity = RandFirefly1UnitVec() * speed;

    particle.m_fLifeTime = lifetime;
    particle.m_fAge = 0;

    particle.m_fRotate = (RandRange(40,180));

}

void FireflyEmitter1::RenderSphere( glm::vec4 color, float fRadius )
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

void FireflyEmitter1::DebugRender()
{
    glTranslatef( Origin.x, Origin.y, Origin.z );

    // RenderSphere( glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), MinimumRadius );
     RenderSphere( glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), MaximumRadius );

    glTranslatef( -Origin.x, -Origin.y, -Origin.z );
}
