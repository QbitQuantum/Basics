void Shot::Use(CCPoint in_vector){
	mUsed = true;
	mVector = (in_vector.normalize()*SPEED);
}