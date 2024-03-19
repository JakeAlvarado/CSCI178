#include "GLScene.h"
#include<GLLight.h>
#include<GLTexture.h>
#include<GLModel.h>
#include<GLInputs.h>
#include<GLParallax.h>
#include<GLPlayer.h>
#include<GLEnms.h>
#include<GLTimer.h>
#include<GLCheckCollision.h>

GLTexture *teapotTex = new GLTexture();  // texture object
GLModel *teaPotModel = new GLModel();    // model object
GLInputs *KbMs       = new GLInputs();   // keyboard and Mouse
GLParallax *plx      = new GLParallax(); // parallax

GLParallax *plx1      = new GLParallax(); // parallax
GLPlayer *pl          = new GLPlayer();   // Player class
GLEnms E[20];
GLTexture *enmsTex = new GLTexture();  // texture object
GLTimer *T = new GLTimer();
GLCheckCollision *hit = new GLCheckCollision();


GLScene::GLScene()
{
    //ctor

    screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH); // for smooth render
    glClearColor(0.0f,0.0f,0.0f,0.0f); // clear background to black
    glClearDepth(2.0f);            // depth test for layers
    glEnable(GL_DEPTH_TEST);       // activate depth test
    glDepthFunc(GL_LEQUAL);         // depth function type

    GLLight Light(GL_LIGHT0);
    Light.setLight(GL_LIGHT0);

    glEnable(GL_BLEND);             // Transparent effect of pngs
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);  //enable textures
    teapotTex->loadTexture("images/teapot.jpg");//load texture
    plx->parallaxInit("images/bak.jpg");
    plx1->parallaxInit("images/plx.png");
    pl->initPlayer(6,4,"images/player.png");
    pl->actionTrigger= pl->STAND;
    enmsTex->loadTexture("images/mon.png");

    for(int i=0; i<20; i++)
    {
        E[i].pos.x = (float)rand()/(float)RAND_MAX*5-2.5;
        E[i].pos.y = -1.2;

        E[i].pos.x<pl->plPosition.x?E[i].action = E[i].WALKRIGHT:E[i].action = E[i].WALKLEFT;

        E[i].eScale.x = E[i].eScale.y = (float)(rand()%12)/30.0;

    }

    T->startTime= clock();

    return true;
}

GLint GLScene::drawScene()    // this function runs on a loop
                              // DO NOT ABUSE ME
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// clear bits in each itterration
   glLoadIdentity();
   glColor3f(1.0,1.0,1.0);     //color the object red

   glPushMatrix(); //group object

     glScaled(3.33,3.33,1.0);
     glDisable(GL_LIGHTING);

     plx1->parallaxDraw(screenWidth,screenHeight);   // draw model obj
     plx->parallaxDraw(screenWidth,screenHeight);   // draw model obj
   //plx->parallaxScroll(true,"left", 0.01);      // parallax Auto mode
     glEnable(GL_LIGHTING);
   glPopMatrix();

   glPushMatrix();

   enmsTex->bindTexture();


   glDisable(GL_LIGHTING);
    for(int i=0; i<20; i++)
    {

       if(E[i].pos.x >3.5){E[i].action = E[i].WALKLEFT;E[i].speed =-0.01; E[i].pos.y = -1.2; E[i].eRotate.z = 0.0;}
       if(E[i].pos.x<-3.5){E[i].action = E[i].WALKRIGHT;E[i].speed =0.01; E[i].pos.y = -1.2; E[i].eRotate.z = 0.0;}

       if (hit->isRadialCollision(E[i].pos, pl->plPosition, 0.5, 0.5, 0.02))
        {
            if (pl->plPosition.x > E[i].pos.x && pl->actionTrigger==pl->WALKLEFT)
            {
                E[i].action = E[i].ROLLLEFT;
            }
            else if (pl->plPosition.x < E[i].pos.x && pl->actionTrigger==pl->WALKRIGHT)
            {
                E[i].action = E[i].ROLLRIGHT;
            }
        }

       E[i].drawEnemy();
       E[i].actions();
    }
    glEnable(GL_LIGHTING);

   glPopMatrix();

    glPushMatrix();
    glDisable(GL_LIGHTING);
    pl->drawPlayer();
    pl->actions();
    glEnable(GL_LIGHTING);
    glPopMatrix();


   return true;
}

GLvoid GLScene::resizeScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat)height; // keep track of the ratio
    glViewport(0,0,width,height); // adjusting the viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,aspectRatio,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)   // check for inputs
    {
    case WM_KEYDOWN:
         KbMs->wParam = wParam;
         KbMs->keyPress(teaPotModel,pl);
         KbMs->keyBackground(plx,0.005);
         KbMs->keyBackground(plx1,0.001);
         break;

    case WM_KEYUP:
         KbMs->wParam = wParam;
         KbMs->keyUP(pl);
         break;

    case WM_LBUTTONDOWN:
         KbMs->wParam = wParam;
         KbMs->mouseEventDown(teaPotModel,LOWORD(lParam),HIWORD(lParam));
         break;

    case WM_RBUTTONDOWN:
         KbMs->wParam = wParam;
         KbMs->mouseEventDown(teaPotModel,LOWORD(lParam),HIWORD(lParam));
         break;

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
        KbMs->mouseEventUp();
        break;

    case WM_MOUSEMOVE:
        KbMs->wParam = wParam;
        KbMs->mouseMove(teaPotModel,LOWORD(lParam),HIWORD(lParam));
         break;
    case WM_MOUSEWHEEL:

        KbMs->mouseWheel(teaPotModel, (double)GET_WHEEL_DELTA_WPARAM(wParam));
       break;
    }
}


