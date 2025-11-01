#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>

class Quaternion {
public:
    const float w, x, y, z;

    Quaternion(float, float, float, float);

    static Quaternion fromRotationXY(float, float);
    static Quaternion fromRotationYX(float, float);

    Quaternion mul(const Quaternion&) const;
    Quaternion norm() const;
    Quaternion inv() const;

    Quaternion operator*(const Quaternion&) const;
};

#endif // QUATERNION_H