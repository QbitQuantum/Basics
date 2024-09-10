	//#################### PUBLIC METHODS ####################
std::vector<ObjectCommand_Ptr> MinimusGotoPositionYoke::generate_commands(InputState& input)
{
	const Database& db = *m_objectManager->database();
	NavManager_CPtr navManager = db.get("db://NavManager", navManager);
	shared_ptr<std::vector<CollisionPolygon_Ptr> > polygons = db.get("db://OnionPolygons", polygons);
	OnionTree_CPtr tree = db.get("db://OnionTree", tree);

	// Check to make sure the yoke's still active.
	if(m_state != YOKE_ACTIVE)
	{
		return std::vector<ObjectCommand_Ptr>();
	}

	ICmpMovement_CPtr cmpMovement = m_objectManager->get_component(m_objectID, cmpMovement);		assert(cmpMovement != NULL);
	ICmpSimulation_CPtr cmpSimulation = m_objectManager->get_component(m_objectID, cmpSimulation);	assert(cmpSimulation != NULL);

	const Vector3d& source = cmpSimulation->position();

	if(!m_path)
	{
		int mapIndex = m_objectManager->bounds_manager()->lookup_bounds_index(cmpSimulation->bounds_group(), cmpSimulation->posture());
		NavDataset_CPtr navDataset = navManager->dataset(mapIndex);
		NavMesh_CPtr navMesh = navDataset->nav_mesh();
		GlobalPathfinder pathfinder(navMesh, navDataset->adjacency_list(), navDataset->path_table());

		int suggestedSourcePoly = cmpMovement->cur_nav_poly_index();
		int sourcePoly = NavMeshUtil::find_nav_polygon(source, suggestedSourcePoly, *polygons, tree, navMesh);
		if(sourcePoly == -1)	{ m_state = YOKE_FAILED; return std::vector<ObjectCommand_Ptr>(); }
		int destPoly = NavMeshUtil::find_nav_polygon(m_dest, -1, *polygons, tree, navMesh);
		if(destPoly == -1)		{ m_state = YOKE_FAILED; return std::vector<ObjectCommand_Ptr>(); }

		// FIXME: It's wasteful to copy the array of links each time (even though it's an array of pointers).
		m_links = navMesh->links();

		m_path.reset(new std::list<int>);
		bool pathFound = pathfinder.find_path(source, sourcePoly, m_dest, destPoly, *m_path);
		if(!pathFound)			{ m_state = YOKE_FAILED; return std::vector<ObjectCommand_Ptr>(); }
	}

	// FIXME:	The way this yoke decides that it's traversed a link isn't sufficient.
	//			I've devised a better way of doing it, but it's not yet implemented.

	// Step 1:	If the path is non-empty, go to the next link that we haven't already passed.
	Vector3d dir;
	while(!m_path->empty())
	{
		const Vector3d& linkIn = m_links[m_path->front()]->source_position();
		const Vector3d& linkOut = m_links[m_path->front()]->dest_position();
		dir = linkIn - source;
		if(dir.length() >= 0.1 && source.distance(linkOut) >= 0.1)
		{
			dir.normalize();
			break;
		}
		else
		{
			m_path->pop_front();
		}
	}

	if(!m_path->empty())
	{
		std::vector<ObjectCommand_Ptr> commands;
		commands.push_back(ObjectCommand_Ptr(new CmdBipedWalk(m_objectID, dir)));
		commands.push_back(ObjectCommand_Ptr(new CmdBipedSetLook(m_objectID, dir)));
		return commands;
	}

	// Step 2:	If the path is empty, go straight to the actual destination.
	dir = m_dest - source;
	if(dir.length() >= 0.1)
	{
		dir.normalize();

		std::vector<ObjectCommand_Ptr> commands;
		commands.push_back(ObjectCommand_Ptr(new CmdBipedWalk(m_objectID, dir)));
		commands.push_back(ObjectCommand_Ptr(new CmdBipedSetLook(m_objectID, dir)));
		return commands;
	}
	else
	{
		// We've reached the destination.
		m_state = YOKE_SUCCEEDED;
		return std::vector<ObjectCommand_Ptr>();
	}
}