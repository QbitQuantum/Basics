ofVec3f BasicScreenObject::globalToLocalDir(ofVec3f _globaldir){
	ofMatrix4x4	local = getParent()->getGlobalTransformMatrix().getInverse();
	local.setTranslation(0, 0, 0);
	return _globaldir*local;	
}