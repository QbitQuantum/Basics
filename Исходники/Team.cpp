float Team::_getScoreOfPosition(const Ogre::Vector3& position)
{
	// Closer to opponent's goal
	float score = 9.f * fabs((position - mGoal->getCenter()).x) / (2 * Prm.HalfPitchWidth);

	// 距离控球队员的距离
	float best_dist = 8.f;
	float dist_to_ctrl = fabs(position.distance(getControllingPlayer()->getPosition()));

	if (dist_to_ctrl > best_dist)
	{
		score += 4.f * (best_dist / (1.1 * dist_to_ctrl));
	}
	else 
	{
		score += 4.f * (dist_to_ctrl / best_dist);
	}

	return score;
}