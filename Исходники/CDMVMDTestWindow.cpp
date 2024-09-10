CDMVMDTestWindow::CDMVMDTestWindow( int w, int h, const char* label )
: Fl_Window( w, h, label )
{

	// create sliders on the right
	int interfaceWidth = 300;
	int interfaceStartX = w-(interfaceWidth+10);
	int menuHeight = 0;
	Fl_Hor_Slider* slider = new Fl_Hor_Slider( interfaceStartX, 30+menuHeight, interfaceWidth-100, 20, "XSlider" );
	slider->labeltype(FL_NORMAL_LABEL);
	slider->align(FL_ALIGN_RIGHT);
	slider->callback(&CDMVMDTestWindow::_sliderChanged, this );
	slider->value(0);
	slider->bounds(-1,1);

	slider = new Fl_Hor_Slider( interfaceStartX, 70+menuHeight, interfaceWidth-100, 20, "YSlider" );
	slider->labeltype(FL_NORMAL_LABEL);
	slider->align(FL_ALIGN_RIGHT);
	slider->callback(&CDMVMDTestWindow::_sliderChanged, this );
	slider->value(0);
	slider->bounds(-1,1);
	

	
	
	CDAssimpLoader loader;
	bool loaded = loader.loadModel("data/male_head_3ds-st.dae");
	assert(loaded);
	originalMesh = loader.getLoadedMesh();
	originalMesh.updateNormals();
	
	loaded = loader.loadModel("data/candide-closed.dae");
	assert(loaded);
	controlMesh = loader.getLoadedMesh();
	controlMesh.updateNormals();
	
	// test deformer
	deformer.setupDeformation(originalMesh, controlMesh);
	
	if ( glWindow ) {
		glWindow->redraw();
	}
	
	
	// create opengl window
	glWindow = new CDMVMDTestGlWindow( 10, 10, w-interfaceWidth-30, h-20, controlMesh, originalMesh );
	resizable(glWindow);
	glWindow->end();


	// done
	end();
		
	// setup idle
	Fl::add_timeout( framerate, &idleCallback, this );
		 
	// call first draw
	updateDeformation();
	deformer.compareDeformedWithOriginal();
	
	//CDMeshObjWriter writer;
	//writer.writeObj( deformer.getDeformedMesh(), "/tmp/deformed.obj");
}