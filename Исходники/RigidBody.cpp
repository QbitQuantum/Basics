void RigidBody::setA(const RotMat3x3d& a) {
    ((snapshotMan_->getCurrentSnapshot())->*storage_).aMat[localIndex_] = a;
    ((snapshotMan_->getCurrentSnapshot())->*storage_).unitVector[localIndex_] = a.inverse() * sU_.getColumn(2);

    std::vector<Atom*>::iterator i;
    for (i = atoms_.begin(); i != atoms_.end(); ++i) {
        if ((*i)->isDirectional()) {
            (*i)->setA(a * (*i)->getA());
        }
    }
}    