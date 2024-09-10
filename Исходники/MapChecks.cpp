	bool fixProblem(unsigned index, unsigned fix_type, MapEditor* editor)
	{
		if (index >= things.size())
			return false;

		if (fix_type == 0)
		{
			MapThing* thing = things[index];
			MapLine* line = lines[index];

			// Get nearest line point to thing
			fpoint2_t np = MathStuff::closestPointOnLine(thing->xPos(), thing->yPos(), line->x1(), line->y1(), line->x2(), line->y2());

			// Get distance to move
			double r = theGameConfiguration->thingType(thing->getType())->getRadius();
			double dist = MathStuff::distance(0, 0, r, r);

			editor->beginUndoRecord("Move Thing", true, false, false);

			// Move along line direction
			map->moveThing(thing->getIndex(), np.x - (line->frontVector().x * dist), np.y - (line->frontVector().y * dist));

			editor->endUndoRecord();

			return true;
		}

		return false;
	}