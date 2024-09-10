bool ViewInfo::isOblique() {
    int i;
    double d = 0.0;
    for (i=0; i<3; i++) {
	d += (fabs(m2p[0][i]*m2p[1][i]) + fabs(m2p[0][i]*m2p[2][i]) + fabs(m2p[1][i]*m2p[2][i]));
    }
    if(fabs(d) < 1.0e-4) return false;
    else return true;
}