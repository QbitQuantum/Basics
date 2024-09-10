Vector2d ComponentSteering::followLeader(GameObject* leader)
{
	Vector2d tv = leader->velocity;
	Vector2d force;
 
	// Calculate the behind point
	tv *= -1;
	tv.normalize();
	tv *= 10;

	Vector2d behindLeader = leader->position + tv;
 
	// Creates a force to arrive at the behind point
	force = force + arrive(behindLeader);

 
	return force;
}