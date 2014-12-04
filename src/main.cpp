#include "ParticleSystemPCH.h"
#include "ElapsedTime.h"
#include "FlameEffect.h"
#include "FlameEmitter.h"
#include "SmokeEffect.h"
#include "SmokeEmitter.h"
#include "SparkEffect.h"
#include "SparkEmitter.h"
#include "Random.h"
#include "ExplosionSystem.h"
#include "CubeEmitter.h"
#include "FireflyEmitter.h"
#include "FireflyEffect.h"
#include "FireflyEmitter1.h"
#include "FireflyEffect1.h"
#include "FireflyEmitter2.h"
#include "FireflyEffect2.h" 

PivotCamera g_Camera;
CubeEmitter g_CubeEmitter;

// FIREFLY

FireflyEmitter g_FireflyEmitter;
FireflyEffect g_FireflyEffect(2);

FireflyEmitter1 g_FireflyEmitter1;
FireflyEffect1 g_FireflyEffect1(2);

FireflyEmitter2 g_FireflyEmitter2;
FireflyEffect2 g_FireflyEffect2(2);


// FIRE
FlameEmitter g_FlameEmitter;
SmokeEmitter g_SmokeEmitter;
SparkEmitter g_SparkEmitter;

FlameEffect g_FlameEffect(1);
SmokeEffect g_SmokeEffect(1);
SparkEffect g_SparkEffect(0);

ExplosionSystem ES = ExplosionSystem();

int effect = 0;

int g_iWindowWidth = 1280;
int g_iWindowHeight = 720;
int g_iGLUTWindowHandle = 0;
int g_iErrorCode = 0;

bool g_bLeftMouseDown = false;
bool g_bRightMouseDown = false;

bool g_bUpdate = true;

glm::vec2 g_MouseCurrent = glm::vec2(0);
glm::vec2 g_MousePrevious = glm::vec2(0);
glm::vec2 g_MouseDelta = glm::vec2(0);

glm::vec3 g_DefaultCameraTranslate(0, 0, 140);
glm::vec3 g_DefaultCameraRotate(30, 0, 0);
glm::vec3 g_DefaultCameraPivot(0, 0, 0);

void InitGL(int argc, char* argv[]);
void DisplayGL();
void IdleGL();
void SpecialKeysGL(int c, int x, int y);
void KeyboardGL(unsigned char c, int x, int y);
void MouseGL(int button, int state, int x, int y);
void MotionGL(int x, int y);
void ReshapeGL(int w, int h);

// FIREFLY
void setFirefly();
void setFirefly1();

// FIRE
void setFire();
void setFlames();
void setRoundSparks();
void setSmoke();

// We're exiting, cleanup the allocated resources.
void Cleanup();

int main(int argc, char* argv[])
{

    InitGL(argc, argv);

    if (argc == 2)
        effect = std::atoi(argv[1]);

    g_Camera.SetPivot(g_DefaultCameraPivot);
    g_Camera.SetTranslate(g_DefaultCameraTranslate);

    if (effect == 0)
    {
        g_Camera.SetRotate(g_DefaultCameraRotate);
        g_Camera.SetTranslate(glm::vec3(0, 0, 30));        
    }
    else if (effect == 1)
    {
        g_Camera.SetRotate(glm::vec3(-60, 0, 0));
        g_Camera.SetTranslate(glm::vec3(0, 0, 140));
    }

    else if (effect == 2)
    {
    	g_Camera.SetRotate(g_DefaultCameraRotate);
        g_Camera.SetTranslate(glm::vec3(0, 0, 30));
    }

    if (effect == 0)
        setFire();
    if (effect == 1)
        ES.setCamera(&g_Camera);
    if (effect == 2)
    	setFirefly();

    glutMainLoop();
}

// FIREFLY

