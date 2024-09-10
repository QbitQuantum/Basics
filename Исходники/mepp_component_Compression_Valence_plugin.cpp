void mepp_component_Compression_Valence_plugin::OnDecompress_all()
{
	Timer timer;
	timer.start();

	// active viewer
	if (mw->activeMdiChild() != 0)
	{
		Viewer* viewer = (Viewer *)mw->activeMdiChild();
		PolyhedronPtr polyhedron_ptr = viewer->getScenePtr()->get_polyhedron();

		Compression_Valence_ComponentPtr component_ptr = findOrCreateComponentForViewer<Compression_Valence_ComponentPtr, Compression_Valence_Component>(viewer, polyhedron_ptr);
		{

			if (!component_ptr->IsDecompress)
			{				
				QMessageBox::information(mw, APPLICATION, tr("Decompression not possible: please load .p3d file first."));
				return;
			}			

			if (component_ptr->Possible_change_sequence == true)
				component_ptr->Possible_change_sequence = false;

			// read from file
			if (!component_ptr->Sequence)
			{
				component_ptr->Decompression_All_From_File(*viewer->getScenePtr()->get_polyhedron(0));				
			}

			// read from sequence
			else
			{
				while(component_ptr->Process_level != component_ptr->Total_layer)
				{
					PolyhedronPtr New_mesh(new Polyhedron());
					component_ptr->Decompression_From_Sequence(*viewer->getScenePtr()->get_polyhedron(component_ptr->Process_level), *New_mesh);					
					vector<PolyhedronPtr/*Polyhedron**/>::iterator it = viewer->getScenePtr()->get_begin_polyhedrons();	// MT
					viewer->getScenePtr()->insert_polyhedron(it + component_ptr->Process_level-1, New_mesh);				
				}
				viewer->getScenePtr()->set_current_polyhedron(component_ptr->Process_level);				
			}
			ShowText();
			viewer->recreateListsAndUpdateGL();
		}
	}
	timer.stop();
	double Time = timer.time();
	QString Total_time = QString("Processing time : %1 s \n\n").arg(double(Time), 4, 'f', 3);			
	QMessageBox::information(mw, APPLICATION, Total_time);
	//QApplication::restoreOverrideCursor();
}