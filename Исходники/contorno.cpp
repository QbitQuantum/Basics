bool Contorno::colision(Nave *s) {
    Vector3D pe = s->getP();
    float re = s->getR();
    Vector3D vd = pe - p;
    float l = vd.length();
    return l < r + re;
}