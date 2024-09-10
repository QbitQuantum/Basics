/// Finds a random 2D point, within the specified region, that has no other objects within the requested radius, using an exising (already seeded) Mersenne Twister random number generator.
bool GridDatabase2D::randomPositionInRegionWithoutCollisions(const Util::AxisAlignedBox & region, SpatialDatabaseItemPtr item, bool excludeAgents, MTRand & randomNumberGenerator)
{
	Point ret(0.0f, 0.0f, 0.0f);
	bool notFoundYet;
	unsigned int numTries = 0;
	float radius = 0.0f;
	AgentInterface * ai;
	AgentInitialConditions aic;

	if ( item->isAgent() )
	{
		ai = dynamic_cast<AgentInterface*>(item);
		radius = ai->radius();
		aic = ai->getAgentConditions(ai);
	}
	float xspan = region.xmax - region.xmin - 2*radius;
	float zspan = region.zmax - region.zmin - 2*radius;

	do {

		ret.x = region.xmin + radius + ((float)randomNumberGenerator.rand(xspan));
		ret.y = 0.0f;
		ret.z = region.zmin + radius + ((float)randomNumberGenerator.rand(zspan));

		aic.position = ret;


		// assume this new point has no collisions, until we find out below
		notFoundYet = false;

		// check if ret collides with anything
		set<SpatialDatabaseItemPtr> neighbors;
		neighbors.clear();
		float _new_radius = radius;
		getItemsInRange(neighbors, ret.x - _new_radius, ret.x + _new_radius, ret.z - _new_radius, ret.z + _new_radius, NULL);
		set<SpatialDatabaseItemPtr>::iterator neighbor;
		for (size_t dirs=0; dirs < 10; dirs++)
		{
			float theta = randomNumberGenerator.rand() * M_2_PI;

			double directionX = cos(theta);
			double directionZ = sin(theta);
			aic.direction = Util::Vector(directionX, 0.0f, directionZ);

			ai->reset(aic, ai->getSimulationEngine());
			ai->disable();

			/*
			 * increment must be after loop body or (*neighbor)->isAgent()) will be called on an
			 * element that is beyond the set.
			 */
			for (neighbor = neighbors.begin(); neighbor != neighbors.end(); neighbor++)
			{
				if ((excludeAgents) && ((*neighbor)->isAgent()))
				{
					continue;
				}
				notFoundYet = (*neighbor)->overlaps(ret, radius) ||  ai->overlaps((*neighbor));
				if (notFoundYet)
				{
					std::cout << "Try again placing agent: " << std::endl;
					break;
				}

			}
			if (notFoundYet)
			{ // no intersections
				break;
			}

		}// dirs

		numTries++;
		if (numTries > 1000)
		{
			cerr << "ERROR: trying too hard to find a random position in region.  The region is probably already too dense." << endl;
			if (numTries > 10000)
			{
				throw GenericException("Gave up trying to find a random position in region.");
			}
		}
	} while (notFoundYet);

	return !notFoundYet;
}