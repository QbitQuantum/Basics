bool Simple::Initialize ()
{
  if (!csInitializer::RequestPlugins (object_reg,
                                      CS_REQUEST_VFS,
                                      CS_REQUEST_PLUGIN( "crystalspace.graphics2d.wxgl", iGraphics2D ),
                                      CS_REQUEST_OPENGL3D,
                                      CS_REQUEST_ENGINE,
                                      CS_REQUEST_FONTSERVER,
                                      CS_REQUEST_IMAGELOADER,
                                      CS_REQUEST_LEVELLOADER,
                                      CS_REQUEST_REPORTER,
                                      CS_REQUEST_REPORTERLISTENER,
                                      CS_REQUEST_END))
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "Can't initialize plugins!");
    return false;
  }

  //csEventNameRegistry::Register (object_reg);
  if (!csInitializer::SetupEventHandler (object_reg, SimpleEventHandler))
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "Can't initialize event handler!");
    return false;
  }
  CS_INITIALIZE_EVENT_SHORTCUTS (object_reg);

  KeyboardDown = csevKeyboardDown (object_reg);
  MouseMove = csevMouseMove (object_reg, 0);
  MouseUp = csevMouseUp (object_reg, 0);
  MouseDown = csevMouseDown (object_reg, 0);

  // Check for commandline help.
  if (csCommandLineHelper::CheckHelp (object_reg))
  {
    csCommandLineHelper::Help (object_reg);
    return false;
  }

  // The virtual clock.
  vc = csQueryRegistry<iVirtualClock> (object_reg);
  if (vc == 0)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "Can't find the virtual clock!");
    return false;
  }

  // Find the pointer to engine plugin
  engine = csQueryRegistry<iEngine> (object_reg);
  if (engine == 0)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "No iEngine plugin!");
    return false;
  }

  loader = csQueryRegistry<iLoader> (object_reg);
  if (loader == 0)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "No iLoader plugin!");
    return false;
  }

  g3d = csQueryRegistry<iGraphics3D> (object_reg);
  if (g3d == 0)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "No iGraphics3D plugin!");
    return false;
  }

  kbd = csQueryRegistry<iKeyboardDriver> (object_reg);
  if (kbd == 0)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "No iKeyboardDriver plugin!");
    return false;
  }

  // Load the frame from an XRC file
  wxXmlResource::Get ()->InitAllHandlers ();
  /* Find the file in the CS dirs.
   * (This is slightly more complicated as there may not be "one" CS dir.) */
  csPathsList* installPaths = csInstallationPathsHelper::GetPlatformInstallationPaths ();
  wxString searchPath;
  for (size_t i = 0; i < installPaths->GetSize(); i++)
  {
    if (!searchPath.IsEmpty()) searchPath.Append (wxPATH_SEP);
    searchPath.Append (wxString ((*installPaths)[i].path, wxConvUTF8));
  }
  delete installPaths;
  wxString resourceLocation;
  wxFileSystem wxfs;
  if (!wxfs.FindFileInPath (&resourceLocation, searchPath, wxT ("data/wxtest/wxtest.xrc"))
    || !wxXmlResource::Get ()->Load (resourceLocation))
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "Could not load XRC ressource file!");
    return false;
  }

  wxPanel* mainPanel = wxXmlResource::Get ()->LoadPanel (this, wxT ("MyPanel"));
  if (!mainPanel)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "Could not find main panel in XRC ressource file!");
    return false;
  }

  // Populate the tree with some test items
  wxTreeCtrl* tree = XRCCTRL (*mainPanel, "m_treeCtrl", wxTreeCtrl);
  if (!tree)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "Could not find tree in XRC ressource file!");
    return false;
  }

  wxImageList* imageList = new wxImageList (16, 16);
  tree->AssignImageList (imageList);
  
  wxBitmap sceneBmp (sceneIcon_xpm);
  int rootIconIdx = imageList->Add (sceneBmp);

  wxTreeItemId rootId = tree->AddRoot (wxT ("Root node"), rootIconIdx);
  tree->AppendItem (rootId, wxT ("test1"), rootIconIdx);
  tree->AppendItem (rootId, wxT ("test2"), rootIconIdx);
  tree->AppendItem (rootId, wxT ("test3"), rootIconIdx);
  tree->AppendItem (rootId, wxT ("test4"), rootIconIdx);
  tree->ExpandAll ();

  // Find the panel where to place the wxgl canvas
  wxPanel* panel = XRCCTRL (*this, "m_panel1", wxPanel);
  if (!panel)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "Could not find the panel for the wxgl canvas in XRC ressource file!");
    return false;
  }

  // Create the wxgl canvas
  iGraphics2D* g2d = g3d->GetDriver2D ();
  g2d->AllowResize (true);
  wxwindow = scfQueryInterface<iWxWindow> (g2d);
  if (!wxwindow)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "Canvas is no iWxWindow plugin!");
    return false;
  }

  wxPanel* panel1 = new Simple::Panel (panel, this);
  panel->GetSizer ()->Add (panel1, 1, wxALL | wxEXPAND);
  wxwindow->SetParent (panel1);

  Show (true);

  // Open the main system. This will open all the previously loaded plug-ins.
  if (!csInitializer::OpenApplication (object_reg))
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "Error opening system!");
    return false;
  }

  /* Manually focus the GL canvas.
     This is so it receives keyboard events (and conveniently translate these
     into CS keyboard events/update the CS keyboard state).
   */
  wxwindow->GetWindow ()->SetFocus ();

  // Load the texture from the standard library.  This is located in
  // CS/data/standard.zip and mounted as /lib/std using the Virtual
  // File System (VFS) plugin.
  if (!loader->LoadTexture ("stone", "/lib/std/stone4.gif"))
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
              "crystalspace.application.wxtest",
              "Error loading %s texture!",
              CS::Quote::Single ("stone4"));
    return false;
  }
  iMaterialWrapper* tm = engine->GetMaterialList ()->FindByName ("stone");

  // these are used store the current orientation of the camera
  rotY = rotX = 0;

  room = engine->CreateSector ("room");

  // First we make a primitive for our geometry.
  using namespace CS::Geometry;
  DensityTextureMapper mapper (0.3f);
  TesselatedBox box (csVector3 (-5, 0, -5), csVector3 (5, 20, 5));
  box.SetLevel (3);
  box.SetMapper (&mapper);
  box.SetFlags (Primitives::CS_PRIMBOX_INSIDE);

  // Now we make a factory and a mesh at once.
  csRef<iMeshWrapper> walls = GeneralMeshBuilder::CreateFactoryAndMesh (
      engine, room, "walls", "walls_factory", &box);
  walls->GetMeshObject ()->SetMaterialWrapper (tm);

  csRef<iLight> light;
  iLightList* ll = room->GetLights ();

  light = engine->CreateLight (0, csVector3 (-3, 5, 0), 10,
                               csColor (1, 0, 0));
  ll->Add (light);

  light = engine->CreateLight (0, csVector3 (3, 5,  0), 10,
                               csColor (0, 0, 1));
  ll->Add (light);

  light = engine->CreateLight (0, csVector3 (0, 5, -3), 10,
                               csColor (0, 1, 0));
  ll->Add (light);

  engine->Prepare ();

  using namespace CS::Lighting;
  SimpleStaticLighter::ShineLights (room, engine, 4);

  view = csPtr<iView> (new csView (engine, g3d));
  view->SetAutoResize (false);
  view->GetPerspectiveCamera ()->SetFOV ((float) (g2d->GetHeight ()) / (float) (g2d->GetWidth ()), g2d->GetWidth ());
  view->GetCamera ()->SetSector (room);
  view->GetCamera ()->GetTransform ().SetOrigin (csVector3 (0, 5, -3));
  view->SetRectangle (0, 0, g2d->GetWidth (), g2d->GetHeight ());

  printer.AttachNew (new FramePrinter (object_reg));

  return true;
}