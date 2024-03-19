#ifndef GLPLAYER_H
#define GLPLAYER_H

#include<common.h>
#include<GLTexture.h>
#include<GLTimer.h>

class GLPlayer
{
    public:
        GLPlayer();
        virtual ~GLPlayer();

        enum {STAND, WALKLEFT,WALKRIGHT, RUN, JUMP, ATTACK};

        GLTexture *texture = new GLTexture();
        GLTimer   *myTime = new GLTimer();

        void initPlayer(int,int,char* fileName); // number of x, y frames
        void drawPlayer();
        void actions();

        vec3 plPosition;
        vec3 plScale;

        vec3 vert[4];
        float xMax,xMin,yMax,yMin;
        int framesX,framesY;

        int actionTrigger;  // for load actions

    protected:

    private:
};

#endif // GLPLAYER_H
