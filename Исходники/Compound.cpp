Vector3d Compound::PointOfReference::vectorFromPointAndNearVector(Compound::PointPtr point, Vector3d vector, int i) {
	if(i > 10 | vector.squaredNorm() > 10000 | vector != vector) {
		//std::cout << "Compound.cpp vector:\n" << vector << std::endl;
		//return vector;
		return Vector3d(0,0,0);
	}
	Vector3d v1 = point->getPosition()->getVector();
	//Vector3d v0 = point->getPosition()->getVector();
	//assert(v0 == v0);
	double epsilon = 0.00001;
	Manifold* space = point->getPosition()->getSpace();
	//std::cout << "Compound.cpp i:\t" << i << std::endl;
	Vector3d v0 = this->pointFromVector(vector)->getVector(space);
	Vector3d vx = this->pointFromVector(vector + Vector3d(epsilon,0,0))->getVector(space);
	Vector3d vy = this->pointFromVector(vector + Vector3d(0,epsilon,0))->getVector(space);
	Vector3d vz = this->pointFromVector(vector + Vector3d(0,0,epsilon))->getVector(space);
	assert(vz == vz);
	Matrix3d jacobean;
	jacobean << vx-v0,vy-v0,vz-v0;
	jacobean /= epsilon;
	/*std::cout << "getPosition()->getVector():\n" << getPosition()->getVector() << std::endl;
	std::cout << "vector:\n" << vector << std::endl;
	std::cout << "v0:\n" << v0 << std::endl;
	std::cout << "vx:\n" << vx << std::endl;
	std::cout << "vy:\n" << vy << std::endl;
	std::cout << "vz:\n" << vz << std::endl;*/
	//std::cout << "jacobean:\n" << jacobean << std::endl;
	Vector3d delta = jacobean.inverse()*(v1-v0);
	//std::cout << "v1-v0:\n" << v1-v0 << std::endl;
	//std::cout << "delta:\n" << delta << std::endl;
	if(delta != delta) {
		return Vector3d(0,0,0);
	}
	//std::cout << "delta.norm():\t" << delta.norm() << std::endl;
	double squaredNorm = delta.squaredNorm();
	double max = 5;
	if(squaredNorm > max*max) {
		delta = max*delta/sqrt(squaredNorm);
	}
	if(squaredNorm < EPSILON*EPSILON) {
		/*std::cout << "v1-v0:\n" << v1-v0 << std::endl;
		std::cout << "delta:\n" << delta << std::endl;
		std::cout << "vector:\n" << vector << std::endl;
		std::cout << "delta+vector:\n" << delta+vector << std::endl;
		std::cout << "pointOfReference->vectorFromPoint(point):\n" << pointOfReference->getGeodesic(point->getPosition())->getVector() << std::endl;*/
		assert(pointFromVector(delta+vector)->getPosition()->getSpace() == point->getPosition()->getSpace());
		assert((pointFromVector(delta+vector)->getPosition()->getVector() - point->getPosition()->getVector()).squaredNorm() < EPSILON);
		/*assert((pointOfReference->getSpace()->pointFromVector(pointOfReference, vector)->getVector() - point->getPosition()->getVector()).squaredNorm() < EPSILON);
		assert((this->pointFromVector(delta+vector)->getPosition()->getVector() - pointOfReference->getSpace()->pointFromVector(pointOfReference, vector)->getVector()).squaredNorm() < EPSILON);
		assert((delta+vector - pointOfReference->getSpace()->vectorFromPoint(pointOfReference, point->getPosition())).squaredNorm() < EPSILON);*/	//Only for portals that connect to themselves.
		//std::cout << "i:\t" << i << std::endl;
		return delta+vector;
	} else {
		return vectorFromPointAndNearVector(point, delta+vector, i+1);
	}
}