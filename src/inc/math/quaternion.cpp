#include "../../impl/math/quaternion.h"

using namespace std;

Quaternion::Quaternion(float w, float x, float y, float z)
    : w(w), x(x), y(y), z(z) {}

Quaternion Quaternion::fromRotationXY(float pitchDeg, float yawDeg) {
    float halfPitch = pitchDeg * (M_PI / 360.0f);
    float halfYaw   = yawDeg * (M_PI / 360.0f);

    float sp = sin(halfPitch);
    float cp = cos(halfPitch);
    float sy = sin(halfYaw);
    float cy = cos(halfYaw);

    return Quaternion(
        cp * cy,
        sp * cy,
        cp * sy,
        -sp * sy
    );
}

Quaternion Quaternion::fromRotationYX(float yawDeg, float pitchDeg) {
    float halfPitch = pitchDeg * (M_PI / 360.0f);
    float halfYaw   = yawDeg * (M_PI / 360.0f);

    float sp = sin(halfPitch);
    float cp = cos(halfPitch);
    float sy = sin(halfYaw);
    float cy = cos(halfYaw);

    return Quaternion(
        cp * cy,
        cp * sy,
        sp * cy,
        -sp * sy
    );
}

Quaternion Quaternion::mul(const Quaternion& q) const {
    return Quaternion(
        w * q.w - x * q.x - y * q.y - z * q.z,
        w * q.x + x * q.w + y * q.z - z * q.y,
        w * q.y - x * q.z + y * q.w + z * q.x,
        w * q.z + x * q.y - y * q.x + z * q.w
    );
}

Quaternion Quaternion::norm() const {
    float len = sqrt(w * w + x * x + y * y + z * z);
    return Quaternion(w / len, x / len, y / len, z / len);
}

Quaternion Quaternion::inv() const {
    return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::operator*(const Quaternion& q) const {
    return mul(q);
}
