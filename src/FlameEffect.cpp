#include "ParticleSystemPCH.h"
#include "FlameEmitter.h"
#include "Camera.h"
#include "Random.h"
#include "FlameEffect.h"

FlameEffect::FlameEffect(unsigned int numParticles /* = 0 */)
: m_pCamera( NULL )
, m_pParticleEmitter( NULL )
, m_ColorInterpolator( glm::vec4(1) )
, m_LocalToWorldMatrix(1)
, m_TextureID(0)
, m_Force( 12, 60.81f, 0 )
, max_particle(1000)
{
  Resize(numParticles);
}

FlameEffect::~FlameEffect()
{
    if ( m_TextureID != 0 )
    {
        glDeleteTextures( 1, &m_TextureID );
        m_TextureID = 0;
    }
}

void FlameEffect::SetCamera( Camera* pCamera )
{
    m_pCamera = pCamera;
}

void FlameEffect::SetParticleEmitter( ParticleEmitter* pEmitter )
{
    m_pParticleEmitter = pEmitter;
}

void FlameEffect::SetColorInterplator( const ColorInterpolator& colors )
{
    m_ColorInterpolator = colors;
}

bool FlameEffect::LoadTexture( const std::string& fileName )
{
    if ( m_TextureID != 0 )
    {
        glDeleteTextures(1, &m_TextureID );
    }

    m_TextureID = SOIL_load_OGL_texture( fileName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS );

    return ( m_TextureID != 0 );
}

void FlameEffect::RandomizeParticle( Particle& particle )
{
    particle.m_fAge = 0.0f;
    particle.m_fLifeTime = RandRange( 0.05, 0.08 );

    glm::vec3 unitVec = RandFlameUnitVec();

    particle.m_Position = unitVec * 1.0f;
    particle.m_Velocity = unitVec * RandRange( 10, 20 );
}

void FlameEffect::RandomizeParticles()
{
    for ( unsigned int i = 0; i < m_Particles.size(); ++i )
    {
        RandomizeParticle(m_Particles[i]);
    }
}

void FlameEffect::EmitParticle( Particle& particle )
{
    assert( m_pParticleEmitter != NULL );
    m_pParticleEmitter->EmitParticle( particle );
}

void FlameEffect::EmitParticles()
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

void FlameEffect::BuildVertexBuffer()
{
    const glm::vec3 X( 0.5, 0, 0 );
    const glm::vec3 Y( 0, 0.5, 0 );
    const glm::vec3 Z( 0, 0 , 1 );

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

void FlameEffect::Update(float fDeltaTime)
{
	if (m_Particles.size() >= max_particle)
		m_Particles.erase(m_Particles.begin());

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

        float lifeRatio = (particle.m_fAge / particle.m_fLifeTime);
        particle.m_Velocity += ( m_Force * fDeltaTime );
        particle.m_Position += ( particle.m_Velocity * fDeltaTime );
        particle.m_Color = m_ColorInterpolator.GetValue( lifeRatio );
        particle.m_fRotate = glm::lerp<float>( 0.0f, 2.0f * particle.m_ClockRot, lifeRatio );
        //particle.m_fSize = glm::lerp<float>( 3.0f, 0.4f, lifeRatio );
        particle.m_fSize = glm::lerp<float>( 1.5f, 0.1f, lifeRatio );
    }

    BuildVertexBuffer();
}

void FlameEffect::Render()
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

void FlameEffect::Resize( unsigned int numParticles )
{
    m_Particles.resize( numParticles,  Particle() );
    m_VertexBuffer.resize( numParticles * 4, Vertex() );
}
