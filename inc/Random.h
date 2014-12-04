// Generate a random number between [0..1)
inline float Random()
{
    return rand() / (float)RAND_MAX;
}

inline float RandRange( float fMin, float fMax )
{
    if ( fMin > fMax ) std::swap( fMin, fMax );
    return ( Random() * ( fMax - fMin ) ) + fMin;
}

inline glm::vec3 RandFlameUnitVec()
{
    float x = RandRange(-0.8f,0.8f); //( Random() * 2.0f ) - 1.0f;
    float y = RandRange(5.0f,7.0f);//( Random() * 2.0f ) - 1.0f;
    float z = RandRange(-0.8f,0.8f);//( Random() * 2.0f ) - 1.0f;

    return glm::vec3(x, y, z);
}

inline glm::vec3 RandSmokeUnitVec()
{
    float x = RandRange(-0.5f, 0.5f); //( Random() * 2.0f ) - 1.0f;
    float y = RandRange(2.0f,3.0f);//( Random() * 2.0f ) - 1.0f;
    float z = RandRange(-0.5f, 0.5f);//( Random() * 2.0f ) - 1.0f;

    return glm::vec3(x, y, z);
}


inline glm::vec3 RandSparkUnitVec()
{
    float x = RandRange(-0.5f, 0.5f); //( Random() * 2.0f ) - 1.0f;
    float y = RandRange(2.0f,3.0f);//( Random() * 2.0f ) - 1.0f;
    float z = RandRange(-0.5f, 0.5f);//( Random() * 2.0f ) - 1.0f;

    return glm::vec3(x, y, z);
}

inline glm::vec3 RandMistUnitVec()
{
    float x = RandRange(-35.5f, 35.5f); //( Random() * 2.0f ) - 1.0f;
    float y = RandRange(-35.5f,35.5f);//( Random() * 2.0f ) - 1.0f;
    float z = RandRange(-35.5f, 35.5f);//( Random() * 2.0f ) - 1.0f;

    return (glm::normalize(glm::vec3(x, y, z)) * glm::vec3(-35.0f, -35.0f, -35.0f));
}

inline glm::vec3 RandBurstUnitVec()
{
    float x = RandRange(-55.5f, 55.5f); //( Random() * 2.0f ) - 1.0f;
    float y = RandRange(-55.5f, 55.5f);//( Random() * 2.0f ) - 1.0f;
    float z = RandRange(-55.5f, 55.5f);//( Random() * 2.0f ) - 1.0f;

    return glm::normalize(glm::vec3(x, y, z));
}

inline glm::vec3 RandShockwaveUnitVec()
{
    float x = RandRange(0.f, 0.f); //( Random() * 2.0f ) - 1.0f;
    float y = RandRange(0.f, 0.f);//( Random() * 2.0f ) - 1.0f;
    float z = RandRange(0.f, 0.f);//( Random() * 2.0f ) - 1.0f;

    return glm::vec3(x, y, z);
}

inline glm::vec3 RandFlashUnitVec()
{
    float x = RandRange(0.f, 0.f); //( Random() * 2.0f ) - 1.0f;
    float y = RandRange(0.f, 0.f);//( Random() * 2.0f ) - 1.0f;
    float z = RandRange(0.f, 0.f);//( Random() * 2.0f ) - 1.0f;

    return glm::vec3(x, y, z);
}

inline glm::vec3 RandTrailUnitVec()
{
    float x = RandRange(-40.f, 40.f); //( Random() * 2.0f ) - 1.0f;
    float y = RandRange(-40.f, 40.f);//( Random() * 2.0f ) - 1.0f;
    float z = RandRange(-40.f, 40.f);//( Random() * 2.0f ) - 1.0f;

    return glm::normalize(glm::vec3(x, y, z));
}

inline glm::vec3 RandExplosionSparksUnitVec()
{
    float x = RandRange(0.f, 0.f); //( Random() * 2.0f ) - 1.0f;
    float y = RandRange(0.f, 0.f);//( Random() * 2.0f ) - 1.0f;
    float z = RandRange(0.f, 0.f);//( Random() * 2.0f ) - 1.0f;

    return glm::vec3(x, y, z);
}

inline glm::vec3 RandDebrisUnitVec()
{
    float x = RandRange(-45.f, 45.f); //( Random() * 2.0f ) - 1.0f;
    float y = RandRange(-45.f, 45.f);//( Random() * 2.0f ) - 1.0f;
    float z = RandRange(-45.f, 45.f);//( Random() * 2.0f ) - 1.0f;

    return glm::vec3(x, y, z);
}

inline glm::vec3 RandomNewForce()
{
    float x = RandRange(-45.f, 45.f); //( Random() * 2.0f ) - 1.0f;
    float y = RandRange(-45.f, 45.f);//( Random() * 2.0f ) - 1.0f;
    float z = RandRange(-45.f, 45.f);//( Random() * 2.0f ) - 1.0f;

    float speed = RandRange(50000, 100000);

    return (glm::normalize(glm::vec3(x, y, z)) * speed * 2.f);
}