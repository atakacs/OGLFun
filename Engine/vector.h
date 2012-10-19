/* vector.h
 * Part of the Saynoir project
 *
 * Cointains the declaration and defenition of the CVector
 * class used for holding matematical vector information.
 *
 * Authors: Alexander Takacs and David Keijser
 */
 
#ifndef __VECTOR_H
#define __VECTOR_H

#include <SDL/SDL_opengl.h>
#include <math.h>

//#define PI		(3.14159265359f)
#define DEG2RAD(a)	(PI/180*(a))
#define RAD2DEG(a)	(180/PI*(a))

typedef float scalar_t;

class CVector
{
public:
    scalar_t x;
    scalar_t y;
    scalar_t z;
    
    // Constructor
    CVector(scalar_t scXValue = 0, scalar_t scYValue = 0, scalar_t scZValue = 0)
    {
        x = scXValue;
        y = scYValue;
        z = scZValue;
    }
    
    // Copy constructor
    CVector(const CVector &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
    
    //Vector assignment
    const CVector& operator=(const CVector &vec)
    {
        x = vec.x;
        y = vec.y; // Corrected this
        z = vec.z;
        
        return *this;
    }
    
    //Vector equality comparishon
    const bool operator==(const CVector &vec) const
    {
        return((vec.x == x) && (vec.y == y) && (vec.z == z));
    }
    
    //Vector inequality comparishon
    const bool operator!=(const CVector &vec) const
    {
        return !(*this == vec);
    }
    
    //Vector addition
    const CVector operator+(const CVector &vec) const
    {
        return CVector(x + vec.x, y + vec.y, z + vec.z);
    }
    
    //Vector addition
    const CVector operator+() const
    {
        return CVector(*this);
    }
    
    //Vector increment
    const CVector& operator+=(const CVector &vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        
        return *this;
    }
    
    //Vector dectement
    const CVector operator-(const CVector &vec) const
    {
        return CVector(x - vec.x, y - vec.y, z - vec.z);
    }
    
    //Vector negation
    const CVector operator-() const
    {
        return CVector(-x, -y, -z);
    }
    
    //Vector decrement
    const CVector& operator-=(const CVector &vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        
        return *this;
    }
    
    //Scalar multiplication
    const CVector& operator*=(const scalar_t &s)
    {
        x *= s;
        y *= s;
        z *= s;
    
        return *this;
    }
    
    //Scalar divisision
    const CVector& operator/=(const scalar_t &s)
    {
        const scalar_t f = 1/s;
        
        x *= f;
        y *= f;
        z *= f;
    
        return *this;
    }
    
    //Post multiplication by scalar
    const CVector operator*(const scalar_t &s) const
    {
        return CVector(x*s, y*s, z*s);
    }
    
    //Pre multiplication by scalar
    friend inline const CVector operator*(const scalar_t &s, const CVector &vec)
    {
        return vec*s;
    }
    
    //Divide by scalar
    const CVector operator/(const scalar_t &s) const
    {
        const scalar_t f = 1/s;
        
        return CVector(x*f, y*f, z*f);
    }
    
    //Cross product
    const CVector CrossProduct(const CVector &vec) const
    {
        return CVector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
    }
    
    //Cross product
    const CVector operator^(const CVector &vec) const
    {
    	return CrossProduct(vec);
        //return CVector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
    }
    
    //Dot product
    const scalar_t DotProduct(const CVector &vec) const
    {
        return x*vec.x + y*vec.y + z*vec.z;
    }
    
    //Dot product
    const scalar_t operator%(const CVector &vec) const
    {
        return x*vec.x + y*vec.y + z*vec.z;
    }
    
    //Vector length
    const scalar_t Length() const
    {
        return (scalar_t)sqrt((double)(x*x + y*y + z*z));
    }
    
    //Return the unit vector
    const CVector UnitVector() const
    {
        return (*this) / Length();
    }
    
    //Normalize vector
    void Normalize()
    {
        (*this) /= Length();
    }
    
    //Length operator
    const scalar_t operator!() const
    {
        return sqrtf(x*x + y*y + z*z);
    }
    
    //Return vector with the specified length
    const CVector operator|(const scalar_t scLength) const
    {
        return (*this) * (scLength / !(*this));
    }
    
    //Set length of vector equal to length
    const CVector operator|=(const scalar_t scLength)
    {
        return (*this) = (*this) | scLength;
    }
    
    //Return angle between this vector and normal vector
    const inline float Angle(const CVector &normal) const
    {
        return acosf(*this % normal); //return arccos
    }
    
    //Reflect this vector about a normal vector
    const inline CVector Reflection(const CVector &normal) const
    {
        const CVector vec(*this | 1); //get unit vector
        return (vec  - normal * 2.0 * (vec % normal)) * !*this;
    }
};    //end of CVector


typedef CVector Vector;

void CalculateNormal(CVector *p1, CVector *p2, CVector *p3, CVector *vNormal);
void CalculateNormal(CVector *p1, CVector *p2, CVector *p3);

#endif
    
    
