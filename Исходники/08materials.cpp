// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
	OSG::preloadSharedObject("OSGFileIO");
	OSG::preloadSharedObject("OSGTBFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the scene
        
        // create a pretty simple graph: a Group with two Transforms as children,
        // each of which carries a single Geometry.
        
        // The scene group
        
        OSG::NodeRefPtr  scene = OSG::Node::create();
        OSG::GroupRefPtr g     = OSG::Group::create();
        
        scene->setCore(g);
        
        // The cylinder and its transformation
        OSG::NodeRefPtr     cyl    = OSG::Node::create();
        OSG::GeometryRefPtr cylgeo = OSG::makeCylinderGeo( 1.4f, .3f, 64, 
                                                           true, true, true );
        
        cyl->setCore(cylgeo);
    
        cyltrans = OSG::Transform::create();
    
        OSG::NodeRefPtr cyltransnode = OSG::Node::create();
        cyltransnode->setCore (cyltrans);
        cyltransnode->addChild(cyl     );
        
        // add it to the scene
        scene->addChild(cyltransnode);
        
        // The torus and its transformation
        OSG::NodeRefPtr     torus    = OSG::Node::create();
        OSG::GeometryRefPtr torusgeo = OSG::makeTorusGeo( .2f, 1, 32, 64 );
        
        torus->setCore(torusgeo);
            
        tortrans = OSG::Transform::create();
    
        OSG::NodeRefPtr tortransnode = OSG::Node::create();
        tortransnode->setCore (tortrans);
        tortransnode->addChild(torus   );
        
        // add it to the scene
        scene->addChild(tortransnode);
    
        // create the materials: Here, just using cgfx materials.
        OSG::CgFXMaterialRefPtr mat1 = OSG::CgFXMaterial::create();
        if(argc > 1)
        {
        	mat1->setEffectFile(argv[1]);
        }
        
    
        // assign the material to the geometry
        cylgeo->setMaterial(mat1);
        
        // assign the material to the geometry
        torusgeo->setMaterial(mat1);
    
        OSG::commitChanges();
    
        // create the SimpleSceneManager helper
        mgr = new OSG::SimpleSceneManager;
    
        // tell the manager what to manage
        mgr->setWindow(gwin );
        
    

        
        // file io
		OSG::FCFileType::FCPtrStore Containers;
		Containers.insert(scene);
		//Use an empty Ignore types vector
		OSG::FCFileType::FCTypeVector IgnoreTypes;
		//IgnoreTypes.push_back(Node::getClassType().getId());
	    
		//Write the Field Containers to a xml file
		OSG::FCFileHandler::the()->write(Containers,OSG::BoostPath("C:/Users/danielg/Desktop/test.xml"),IgnoreTypes);

        //Read FieldContainers from an XML file
        OSG::FCFileType::FCPtrStore NewContainers;
        NewContainers = OSG::FCFileHandler::the()->read(OSG::BoostPath("C://Users//danielg//Documents//VirtualCellData//trunk//Artwork//Models//Vehicles_and_Tools//Protein_Ship//Ship_Export_Test.dae"));

        //Write the read FieldContainers to an XML file
       // OSG::FCFileHandler::the()->write(NewContainers,OSG::BoostPath("C:/Users/danielg/Desktop/test2.xml"),IgnoreTypes);

		//NewContainers.clear();

		// NewContainers = OSG::FCFileHandler::the()->read(OSG::BoostPath("C:/Users/danielg/Desktop/test2.xml"));

		OSG::FCFileType::FCPtrStore::iterator itor = NewContainers.begin();
		OSG::FCFileType::FCPtrStore::iterator endIt = NewContainers.end();
		OSG::NodeRefPtr root;
		for(; itor != endIt; itor++)
		{
			OSG::Node *cur = OSG::dynamic_pointer_cast<OSG::Node>((*itor));
			if(cur != NULL)
			{
				if(cur->getParent() == NULL) 
				{
					root = cur; //mgr->setRoot(cur);
					break;
				}
			}
		}

		std::string filepath("C://Users//danielg//Desktop//test.osb");
		OSG::SceneFileHandler::the()->write(root,filepath.c_str());

		root = OSG::SceneFileHandler::the()->read(filepath.c_str());

		if(root != NULL)
		{
			mgr->setRoot(root);
		} else
		{
			std::cout << std::endl << "ERROR READING THE OSB FILE BACK IN~~~~!" << std::endl;
		}

		// show the whole scene
        mgr->showAll();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}