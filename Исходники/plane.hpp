inline void Plane<N, T>::setNormalAndPoint(const VectorType& normal, const VectorType& point)
{
	this->normal = normal;
	dist = -(normal.dot(point));
}