void setFirefly()
{
	if (g_FireflyEffect.LoadTexture("./Textures/roundsparks/star.png"))
        std::cout << "Successfully loaded particle texture." << std::endl;

    else
        std::cerr << "Failed to load particle texture!" << std::endl;

    FireflyEffect::ColorInterpolator colors;

    colors.AddValue(0.0f, glm::vec4(0.274, 0.51, 0.705, 0.01));
    colors.AddValue(0.04f, glm::vec4(0.274, 0.51, 0.705, 0.1));
    colors.AddValue(0.6f, glm::vec4(0.69, 0.768, 0.87, 0.05));

    g_FireflyEffect.SetColorInterplator(colors);
    g_FireflyEffect.SetParticleEmitter(&g_FireflyEmitter);
    g_FireflyEffect.EmitParticles();
    g_FireflyEffect.SetCamera(&g_Camera);

    // ---------------------------------------------------

    if (g_FireflyEffect1.LoadTexture("./Textures/roundsparks/star.png"))
        std::cout << "Successfully loaded particle texture." << std::endl;

    else
        std::cerr << "Failed to load particle texture!" << std::endl;

    FireflyEffect1::ColorInterpolator colors1;

    colors1.AddValue(0.0f, glm::vec4(0.274, 0.51, 0.705, 0.01));
    colors1.AddValue(0.04f, glm::vec4(0.274, 0.51, 0.705, 0.1));
    colors1.AddValue(0.6f, glm::vec4(0.69, 0.768, 0.87, 0.05));

    g_FireflyEffect1.SetColorInterplator(colors1);
    g_FireflyEffect1.SetParticleEmitter(&g_FireflyEmitter1);
    g_FireflyEffect1.EmitParticles();
    g_FireflyEffect1.SetCamera(&g_Camera);

    // ----------------------------------------------------

    if (g_FireflyEffect2.LoadTexture("./Textures/roundsparks/star.png"))
        std::cout << "Successfully loaded particle texture." << std::endl;

    else
        std::cerr << "Failed to load particle texture!" << std::endl;

    FireflyEffect2::ColorInterpolator colors2;

    colors2.AddValue(0.0f, glm::vec4(0.274, 0.51, 0.705, 0.01));
    colors2.AddValue(0.04f, glm::vec4(0.274, 0.51, 0.705, 0.1));
    colors2.AddValue(0.6f, glm::vec4(0.69, 0.768, 0.87, 0.05));

    g_FireflyEffect2.SetColorInterplator(colors2);
    g_FireflyEffect2.SetParticleEmitter(&g_FireflyEmitter2);
    g_FireflyEffect2.EmitParticles();
    g_FireflyEffect2.SetCamera(&g_Camera);

}

// FIRE

void setFire()
{
    setFlames();
    setRoundSparks();
    setSmoke();
}

void setFlames()
{
    if (g_FlameEffect.LoadTexture("./Textures/fire/fire1.png"))
        std::cout << "Successfully loaded particle texture." << std::endl;

    else
        std::cerr << "Failed to load particle texture!" << std::endl;

    FlameEffect::ColorInterpolator colors;

    colors.AddValue(0.0f, glm::vec4(0.9, 0.9, 0.6, 0.05));
    colors.AddValue(0.04f, glm::vec4(0.9, 0.9, 0.3, 0.1));
    colors.AddValue(0.6f, glm::vec4(0.8, 0.2, 0.0, 0.2));

    g_FlameEffect.SetColorInterplator(colors);
    g_FlameEffect.SetParticleEmitter(&g_FlameEmitter);
    g_FlameEffect.EmitParticles();
    g_FlameEffect.SetCamera(&g_Camera);
}

void setRoundSparks()
{
    if (g_SparkEffect.LoadTexture("./Textures/roundsparks/roundspark.png"))
        std::cout << "Successfully loaded particle texture." << std::endl;

    else
        std::cerr << "Failed to load particle texture!" << std::endl;

    SparkEffect::ColorInterpolator sparkcolors;

    sparkcolors.AddValue(0.0f, glm::vec4(0.8, 0.2, 0.0, 0.5));
    sparkcolors.AddValue(0.05f, glm::vec4(0.8, 0.2, 0.0, 1));
    sparkcolors.AddValue(0.2f, glm::vec4(1, 0.2, 0, 0.5));

    g_SparkEffect.SetColorInterplator(sparkcolors);
    g_SparkEffect.SetParticleEmitter(&g_SparkEmitter);
    g_SparkEffect.EmitParticles();
    g_SparkEffect.SetCamera(&g_Camera);
}

