void WireExport::Export(string folder, string fileName)
{
	MStatus stat;

	mFolder = folder;
	mFileName = fileName;

	mSaver.SetFolder(mFolder);

	MItDependencyNodes itRenderLayers(MFn::kRenderLayer,&stat);
	err_code(stat);

	MFnRenderLayer wireLayer;
	while (!itRenderLayers.isDone())
	{		
		MFnRenderLayer renderLayer( itRenderLayers.item() );

		if (renderLayer.name() == "wire")
		{
			stat = wireLayer.setObject( renderLayer.object() );
			err_code(stat);
			break;
		}

		stat = itRenderLayers.next();
		err_code(stat);
	}

	MItDependencyNodes itDepCurve(MFn::kNurbsCurve,&stat);
	err_code(stat);

	vector<Wire> wires;

	while (!itDepCurve.isDone())
	{
		MObject obj = itDepCurve.item();
		MFnNurbsCurve wire(obj, &stat);
		err_code(stat);

		bool objInLayer = wireLayer.inLayer(obj, &stat);
		//err_code(stat);	

		if (!objInLayer)
		{
			stat = itDepCurve.next();
			err_code(stat);	
			continue;
		}

		MString cmd = MString("reference -q -f ") + wire.name();
		MString file_id;
		stat = MGlobal::executeCommand( cmd, file_id );
		if( stat == MS::kSuccess ) 
		{ 
			itDepCurve.next();
			continue;
		}

		MObject parentObj = wire.parent(0, &stat);
		err_code(stat);

		Wire newWire;
		newWire.name = wire.name().asChar();

		
		MPointArray points;

		stat = wire.getCVs(points);			
		err_code(stat);


		int numOfPoints = points.length();
		for (int n = 0; n < numOfPoints ; n++)
		{
			MPoint point = points[n];
			WirePoint wirePoint;
			wirePoint.x = (float)point.x;
			wirePoint.z = (float)point.z;

			double param;
			stat = wire.getParamAtPoint( point, param );
			err_code(stat);

			MVector	tangent = wire.tangent( param , MSpace::kObject, &stat);
			err_code(stat);

			tangent.normalize();

			wirePoint.tx = (float)tangent.x;
			wirePoint.tz = (float)tangent.z;

			newWire.wirePoints.push_back(wirePoint);
		}

		wires.push_back(newWire);

		stat = itDepCurve.next();
		err_code(stat);
	}

	WriteWires(wires);


}