#include "ParticleSystemPCH.h"
#include "FlameEmitter.h"
#include "Camera.h"
#include "Random.h"
#include "FireflyEffect1.h"

FireflyEffect1::FireflyEffect1(unsigned int numParticles /* = 0 */)
: m_pCamera( NULL )
, m_pParticleEmitter( NULL )
, m_ColorInterpolator( glm::vec4(1) )
, m_LocalToWorldMatrix(1)
, m_TextureID(0)
, m_Force( 0, 0, 0 )
, max_particle(15000)
{
  Resize(numParticles);
}

FireflyEffect1::~FireflyEffect1()
{
}

void FireflyEffect1::SetCamera( Camera* pCamera )
{
    m_pCamera = pCamera;
}

void FireflyEffect1::SetParticleEmitter( ParticleEmitter* pEmitter )
{
    m_pParticleEmitter = pEmitter;
}

void FireflyEffect1::SetColorInterplator( const ColorInterpolator& colors )
{
    m_ColorInterpolator = colors;
}

bool FireflyEffect1::LoadTexture( const std::string& fileName )
{
    // if ( m_TextureID != 0 )
    //     glDeleteTextures(1, &m_TextureID );

    m_TextureID = SOIL_load_OGL_texture( fileName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS );

    return ( m_TextureID != 0 );
}

void FireflyEffect1::RandomizeParticle( Particle& particle )
{
    particle.m_fAge = 0.0f;
    particle.m_fLifeTime = RandRange( 0.05, 0.08 );

    glm::vec3 unitVec = glm::vec3(0, 0, 0);

    particle.m_Position = unitVec * 1.0f;
    particle.m_Velocity = unitVec * RandRange( 10, 20 );
}

void FireflyEffect1::RandomizeParticles()
{
    for ( unsigned int i = 0; i < m_Particles.size(); ++i )
    {
        RandomizeParticle(m_Particles[i]);
    }
}

void FireflyEffect1::EmitParticle( Particle& particle )
{
    assert( m_pParticleEmitter != NULL );
    m_pParticleEmitter->EmitParticle( particle );
}

void FireflyEffect1::EmitParticles()
{
    if ( m_pParticleEmitter == NULL )
    {
        RandomizeParticles();
    }
    else 
    {
        for ( unsigned int i = 0; i < m_Particles.size(); ++i )
        {
            EmitParticle(m_Particles[i]);
        }
    }
}

void FireflyEffect1::BuildVertexBuffer()
{
    const glm::vec3 X( 0.5, 0, 0 );
    const glm::vec3 Y( 0, 0.5, 0 );
    const glm::vec3 Z( 0, 0 , 1 );
    //std::cout << "caca" << std::endl;

    glm::quat cameraRotation;

    if ( m_pCamera != NULL )
    {
        cameraRotation = glm::quat( glm::radians(m_pCamera->GetRotation()) );    
    }

    // Make sure the vertex buffer has enough vertices to render the effect
    // If the vertex buffer is already the correct size, no change is made.
    m_VertexBuffer.resize(m_Particles.size() * 4, Vertex() );

    for ( unsigned int i = 0; i < m_Particles.size(); ++i )
    {
        Particle& particle = m_Particles[i];
        glm::quat rotation = glm::angleAxis( particle.m_fRotate, Z );

        unsigned int vertexIndex = i * 4;
        Vertex& v0 = m_VertexBuffer[vertexIndex + 0];   // Bottom-left
        Vertex& v1 = m_VertexBuffer[vertexIndex + 1];   // Bottom-right
        Vertex& v2 = m_VertexBuffer[vertexIndex + 2];   // Top-right
        Vertex& v3 = m_VertexBuffer[vertexIndex + 3];   // Top-left

        // Bottom-left
        v0.m_Pos = particle.m_Position + ( rotation * ( -X - Y ) * particle.m_fSize ) * cameraRotation;
        v0.m_Tex0 = glm::vec2( 0, 1 );
        v0.m_Diffuse = particle.m_Color;

        // Bottom-right
        v1.m_Pos = particle.m_Position + ( rotation * ( X - Y ) * particle.m_fSize ) * cameraRotation;
        v1.m_Tex0 = glm::vec2( 1, 1 );
        v1.m_Diffuse = particle.m_Color;

        // Top-right
        v2.m_Pos = particle.m_Position + ( rotation * ( X + Y ) * particle.m_fSize ) * cameraRotation;
        v2.m_Tex0 = glm::vec2( 1, 0 );
        v2.m_Diffuse = particle.m_Color;

        // Top-left
        v3.m_Pos = particle.m_Position + ( rotation * ( -X + Y ) * particle.m_fSize ) * cameraRotation;
        v3.m_Tex0 = glm::vec2( 0, 0 );
        v3.m_Diffuse = particle.m_Color;
    }
    
}

void FireflyEffect1::Update(float fDeltaTime)
{
    if (m_Particles.size() >= max_particle){
        m_Particles.erase(m_Particles.begin());
        //std::cout << m_Particles.size() << std::endl;
    }

    if (m_Particles.size() < max_particle)
    {
        for (int i = 0; i < 10; ++i)
            m_Particles.push_back(Particle());
    }


    for ( unsigned int i = 0; i < m_Particles.size(); ++i )
    {
        Particle& particle = m_Particles[i];
        particle.m_fAge += fDeltaTime;

        if ( particle.m_fAge > particle.m_fLifeTime )
        {
            if ( m_pParticleEmitter != NULL )
                EmitParticle(particle);
            else RandomizeParticle(particle);
        }

        else
        {
            float lifeRatio = (particle.m_fAge / particle.m_fLifeTime);
            particle.m_Velocity += ( m_Force * fDeltaTime );
            particle.m_Position += ( particle.m_Velocity * fDeltaTime );
            particle.m_Color = m_ColorInterpolator.GetValue( lifeRatio );
            particle.m_fRotate = glm::lerp<float>( 0.0f, particle.m_ClockRot * 5.0f, lifeRatio );
            particle.m_fSize = glm::lerp<float>( 0.7f, 0.f, lifeRatio );
        }
    }

    BuildVertexBuffer();
}

void FireflyEffect1::Render()
{
    glDisable(GL_DEPTH_TEST);           // Disables Depth Testing
    glEnable(GL_BLEND);                 // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);   // Type Of Blending To Perform
    glEnable(GL_TEXTURE_2D);            // Enable textures

    glPushMatrix();
    glMultMatrixf( glm::value_ptr(m_LocalToWorldMatrix) );
    
    glBindTexture( GL_TEXTURE_2D, m_TextureID );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Pos) );
    glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Tex0) );
    glColorPointer( 4, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Diffuse) );

    glDrawArrays( GL_QUADS, 0, m_VertexBuffer.size() );

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    glBindTexture( GL_TEXTURE_2D, 0 );

    glPopMatrix();

}

void FireflyEffect1::Resize( unsigned int numParticles )
{
    m_Particles.resize( numParticles,  Particle() );
    m_VertexBuffer.resize( numParticles * 4, Vertex() );
}
