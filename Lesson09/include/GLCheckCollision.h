#ifndef GLCHECKCOLLISION_H
#define GLCHECKCOLLISION_H

#include <common.h>

class GLCheckCollision
{
    public:
        GLCheckCollision();
        virtual ~GLCheckCollision();

        bool isLinearCollision(vec2, vec2);               // check z, z1, or y, y1 components
        bool isRadialCollision(vec3, vec3, float, float, float);   // elements 1, element 2, radius  1, radius 2
        bool isHitPlane(vec2, vec2);                        // check object vs floor/wall

        bool isCubicCollision(vec3, vec3);               // check x, y, z components of two models
        bool isSphereCollision(vec3, vec3, float, float, float);   // elements 1, element 2, radius  1, radius 2
        bool isHitPlane3D(vec3, vec3);                        // check object vs floor/wall

    protected:

    private:
};

#endif // GLCHECKCOLLISION_H
