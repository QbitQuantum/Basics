void FixedJoint::setRestTransform(const Transform& _link1_X_link2)
{
    link1_X_link2 = _link1_X_link2;
    link2_X_link1 = _link1_X_link2.inverse();
}