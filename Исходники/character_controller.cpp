// Returns the portion of 'direction' that is parallel to 'normal'
btVector3 CCharacterController::ParallelComponent(const btVector3& direction, const btVector3& normal)
{
	btScalar magnitude = direction.dot(normal);
	return normal * magnitude;
}