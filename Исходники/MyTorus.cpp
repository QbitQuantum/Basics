void MyTorus::torusNormal(double phi, double theta, Vector3d &normal){
    Vector3d dT_dTheta (-(R+r*cos(phi))*sin(theta),(R+r*cos(phi))*cos(theta),0);
    Vector3d dT_dPhi (-r*sin(phi)*cos(theta),-r*sin(phi)*sin(theta),r*cos(phi));
    normal.cross(dT_dTheta,dT_dPhi);
    normal.normalize();

}