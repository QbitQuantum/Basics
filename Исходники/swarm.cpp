void updateSwarmWithSignedDistance(int distanceID, float fDeltaTime, float sdInfluence)
{
	// update the signed distance function based on the time passed.
	updateSD(distanceID, fDeltaTime);

	for (int i = 0; i < NUM_TRIANGLES; i++)
	{
		// update direction based on destination point
		float destDirection[3];
		destDirection[0] = tris.moveToPoint[i][0] - tris.position[i][0];
		destDirection[1] = tris.moveToPoint[i][1] - tris.position[i][1];
		destDirection[2] = tris.moveToPoint[i][2] - tris.position[i][2];
		// normalize the length to where we go so that the speed is fixed.
		normalize(destDirection, 3);
		slerp(tris.direction[i], destDirection, tris.direction[i], 3, 1.8f * fDeltaTime);
		reNormal(tris.normal[i], tris.direction[i], 3);

		// update normal based on signed distance
		float signedDist = getSD(tris.position[i], distanceID);
		getSDNormal(tris.position[i], destDirection, distanceID);
		float t = 1.0f - fabsf(signedDist);
		t = t < 0.0f ? 0.0f : t;
		t = t > 1.0f ? 1.0f : t;
		slerp(tris.normal[i], destDirection, tris.normal[i], 3, t * sdInfluence);
		reNormal(tris.direction[i], tris.normal[i], 3);
	}
}