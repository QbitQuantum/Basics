void VRMolecule::rotateBond(int a, int b, float f) {
    if (atoms.count(a) == 0) return;
    if (atoms.count(b) == 0) return;
    VRAtom* A = atoms[a];
    VRAtom* B = atoms[b];

	uint now = VRGlobals::CURRENT_FRAME + rand();
    A->recFlag = now;

    Vec3d p1 = Vec3d( A->getTransformation()[3] );
    Vec3d p2 = Vec3d( B->getTransformation()[3] );
    Vec3d dir = p2-p1;
    Quaterniond q(dir, f);
    Matrix4d R;
    R.setRotate(q);

    Matrix4d T;
    T[3] = B->getTransformation()[3];
    Matrix4d _T;
    T.inverse(_T);
    T.mult(R);
    T.mult(_T);

    //cout << "ROTATE bound " << a << "-" << b << " around " << dir << " with " << f << endl;

    B->propagateTransformation(T, now);
    updateGeo();
}