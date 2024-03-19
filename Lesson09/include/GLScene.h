#ifndef GLSCENE_H
#define GLSCENE_H

#include <common.h>


class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();
        GLint initGL();
        GLint drawScene();
        GLvoid resizeScene(GLsizei, GLsizei);

        int windMsg(HWND,UINT,WPARAM,LPARAM);  // take windows inputs

        WPARAM wParam;                         // keyboard/Mouse msg

        float screenWidth;                     // get values from main window
        float screenHeight;                    // get Values from main window

    protected:

    private:
};

#endif // GLSCENE_H
