void OctreeNode::calculateObjectsDistanceToCamera(Camera* camera){
	Object3DIterator it;
	for(it = this->objects.begin(); it != this->objects.end(); it++){
		Vec3* distVec = Vec3::subVectors(camera->getPosition(),(*it)->getPosition());
		(*it)->setDistanceToCamera(fabs(distVec->length()));
		delete distVec;
	}
}