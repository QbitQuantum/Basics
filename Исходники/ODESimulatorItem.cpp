void ODEBody::alignToZAxisIn2Dmode()
{
    static const Quat r(AngleAxis(PI / 2.0, Vector3(1.0, 0.0, 0.0)));

    dBodyID& bodyID = odeLinks.front()->bodyID;

    const dReal* q0 = dBodyGetQuaternion(bodyID);
    Quat q(q0[0], q0[1], q0[2], q0[3]);
    Quat q2 = r * q;
    q2.x() = 0.0;
    q2.z() = 0.0;
    q2.normalize();
    Quat q3 = r.inverse() * q2;
    dReal q4[4];
    q4[0] = q3.w();
    q4[1] = q3.x();    
    q4[2] = q3.y();    
    q4[3] = q3.z();    
    dBodySetQuaternion(bodyID, q4);

    const dReal* w = dBodyGetAngularVel(bodyID);
    dBodySetAngularVel(bodyID, 0, 0, w[2]);
}