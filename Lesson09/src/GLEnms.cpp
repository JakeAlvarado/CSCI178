#include "GLEnms.h"
GLEnms::GLEnms()
{
    //ctor

    pos.x =0;    // Default position settings
    pos.y =0;
    pos.z =-5;

    eScale.x =1.0; // default scaling
    eScale.y =1.0;

    eRotate.x =0;  // default rotations
    eRotate.y =0;
    eRotate.z =0;

    framesX =7;   // number of columns in the sprite sheet
    framesY =2;   // number of rows in the spritesheet

    xMax =1.0/framesX;  // default image
    xMin=0;
    yMax=1.0/framesY;
    yMin=0;

    speed =0.01;  // moving speed
    action=STAND;     // set actions
    theta = 30 * PI/180.0;
    v = 35;
    t = 0;
    myTime->startTime = clock();
}

GLEnms::~GLEnms()
{
    //dtor

}

void GLEnms::drawEnemy()
{
    glPushMatrix();
    glTranslatef(pos.x,pos.y,pos.z);
    glRotatef(eRotate.x,1,0,0);
    glRotatef(eRotate.y,0,1,0);
    glRotatef(eRotate.z,0,0,1);

    glScalef(eScale.x,eScale.y,1.0);

     glBegin(GL_QUADS);
      glTexCoord2f(xMin,yMax);
      glVertex3f(-1,-1,0);

      glTexCoord2f(xMax,yMax);
      glVertex3f(1,-1,0);

      glTexCoord2f(xMax,yMin);
      glVertex3f(1,1,0);

      glTexCoord2f(xMin,yMin);
      glVertex3f(-1,1,0);

   glEnd();
   glPopMatrix();

}

void GLEnms::PlaceEnemy(vec3 p)
{
    pos.x =p.x;
    pos.y =p.y;
    pos.z =p.z;
}

void GLEnms::actions()
{
    switch(action)
    {
    case STAND:
        break;


    case WALKLEFT:
        if(clock() - myTime->startTime>30){
        xMin +=1.0/framesX;
        xMax +=1.0/framesX;

        yMin= 0.5;
        yMax=1.0;

         pos.x +=speed;

        myTime->startTime =clock();
        }
        break;

    case WALKRIGHT:
        if(clock() - myTime->startTime>30){
        xMin +=1.0/framesX;
        xMax +=1.0/framesX;

        yMin= 0.0;
        yMax=0.5;

        pos.x +=speed;
         myTime->startTime =clock();
        }
        break;
    case ROLLLEFT:
        if(clock() - myTime->startTime>30){

        xMin +=1.0/framesX;
        xMax +=1.0/framesX;

        yMin= 0.5;
        yMax=1.0;

        eRotate.z += (float)((rand()/RAND_MAX)) * 100;


        pos.x -= (v*t*cos(theta))/1500;
        pos.y += (v*t*sin(theta)-0.5*GRAVITY*t*t)/300;

        if(pos.y > -1.25)t+=0.3;
        else{t = 0; pos.y=-1.2;}

            myTime->startTime =clock();
        }
        break;

    case ROLLRIGHT:
        if(clock() - myTime->startTime>30){

        xMin +=1.0/framesX;
        xMax +=1.0/framesX;

        yMin= 0.0;
        yMax=0.5;

        eRotate.z -= (float)((rand()/(float)RAND_MAX)) * 100;


        pos.x += (v*t*cos(theta))/1500;
        pos.y += (v*t*sin(theta)-0.5*GRAVITY*t*t)/300;

        if(pos.y > -1.25)t+=0.3;
        else{t = 0; pos.y=-1.2;}

            myTime->startTime =clock();
        }
        break;

    }

}
