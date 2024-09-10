void Dart::setAttributes(position3D startPos, position3D destPos, float power) {
	this->x = startPos.x;
	this->y = startPos.y;
	this->z = startPos.z;

	this->destx = destPos.x;
	this->desty = destPos.y;
	this->destz = destPos.z;

	this->dx = (destx - x)/30;
	this->dy = (desty - y)/30;
	this->dz = (destz - z)/30;

	this->angleX = 0.0;
	this->angleY = 0.0;
	this->angleZ = 0.0;

	draw = false;
	flies = true;
	justHit = false;

	angleX = atanf(dx/dz)*radToDec;
	angleY = atanf(dy/dz)*radToDec;
}