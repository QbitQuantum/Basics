Vec3f FNode::getTangent() {
    int Nout = out.size();
    int Nin = in.size();
    if (Nout == 0 && Nin == 0) return Vec3f(0,0,1);

    Vec3f t;
    //for (auto o : out) t += (o.second->transform->getFrom() - transform->getFrom());
    for (auto o : out) t += (o.second->transform->getWorldPosition() - transform->getWorldPosition());
    t.normalize();
    return t;
}