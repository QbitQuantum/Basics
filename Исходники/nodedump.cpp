	void IterateSelection()
	{
		unsigned int i;
		MSelectionList list;
		MDagPath dagpath;
		MFnDagNode fnnode;

		MGlobal::getActiveSelectionList(list);

		for(i = 0; i < list.length(); i++)
		{
			list.getDagPath(i, dagpath);
			fnnode.setObject(dagpath);
			cout << fnnode.name().asChar() << " of type " << fnnode.typeName().asChar() << " is selected" << endl;

			cout << "has " << fnnode.childCount() << " children" << endl;

			//Iterate the children
			for(int j = 0; j < fnnode.childCount(); j++)
			{
				MObject childobj;
				MFnDagNode fnchild;

				childobj = fnnode.child(j);
				fnchild.setObject(childobj);

				cout << "child " << j << " is a " << fnchild.typeName().asChar() << endl;

				//MFn::Type type = fnchild.type()
				//if(fnchild.type() == MFn::kMesh)
				//DumpMesh(dagpath);
				//DumpMesh2(dagpath);
				IterateWorldMeshesInSelection();
			}
		}
	}