void setSmoke()
{
    if (g_SmokeEffect.LoadTexture("./Textures/smoke/smoke5.png"))
        std::cout << "Successfully loaded particle texture." << std::endl;

    else
        std::cerr << "Failed to load particle texture!" << std::endl;

    SmokeEffect::ColorInterpolator smokecolors;

    smokecolors.AddValue(0.0f, glm::vec4(0.2, 0.2, 0.2, 0.005));
    smokecolors.AddValue(0.2f, glm::vec4(0.21, 0.21, 0.21, 0.4));
    smokecolors.AddValue(0.6f, glm::vec4(0.2, 0.2, 0.2, 0.6));

    g_SmokeEffect.SetColorInterplator(smokecolors);
    g_SmokeEffect.SetParticleEmitter(&g_SmokeEmitter);
    g_SmokeEffect.EmitParticles();
    g_SmokeEffect.SetCamera(&g_Camera);
}

void Cleanup()
{
    if (g_iGLUTWindowHandle != 0)
    {
        glutDestroyWindow(g_iGLUTWindowHandle);
        g_iGLUTWindowHandle = 0;
    }
}


void InitGL(int argc, char* argv[])
{
    std::cout << "Initialise OpenGL..." << std::endl;

    glutInit(&argc, argv);
    int iScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int iScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition((iScreenWidth - g_iWindowWidth) / 2,
        (iScreenHeight - g_iWindowHeight) / 2);
    glutInitWindowSize(g_iWindowWidth, g_iWindowHeight);

    g_iGLUTWindowHandle = glutCreateWindow("OpenGL");

    // Register GLUT callbacks
    glutDisplayFunc(DisplayGL);
    glutIdleFunc(IdleGL);
    glutMouseFunc(MouseGL);
    glutMotionFunc(MotionGL);
    glutSpecialFunc(SpecialKeysGL);
    glutKeyboardFunc(KeyboardGL);
    glutReshapeFunc(ReshapeGL);

    // Setup initial GL State
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    glShadeModel(GL_SMOOTH);

    std::cout << "Initialise OpenGL: Success!" << std::endl;
}

void DrawAxis(float fScale, glm::vec3 translate = glm::vec3(0))
{
    glPushAttrib(GL_ENABLE_BIT);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(translate.x, translate.y, translate.z);
    glScalef(fScale, fScale, fScale);

    glBegin(GL_LINES);
    {
        glColor3f(0.4f, 0.4f, 0.4f);
        glVertex3f(0.0f, 0.0f, 0.0);
        glVertex3f(1.0f, 0.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
    }
    glEnd();

    glPopMatrix();
    glPopAttrib();
}

void DisplayGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                   // Clear the color buffer, and the depth buffer.

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    g_Camera.ApplyViewTransform();

    //DrawAxis(20.0f, g_Camera.GetPivot()); 
    
    if (effect == 0)
    {
        g_FlameEffect.Render();
        g_SmokeEffect.Render();
        g_SparkEffect.Render();
    }
    if (effect == 1)
        ES.Render();
    if (effect == 2)
    {
    	g_FireflyEffect.Render();
    	g_FireflyEffect1.Render();
    	g_FireflyEffect2.Render();
    }

    glutSwapBuffers();
   	glutPostRedisplay();
}

