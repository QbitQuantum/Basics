Boid::Boid(ofVec3f pos, ofVec3f vel, radomeModel* pMod) {
    position = pos;
    velocity = vel;
    velocity = vel.normalize();
    acceleration = ofVec3f(0,0,0);
    
	neighborPosition = ofVec3f(0,0,0);
	numNeighbors = 0;
    
	decay = 0.99;
	crowdFactor	= 1.0;
    speedRange = ofVec2f(ofRandom(1.0, 1.5), ofRandom(2.5, 4.0));
    speedRangeSquared = ofVec2f(speedRange[0] * speedRange[0], speedRange[1] * speedRange[1]);
    
    pModel = pMod;
}