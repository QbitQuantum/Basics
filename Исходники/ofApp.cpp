//--------------------------------------------------------------
void rotateToNormal(ofVec3f normal) {
	normal.normalize();

	float rotationAmount;
	ofVec3f rotationAngle;
	ofQuaternion rotation;

	ofVec3f axis(0, 0, 1);
	rotation.makeRotate(axis, normal);
	rotation.getRotate(rotationAmount, rotationAngle);
	ofRotateDeg(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
}