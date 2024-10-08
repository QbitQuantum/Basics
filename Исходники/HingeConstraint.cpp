void HingeConstraint::update(){

    Quat qA = m_connA->m_quaternion;
    Quat qB = m_connB->m_quaternion;

    // Local vector in A that is orthogonal to its pivot
    Vec3 nA_local = m_localAnchorA.cross(m_localPivotA);
    Vec3 nB_local = m_localAnchorB.cross(m_localPivotB);
    nA_local.normalize();
    nB_local.normalize();

    // Compute world vectors
    Vec3 pivotA = qA.multiplyVector(m_localPivotA);
    Vec3 pivotB = qB.multiplyVector(m_localPivotB);
    Vec3 anchorA = qA.multiplyVector(m_localAnchorA);
    Vec3 anchorB = qB.multiplyVector(m_localAnchorB);
    Vec3 nA = qA.multiplyVector(nA_local);
    Vec3 nB = qB.multiplyVector(nB_local);

    // g1 = pivotA.dot(nB)
    // g2 = pivotA.dot(anchorB)
    m_equationA.setViolation(pivotA.dot(nB));
    m_equationB.setViolation(pivotA.dot(anchorB));

    Vec3 zero(0,0,0);
    Vec3 pivotA_x_nB =      pivotA.cross(nB);
    Vec3 pivotA_x_anchorB = pivotA.cross(anchorB);
    m_equationA.setG(zero, pivotA_x_nB, zero, pivotA_x_nB*(-1));
    m_equationB.setG(zero, pivotA_x_anchorB, zero, pivotA_x_anchorB*(-1));

    BallJointConstraint::update();
}