void IdleGL()
{

    static ElapsedTime elapsedTime;
    float fDeltaTime = elapsedTime.GetElapsedTime();

    if (g_bUpdate)
    {
        if (effect == 0)
        {
            g_FlameEffect.Update(fDeltaTime);
            g_SmokeEffect.Update(fDeltaTime);
            g_SparkEffect.Update(fDeltaTime);
        }
        if (effect == 1)
            ES.Update(fDeltaTime);

        if (effect == 2)
        {
        	g_DefaultCameraRotate.y -= 0.5;
        	g_Camera.SetRotate(g_DefaultCameraRotate);
        	g_FireflyEffect.Update(fDeltaTime * 2);
        	g_FireflyEmitter.Update(fDeltaTime * 2);

        	g_FireflyEffect1.Update(fDeltaTime * 2);
        	g_FireflyEmitter1.Update(g_FireflyEmitter.getPos(), fDeltaTime * 2);

        	g_FireflyEffect2.Update(fDeltaTime * 2);
        	g_FireflyEmitter2.Update(g_FireflyEmitter.getPos(), fDeltaTime * 2);
        }
    }
    else 
    {
        if (effect == 0)
        {
            g_FlameEffect.BuildVertexBuffer();
            g_SmokeEffect.BuildVertexBuffer();
            g_SparkEffect.BuildVertexBuffer();
        }
        if (effect == 1)
            ES.BuildVertexBuffer();
        if (effect == 2)
        {
        	g_FireflyEffect.BuildVertexBuffer();
        	g_FireflyEffect1.BuildVertexBuffer();
        	g_FireflyEffect2.BuildVertexBuffer();
        }
    }

    glutPostRedisplay();
}

template< typename T >
void Increment(T& value, const T& step, const T& max)
{
    value = std::min(max, value + step);
}

template< typename T >
void Decrement(T& value, const T& step, const T& min)
{
    value = std::max(min, value - step);
}

void SpecialKeysGL(int c, int x, int y)
{
    const float fStep = 1.0f;
    switch (c)
    {
    case GLUT_KEY_UP:
        {
            Increment(g_CubeEmitter.MaxWidth, fStep, 100.0f);
            Increment(g_CubeEmitter.MaxHeight, fStep, 100.0f);
            Increment(g_CubeEmitter.MaxDepth, fStep, 100.0f);
            g_CubeEmitter.MinWidth = -g_CubeEmitter.MaxWidth;
            g_CubeEmitter.MinHeight= -g_CubeEmitter.MaxHeight;
            g_CubeEmitter.MinDepth = -g_CubeEmitter.MaxDepth;

            Increment(g_FlameEmitter.MinInclination, fStep, 180.0f);
            Decrement(g_FlameEmitter.MaxInclination, fStep, g_FlameEmitter.MinInclination);
        }
        break;
    case GLUT_KEY_DOWN:
        {
            Decrement(g_CubeEmitter.MaxWidth, fStep, 0.0f);
            Decrement(g_CubeEmitter.MaxHeight, fStep, 0.0f);
            Decrement(g_CubeEmitter.MaxDepth, fStep, 0.0f);

            g_CubeEmitter.MinWidth = -g_CubeEmitter.MaxWidth;
            g_CubeEmitter.MinHeight = -g_CubeEmitter.MaxHeight;
            g_CubeEmitter.MinDepth = -g_CubeEmitter.MaxDepth;

            Decrement(g_FlameEmitter.MinInclination, fStep, 0.0f);
            Increment(g_FlameEmitter.MaxInclination, fStep, 180.0f);
        }
        break;
    case GLUT_KEY_LEFT:
        {
            Increment(g_FlameEmitter.MinAzimuth, fStep, 360.0f);
            Decrement(g_FlameEmitter.MaxAzimuth, fStep, 0.0f);
        }
        break;
    case GLUT_KEY_RIGHT:
        {
            Decrement(g_FlameEmitter.MinAzimuth, fStep, 0.0f);
            Increment(g_FlameEmitter.MaxAzimuth , fStep, 360.0f);
        }
        break;
    };

    glutPostRedisplay();
}

