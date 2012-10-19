/* vector.cpp
 * Part of the Saynoir project
 *
 * Defines vector-calculation functions.
 *
 * Authors: David Keijser and Alexander Takács
 */

#include "vector.h" 

/* Function CalculateNormal()
 * Calculate and return a face/plane normal */
void CalculateNormal(CVector *p1, CVector *p2, CVector *p3, CVector *vNormal)
{
    CVector a, b;
    
    a = *p1 - *p2;  
    b = *p1 - *p3;
    
    // ?product
    /*
    vResult.x = (a.y * b.z - b.y * a.z);
    vResult.y = (b.x * a.z - a.x * b.z);
    vResult.z = (a.x * b.y - b.x * a.y);
    */
    
    // Return result (non-unit length)
    *vNormal = a ^ b;

}

void CalculateNormal(CVector *p1, CVector *p2, CVector *p3)
{
    CVector a, b, vResult;
    float fLength;
    
    a = *p1 - *p2;  
    b = *p1 - *p3;
    
    vResult = a ^ b;

    //calculate the length of the normal
    fLength = vResult.Length();
    
    //normalize and speciefy the normal
    glNormal3f(vResult.x/fLength, vResult.y/fLength, vResult.z/fLength);
}
