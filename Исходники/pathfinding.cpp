QList<unsigned char> cPathfinding::find(P_CHAR pChar, const Coord &from, const Coord &to)
{
	QList<unsigned char> result;
	int i;

	// We can only calculate a path on the normal maps and if the destination is not out of range
	if (from.isInternalMap() || from.distance(to) > (unsigned int)areaSize) {
		return result;
	}

	memset(touched, 0, sizeof(bool) * nodeCount); // Clear the touched nodes
	this->goal = to; // Save the goal

	// Actually th�s should be the x/y offset of our area
	xoffset = (from.x + to.x - areaSize) / 2;
	yoffset = (from.y + to.y - areaSize) / 2;

	int fromNode = getNodeIndex(from.x, from.y, from.z);
	int toNode = getNodeIndex(to.x, to.y, to.z);
	openlist = fromNode; // Where are we

	// Initialize the node
	nodes[fromNode].cost = 0;
	nodes[fromNode].total = heuristic(from.x - xoffset, from.y - yoffset, from.z);
	nodes[fromNode].parent = -1;
	nodes[fromNode].next = -1;
	nodes[fromNode].prev = -1;
	nodes[fromNode].z = from.z;

	// We touched this node
	onopen[fromNode] = true;
	touched[fromNode] = true;

	int depth = 0;
	int newTotal, newCost;

	// This is controlled by the npc moving. Some npcs can fly (move over impassables)
	// others can open doors
	ignoreDoors = false;
	ignoreMovableImpassables = false;
	int successors[8]; // List of successor nodes used in subsequent iterations. Never more than 8
	int successorCount; // Number of successors found

	while (openlist != -1) {
		if (++depth > maxDepth)
			break; // Break if we would exceed the maximum iteration count

		int bestnode = findBest(openlist);

		// Get adjacent nodes that we can walk to
		successorCount = getSuccessors(bestnode, pChar, successors);

		if (successorCount == 0) {
			break; // We've run into a situation where we'll never find a suitable successor
		}

		// Follow every possible successor
		for (i = 0; i < successorCount; ++i) {
			int successor = successors[i];

			if (touched[successor]) {
				continue; // If we worked on the node already, skip this part
			}

			// calculate the cost of the successor based on the currents node cost
			newCost = nodes[bestnode].cost + 1;
			newTotal = newCost + heuristic(successor % areaSize, (successor / areaSize) % areaSize, nodes[successor].z);

			// Always execute, !wasTouched was always true here
			// if ( !wasTouched || m_Nodes[newNode].total > newTotal )
			nodes[successor].parent = bestnode;
			nodes[successor].cost = newCost;
			nodes[successor].total = newTotal;
			addToChain(successor);

			// We found our target
			if (successor == toNode) {
				int pathCount = 0; // Stack allocation speed isn't a concern here anymore
				int parent = nodes[successor].parent;

				// Record the path in reverse order
				while (parent != -1) {
					path[pathCount++] = getDirection(parent % areaSize, (parent / areaSize) % areaSize, successor % areaSize, (successor / areaSize) % areaSize);
					successor = parent; // Track back
					parent = nodes[successor].parent;

					if (successor == fromNode) {
						break;
					}
				}

				int backtrack = 0;
				while (pathCount != 0) {
					result.append( path[--pathCount] );
				}
				return result; // Immediately return
			}
		}
	}

	return result; // Nothing found
}