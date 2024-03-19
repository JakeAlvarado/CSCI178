#include "GLCheckCollision.h"

GLCheckCollision::GLCheckCollision()
{
    //ctor
}

GLCheckCollision::~GLCheckCollision()
{
    //dtor
}

bool GLCheckCollision::isLinearCollision(vec2, vec2)
{

}

bool GLCheckCollision::isRadialCollision(vec3 p1, vec3 p2, float r1, float r2, float threshold)  // position 1, position 2, radius 1, radius 2
{
    return sqrt(pow((p1.x - p2.x ), 2) + pow((p1.y - p2.y), 2)) - (r1+r2) < threshold;
}

bool GLCheckCollision::isHitPlane(vec2, vec2)
{

}

bool GLCheckCollision::isCubicCollision(vec3, vec3)
{

}

bool GLCheckCollision::isSphereCollision(vec3 p1, vec3 p2, float r1, float r2, float threshold)
{
    return abs(sqrt((pow((p1.x - p2.x ), 2) + pow((p1.y - p2.y), 2) + pow((p1.z - p2.z), 2))) - (r1+r2)) > threshold;
}

bool GLCheckCollision::isHitPlane3D(vec3, vec3)
{

}
