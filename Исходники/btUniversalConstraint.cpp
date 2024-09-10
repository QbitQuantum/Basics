// constructor
// anchor, axis1 and axis2 are in world coordinate system
// axis1 must be orthogonal to axis2
btUniversalConstraint::btUniversalConstraint(btRigidBody& rbA, btRigidBody& rbB, btVector3& anchor, btVector3& axis1, btVector3& axis2)
: btGeneric6DofConstraint(rbA, rbB, btTransform::getIdentity(), btTransform::getIdentity(), true),
 m_anchor(anchor),
 m_axis1(axis1),
 m_axis2(axis2)
{
    // build frame basis
    // 6DOF constraint uses Euler angles and to define limits
    // it is assumed that rotational order is :
    // Z - first, allowed limits are (-PI,PI);
    // new position of Y - second (allowed limits are (-PI/2 + epsilon, PI/2 - epsilon), where epsilon is a small positive number
    // used to prevent constraint from instability on poles;
    // new position of X, allowed limits are (-PI,PI);
    // So to simulate ODE Universal joint we should use parent axis as Z, child axis as Y and limit all other DOFs
    // Build the frame in world coordinate system first
    btVector3 zAxis = axis1.normalize();
    btVector3 yAxis = axis2.normalize();
    btVector3 xAxis = yAxis.cross(zAxis); // we want right coordinate system
    btTransform frameInW;
    frameInW.setIdentity();
    frameInW.getBasis().setValue(    xAxis[0], yAxis[0], zAxis[0],
                                    xAxis[1], yAxis[1], zAxis[1],
                                    xAxis[2], yAxis[2], zAxis[2]);
    frameInW.setOrigin(anchor);
    // now get constraint frame in local coordinate systems
    m_frameInA = rbA.getCenterOfMassTransform().inverse() * frameInW;
    m_frameInB = rbB.getCenterOfMassTransform().inverse() * frameInW;
    // sei limits
    setLinearLowerLimit(btVector3(0., 0., 0.));
    setLinearUpperLimit(btVector3(0., 0., 0.));
    setAngularLowerLimit(btVector3(0.f, -SIMD_HALF_PI + UNIV_EPS, -SIMD_PI + UNIV_EPS));
    setAngularUpperLimit(btVector3(0.f,  SIMD_HALF_PI - UNIV_EPS,  SIMD_PI - UNIV_EPS));
}