void DirectionalAtom::setA(const RotMat3x3d& a, int snapshotNo) {
    ((snapshotMan_->getSnapshot(snapshotNo))->*storage_).aMat[localIndex_] = a;
    ((snapshotMan_->getSnapshot(snapshotNo))->*storage_).unitVector[localIndex_] = a.inverse() * sU_.getColumn(2);    
}    