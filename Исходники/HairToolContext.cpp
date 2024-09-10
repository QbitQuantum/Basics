MStatus HairToolContext::doPress( MEvent& event )
 {
	// if we have a left mouse click
	if(event.mouseButton() == MEvent::kLeftMouse)
	{
		//Our Viewer
		m_View = M3dView::active3dView();

		//Get Screen click position
		event.getPosition( m_storage[0], m_storage[1] );
		screenPoints = vector<vec2>();
		screenPoints.push_back(vec2(m_storage[0], m_storage[1]));
		//char buffer[200];
		//sprintf(buffer, "print \"%i, %i\\n\"", m_storage[0], m_storage[1]);
		//MGlobal::executeCommand(buffer);

		//Camera stuff
		MPoint origin = MPoint();
		MVector direction = MVector();
		m_View.viewToWorld(m_storage[0], m_storage[1], origin, direction);

		//Iterate through meshes in scene
		bool intersection = false;
		MPointArray points =  MPointArray();
		MIntArray polygonIds =  MIntArray();
		MItDag dagIter = MItDag(MItDag::kBreadthFirst, MFn::kInvalid);
		for( ; !dagIter.isDone(); dagIter.next() ){
			MDagPath dagPath;
			dagIter.getPath(dagPath);
			MFnDagNode dagNode( dagPath);

			//Object cannot be intermediate, it must be a mesh
			if( dagNode.isIntermediateObject() ) continue;
			if( !dagPath.hasFn(MFn::kMesh) ) continue;
			if( dagPath.hasFn(MFn::kTransform) ) continue;

			MGlobal::executeCommand(MString("print \"node is a mesh \\n\""));

			//MFnMesh mesh = MFnMesh(dagPath);
			MFnMesh mesh(dagPath);
			points =  MPointArray();
			polygonIds =  MIntArray();
			intersection = mesh.intersect(origin, direction, points, 1e-010, MSpace::kWorld, &polygonIds);
			
			if(intersection){
				break;
			}
		}
		
		if(intersection){
			intersectionFound = true;

			MDagPath dagPath;
			dagIter.getPath(dagPath);
			// MFnMesh mesh = MFnMesh(dagPath);
			MFnMesh mesh(dagPath);

			//Polygon Normal
			MVector polygonNormal;
			mesh.getPolygonNormal(polygonIds[0], polygonNormal, MSpace::kWorld);
			if(polygonNormal.normal().angle(direction.normal()) < 20.0f){
				//polygonNormal = mesh.get
			}

			//Camera Right
			m_View.getCamera(dagPath);
			MFnCamera camera(dagPath);
			MVector cameraRight = camera.rightDirection(MSpace::kWorld);
			
			//Resulting Plane
			//Point
			point = points[0];
			//Normal
			normal = cameraRight^polygonNormal;

			//pushback point
			splinePoints = vector<MPoint>();
			splinePoints.push_back(MPoint(points[0].x, points[0].y, points[0].z, points[0].w));

			/*//Calculate Tvalue
			tValue = (points[0].x - origin.x)/direction.x;*/
			
		}
		else{
			intersectionFound = false;
			MGlobal::executeCommand("print \" No Intersection \\n\"");
		}

		// yay!
		return MS::kSuccess;
	}

	// just let the base class handle the event*/
	return MPxContext::doPress(event);
 }