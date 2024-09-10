// Cohesion
// For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
ADDAC_PVector ADDAC_Boid::cohesion(ADDAC_Boid boids[4]) {
    float neighbordist = cohesionV;
    ADDAC_PVector sum;   // Start with empty vector to accumulate all locations
    int count = 0;
    for (int i = 0 ; i < 4; i++) {
		ADDAC_Boid other = boids[i];
		float d = dist(pos, other.pos);
		if ((d > 0) && (d < neighbordist)) {
			// Add location
            sum.add(other.pos);
			count++;
		}
    }
    if (count > 0) {
		sum.div((float)count);
		return steer(sum, false);  // Steer towards the location
    }
    return sum;
}