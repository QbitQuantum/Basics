void Solido::resuelveColision(Solido *s) {
    Vector3D vn = s->getP() - this->getP();
    vn.normalize();
    Vector3D vv = s->getV();
    Vector3D vr = vv.reflect(vn);
    s->setV(vr);
}