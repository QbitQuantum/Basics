	bool AStarPlanner::computePath(std::vector<Util::Point>& agent_path,  Util::Point start, Util::Point goal, SteerLib::GridDatabase2D * _gSpatialDatabase, bool append_to_path)
	{
		gSpatialDatabase = _gSpatialDatabase;

		int startIndex = gSpatialDatabase->getCellIndexFromLocation(start);
		SearchNodePtr startNode(new SearchNode(startIndex, 0, 0));

		int goalIndex = gSpatialDatabase->getCellIndexFromLocation(goal);

		std::vector<SearchNodePtr> open;
		std::vector<SearchNodePtr> closed;
		SearchNodePtr goalNode(nullptr);
		open.push_back(startNode);

		while (!open.empty()) {
			// Get the node with the minimum f, breaking ties on g.
            std::vector<SearchNodePtr>::iterator minIter = std::min_element(open.begin(), open.end());
			SearchNodePtr minNode = *minIter;
			open.erase(minIter);

            // If we're visiting the goal, we're finished.
			if (minNode->index() == goalIndex) {
				goalNode = minNode;
				break;
			}

			// Expand this node.
			std::vector<SearchNodePtr> expandedList = _expand(minNode, goal);
			for (SearchNodePtr& expandedNode : expandedList) {
				// If this cell is already in the open set, check if this is a cheaper path.
				std::vector<SearchNodePtr>::iterator iter = std::find(open.begin(), open.end(), expandedNode);
				if (iter != open.end()) {
					if (expandedNode->g() < (*iter)->g()) {
						(*iter)->g(expandedNode->g());
						(*iter)->prev(minNode);
					}
				} else {
					if (std::find(closed.begin(), closed.end(), expandedNode) == closed.end()) {
						expandedNode->prev(minNode);
						open.push_back(expandedNode);
					}
				}
			}
			closed.push_back(minNode);
		}

        // Check if a path to the goal was not found.
		if (goalNode == nullptr) {
			return false;
		}

		// Go back from goal node to start.
		SearchNodePtr ptr = goalNode;
		float totalPathCost = 0;
		while (ptr != nullptr) {
			Util::Point point;
			gSpatialDatabase->getLocationFromIndex(ptr->index(), point);
			agent_path.insert(agent_path.begin(), point);

			SearchNodePtr prev = ptr->prev();
			if (prev == nullptr) break;

			Util::Point prevPoint;
			gSpatialDatabase->getLocationFromIndex(prev->index(), prevPoint);
			totalPathCost += distanceBetween(point, prevPoint);

			ptr = prev;
		}

		std::cout << "\nTotal path cost is " << totalPathCost << std::endl;
        std::cout << "\nThe number of expanded nodes is " << numExpanded << std::endl;

		return true;
	}