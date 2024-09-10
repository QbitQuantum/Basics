Vector Ant::getClimbMountainForce(){

    Vector normal = GridManager::interpolateNormal(AgentManager::getFace(agentID), position);
	if(normal.x==0 && normal.y==0) // tangent plane is a horizontal plane
	{
		return Vector(0,0,0);
	}
	if(normal.y == 0)
	{
		Vector tangent = Vector(0,1,0)
	}
	else
	{
		float a = -(normal.x/normal.y);
		Vector tangent = Vector(1,a,0);
	}
	Vector steepest = normal.cross(tangent) / normal.cross(tangent).magnitude();
	// z component must be between -1 and 1
	if(steepest.z < 0)
		steepest = steepest * -1;
	// z component between 0 and 1, the closer to 1, the harder it should be to get up
	steepest = steepest * 5* pow(steepest.z -1,2);
	return steepest;
}