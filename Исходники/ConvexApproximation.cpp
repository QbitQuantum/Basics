void ConvexApproximationObject::LoadGeometries (NewtonMesh* const meshOut, const dMatrix& matrix)
{
	INode* stack[1024];

	ConvexApproximationClassDesc* const desc = (ConvexApproximationClassDesc*) ConvexApproximationClassDesc::GetDescriptor();

	INode* const sourceNode = desc->m_sourceNode;
	_ASSERTE (sourceNode);
	stack[0] = sourceNode;
	int stackIndex = 1;


	dMatrix orthogonalRootTransform (matrix.Inverse());

	while (stackIndex) {
		stackIndex --;
		INode* const node = stack[stackIndex];

		// Get Transformation matrix at frame 0
		//dMatrix matrix (GetMatrixFromMaxMatrix (node->GetNodeTM (0)) * orthogonalRootTransform);
		dMatrix matrix (GetMatrixFromMaxMatrix (node->GetObjectTM(0)) * orthogonalRootTransform);
		
		//nodeMap.Insert(sceneNode, node);
		ObjectState os (node->EvalWorldState(0)); 

		// The obj member of ObjectState is the actual object we will export.
		if (os.obj) {

			// We look at the super class ID to determine the type of the object.
			switch(os.obj->SuperClassID()) 
			{
				case GEOMOBJECT_CLASS_ID: 
				{
					if (!node->GetBoneNodeOnOff()) {
						AddPolygonFromObject(node, &os, meshOut, matrix);
					}
					break;
				}
			}
		}

		for (int i = 0; i < node->NumberOfChildren(); i ++) {
			stack[stackIndex] = node->GetChildNode(i);
			stackIndex ++;
			_ASSERTE (stackIndex * sizeof (INode*) < sizeof (stack));	
		}
	}
}