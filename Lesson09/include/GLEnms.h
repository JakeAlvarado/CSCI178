#ifndef GLENMS_H
#define GLENMS_H

#include<common.h>
#include<GLTexture.h>
#include<GLTimer.h>

class GLEnms
{
    public:
        GLEnms();
        virtual ~GLEnms();

        void drawEnemy();
        void PlaceEnemy(vec3);
        void actions();

        bool isEnemyLive =true;

        enum{STAND, WALKLEFT, WALKRIGHT, ROLLLEFT, ROLLRIGHT, ATTACK}; //Actions for Enemy

        vec3 pos;
        vec2 eScale;
        vec3 eRotate;

        int framesX;
        int framesY;

        int action;
        float speed;
        float xMax,xMin,yMax,yMin;
        GLTimer   *myTime = new GLTimer();

        float t;
        float theta;
        int v;

    protected:

    private:
};

#endif // GLENMS_H
