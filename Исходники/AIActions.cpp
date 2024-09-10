AITackleAction::AITackleAction(const Player* p)
	: AIAction(mActionName, p)
{
	// action to tackle the ball/opponent currently holding the ball
	float maxdist = 3.0f;
	Vector3 tacklevec = p->getMatch()->getBall()->getPosition() +
		p->getMatch()->getBall()->getVelocity() * 0.5f -
		p->getPosition();
	float dist = tacklevec.length();
	mScore = -1.0f;
	if(dist < maxdist) {
		Player* nearestopp = MatchHelpers::nearestOppositePlayerToBall(*p->getTeam());
		if(nearestopp->standing()) {
			float oppdist = MatchEntity::distanceBetween(*p,
					*nearestopp);
			const float maxOppDist = 2.0f;
			if(oppdist < maxOppDist) {
				float distToOwnGoal = (MatchHelpers::ownGoalPosition(*p) -
						p->getMatch()->getBall()->getPosition()).length();
				if(distToOwnGoal > 10.0f && distToOwnGoal < 80.0f) {
					mScore = 1.0f - (oppdist / maxOppDist);
					mScore *= mPlayer->getTeam()->getAITacticParameters().TackleActionCoefficient;
				}
			}
		}
	}
	mAction = boost::shared_ptr<PlayerAction>(new TacklePA(tacklevec));
}