bool LagomPlayerBase::CheckHover(const Ogre::Ray& ray)
{
	return ray.intersects( Ogre::Sphere(getIntFactory().ConstructionOffset, getIntFactory().ConstructingTriggerSize) ).first;
}