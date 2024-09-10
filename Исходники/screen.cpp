void Screen::CalculatePosition(Vector3D eye, Vector3D center, Vector3D up) {
	Vector3D f = (center - eye).Normalize();
	pos = eye + f;
	this->up = up.Normalize();
	right = Vector3D::VectorProduct(f, this->up).Normalize();
	if(DEBUG) std::cout << "Position: " << pos << "\nUp: " << this->up << "\nRight: " <<
			right << "\nHeight: " << plane_height << "\nWidth: " << plane_width << std::endl;
}