	// Execute the command
	MStatus OgreExporter::doIt(const MArgList& args)
	{
		// clean up
		delete m_pMesh;
		delete m_pMaterialSet;

		// Parse the arguments.
		m_params.parseArgs(args);
		// Create output files
		m_params.openFiles();
		// Create a new empty mesh
		m_pMesh = new Mesh();
		// Create a new empty material set
		m_pMaterialSet = new MaterialSet();
		// Save current time for later restore
		m_curTime = MAnimControl::currentTime();
		// Save active selection list for later restore
		MGlobal::getActiveSelectionList(m_selList);
		/**************************** LOAD DATA **********************************/
		if (m_params.exportAll)
		{	// We are exporting the whole scene
			std::cout << "Export the whole scene\n";
			std::cout.flush();
			MItDag dagIter;
			MFnDagNode worldDag (dagIter.root());
			MDagPath worldPath;
			worldDag.getPath(worldPath);
			stat = translateNode(worldPath);
		}
		else
		{	// We are translating a selection
			std::cout << "Export selected objects\n";
			std::cout.flush();
			// Get the selection list
			MSelectionList activeList;
			stat = MGlobal::getActiveSelectionList(activeList);
			if (MS::kSuccess != stat)
			{
				std::cout << "Error retrieving selection list\n";
				std::cout.flush();
				exit();
				return MS::kFailure;
			}
			MItSelectionList iter(activeList);

			for ( ; !iter.isDone(); iter.next())
			{								
				MDagPath dagPath;
				stat = iter.getDagPath(dagPath);
				stat = translateNode(dagPath); 
			}							
		}

		// Load vertex animations
		if (m_params.exportVertAnims)
			m_pMesh->loadAnims(m_params);

		// Load blend shapes
		if (m_params.exportBlendShapes)
			m_pMesh->loadBlendShapes(m_params);

		// Restore skeleton to correct pose
		if (m_pMesh->getSkeleton())
			m_pMesh->getSkeleton()->restorePose();

		// Load skeleton animation (do it now, so we have loaded all needed joints)
		if (m_pMesh->getSkeleton() && m_params.exportSkelAnims)
		{
			// Load skeleton animations
			m_pMesh->getSkeleton()->loadAnims(m_params);
		}

		/**************************** WRITE DATA **********************************/
		stat = writeOgreData();

		std::cout << "Export completed succesfully\n";
		std::cout.flush();
		exit();

		return MS::kSuccess;
	}