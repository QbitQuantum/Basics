void UniformScaler::scale(WFMath::MTRand& rnd, const WFMath::Point<2>& pos, Ogre::Vector2& scale)
{
	scale.x = scale.y = mMin + rnd.rand(mRange);
}