void KeyboardGL(unsigned char c, int x, int y)
{
    float fRadiusStep = 1.0f;

    switch (c)
    {
    case ' ': // Space bar
        {
            // Toggle updating of the simulation
            g_bUpdate = !g_bUpdate;
        }
        break;
    case '-':
        {
            g_FlameEmitter.MaximumRadius -= fRadiusStep;
            g_FlameEmitter.MinimumRadius -= fRadiusStep;

            g_FlameEmitter.MaximumRadius = std::max(0.0f, g_FlameEmitter.MaximumRadius);
            g_FlameEmitter.MaximumRadius = std::max(0.0f, g_FlameEmitter.MaximumRadius);
        }
        break;
    case '+':
        {
            g_FlameEmitter.MaximumRadius += fRadiusStep;
            g_FlameEmitter.MinimumRadius += fRadiusStep;

            g_FlameEmitter.MaximumRadius = std::min(200.0f, g_FlameEmitter.MaximumRadius);
            g_FlameEmitter.MaximumRadius = std::min(200.0f, g_FlameEmitter.MaximumRadius);
        }
        break;
    case 's':
    case 'S':
        {
            std::cout << "Shade Model: GL_SMOOTH" << std::endl;
            // Switch to smooth shading model
            glShadeModel(GL_SMOOTH);
        }
        break;
    case 'f':
    case 'F':
        {
            std::cout << "Shade Model: GL_FLAT" << std::endl;
            // Switch to flat shading model
            glShadeModel(GL_FLAT);
        }
        break;
    case 'r':
    case 'R':
        {
            std::cout << "Reset Parameters..." << std::endl;
            g_Camera.SetTranslate(g_DefaultCameraTranslate);
            g_Camera.SetRotate(g_DefaultCameraRotate);
            g_Camera.SetPivot(g_DefaultCameraPivot);
        }
        break;
    case '\033': // escape quits
    case '\015': // Enter quits    
    case 'Q':    // Q quits
    case 'q':    // q (or escape) quits
        {
            // Cleanup up and quit
            exit(0);
        }
        break;
    }

    glutPostRedisplay();
}

void MouseGL(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        g_bLeftMouseDown = (state == GLUT_DOWN);
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        g_bRightMouseDown = (state == GLUT_DOWN);

     if (effect == 0)
        {  
            glm::vec3 newPos = glm::vec3(RandRange(-10, 10), RandRange(-10, 10), RandRange(-10, 10));
            g_FlameEmitter.setOrigin(newPos);
            g_SmokeEmitter.setOrigin(newPos);
            g_SparkEmitter.setOrigin(newPos);
            setFire();
        }
        else if (effect == 1 && g_bRightMouseDown)
        {
        	glm::vec3 newPos = glm::vec3(RandRange(-75, 75), RandRange(-20, 10), RandRange(-75, 75));
        	ES.addExplosion(newPos);
            ES.setExplosion();
		}
    }
    g_MousePrevious = glm::vec2(x, y);

}

void MotionGL(int x, int y)
{
    g_MouseCurrent = glm::vec2(x, y);
    g_MouseDelta = (g_MousePrevious - g_MouseCurrent);

    // Update the camera
    if (g_bLeftMouseDown && g_bRightMouseDown)
    {
        g_Camera.TranslateZ(g_MouseDelta.y);
    }
    else if (g_bLeftMouseDown)
    {
        g_Camera.AddPitch(-g_MouseDelta.y);
        g_Camera.AddYaw(-g_MouseDelta.x);
    }
    else if (g_bRightMouseDown)
    {
        g_Camera.TranslatePivotX(g_MouseDelta.x);
        g_Camera.TranslatePivotY(-g_MouseDelta.y);
    }    

    g_MousePrevious = g_MouseCurrent;
}

void ReshapeGL(int w, int h)
{
    std::cout << "ReshapGL(" << w << ", " << h << ");" << std::endl;

    h = std::max(h, 1);
    
    g_iWindowWidth = w;
    g_iWindowHeight = h;

    g_Camera.SetViewport(0, 0, w, h);
    g_Camera.ApplyViewport();

    g_Camera.SetProjection(60.0f, w/(float)h, 0.1f, 1000.0f);
    g_Camera.ApplyProjectionTransform();

    glutPostRedisplay();
}

