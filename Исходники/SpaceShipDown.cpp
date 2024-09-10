Vec3 EnemyVehicle::steerToEvadeAllOtherEnemies (void) {
	// sum up weighted evasion
	Vec3 evade (0, 0, 0);
	for (int i = 0; i < g_EnemyVehicles.size(); i++) {
		const EnemyVehicle& e = *g_EnemyVehicles[i];
		if (position() != e.position()) {
			
			const Vec3 eOffset = e.position() - position();
			const float eDistance = eOffset.length();
			
			// xxx maybe this should take into account e's heading? xxx
			const float timeEstimate = 2.0 * eDistance / e.speed(); //xxx
			const Vec3 eFuture = e.predictFuturePosition (timeEstimate);
			
			// steering to flee from eFuture (enemy's future position)
			const Vec3 flee = xxxsteerForFlee (eFuture);
			
			//const float eForwardDistance = forward().dot (eOffset);
			//const float behindThreshold = radius() * -50.0;
			
			const float distanceWeight = 0.1; //1 / eDistance;
			const float forwardWeight = 1.0; //((eForwardDistance > behindThreshold) ? 1.0f : 0.5f);
			
			const Vec3 adjustedFlee = flee * distanceWeight * forwardWeight;
			
			evade += adjustedFlee;
		}
	}
	return evade;
}