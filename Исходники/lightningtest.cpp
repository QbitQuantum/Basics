void Simple::CreateRoom ()
{
  // Load the texture from the standard library.  This is located in
  // CS/data/standard.zip and mounted as /lib/std using the Virtual
  // File System (VFS) plugin.
  if (!loader->LoadTexture ("brick", "/lib/std/castle/brick1_d.jpg"))
    ReportError("Error loading %s texture!",
		CS::Quote::Single ("brick1_d"));

  if (!loader->LoadTexture("energy", "/lib/std/energy.jpg"))
    ReportError("Error loading %s texture!",
		CS::Quote::Single ("energy"));

  iMaterialWrapper* tm = engine->GetMaterialList ()->FindByName ("brick");

  // Add a normal map to the material.
  {
    /* Shader variables are identified by numeric IDs for performance reasons.
    * The shader var string set translates string IDs to numeric IDs. */
    csRef<iShaderVarStringSet> svStrings =
      csQueryRegistryTagInterface<iShaderVarStringSet> (GetObjectRegistry(),
      "crystalspace.shader.variablenameset");
    // Load the normal map texture itself
    csRef<iTextureHandle> normalMap = loader->LoadTexture (
      "/lib/std/castle/brick1_n.jpg");
    // Set this to avoid compression - makes for better quality here
    normalMap->SetTextureClass ("normalmap");
    // The normal map is attached to the material through a shader variable.
    csShaderVariable* svNormalMap =
      tm->GetMaterial()->GetVariableAdd (svStrings->Request ("tex normal"));
    svNormalMap->SetValue (normalMap);
  }

  // We create a new sector called "room".
  room = engine->CreateSector ("room");

  // Creating the walls for our room.

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

  // Now we need light to see something.
  csRef<iLight> light;
  iLightList* ll = room->GetLights ();

  light = engine->CreateLight(0, csVector3(-3, 5, 0), 10, csColor(2, 0, 0));
  ll->Add (light);

  light = engine->CreateLight(0, csVector3(3, 5,  0), 10, csColor(0, 0, 2));
  ll->Add (light);

  light = engine->CreateLight(0, csVector3(0, 5, -3), 10, csColor(0, 2, 0));
  ll->Add (light);

  csRef<iMeshObjectType> type = csLoadPlugin<iMeshObjectType> (plgmgr,
    "crystalspace.mesh.object.lightning");

  /// Lightning 1
  csRef<iMeshObjectFactory> LightningObjectFactory1 = type->NewFactory();
  csRef<iLightningFactoryState> LightningFactoryState1 = scfQueryInterface<iLightningFactoryState> (LightningObjectFactory1);

  LightningObjectFactory1->SetMaterialWrapper(engine->GetMaterialList()->FindByName("energy"));
  LightningObjectFactory1->SetMixMode(CS_FX_ADD);
  LightningFactoryState1->SetOrigin(csVector3(0, 0, 0));
  LightningFactoryState1->SetPointCount(20);
  LightningFactoryState1->SetLength(5);
  LightningFactoryState1->SetVibration(0.02f);
  LightningFactoryState1->SetWildness(0.03f);
  LightningFactoryState1->SetUpdateInterval(30);
  LightningFactoryState1->SetDirectional(csVector3(0, 1, 0));  

  csRef<iMeshObject> mesh1 = LightningObjectFactory1->NewInstance();    
  csRef<iMeshWrapper> mw1 = engine->CreateMeshWrapper(mesh1, "lightning1", room, csVector3(-2, 3, 4));
  mw1->SetRenderPriority (engine->GetRenderPriority ("alpha"));

  /// Lightning 2
  csRef<iMeshObjectFactory> LightningObjectFactory = type->NewFactory();
  csRef<iLightningFactoryState> LightningFactoryState2 = scfQueryInterface<iLightningFactoryState> (LightningObjectFactory);

  LightningObjectFactory->SetMaterialWrapper(engine->GetMaterialList()->FindByName("energy"));
  LightningObjectFactory->SetMixMode(CS_FX_ADD);
  LightningFactoryState2->SetOrigin(csVector3(0, 0, 0));
  LightningFactoryState2->SetPointCount(60);
  LightningFactoryState2->SetLength(5);
  LightningFactoryState2->SetVibration(0.03f);
  LightningFactoryState2->SetWildness(0.06f);
  LightningFactoryState2->SetUpdateInterval(50);
  LightningFactoryState2->SetDirectional(csVector3(0, 1, 0));  

  csRef<iMeshObject> mesh2 = LightningObjectFactory->NewInstance();    
  csRef<iMeshWrapper> mw2 = engine->CreateMeshWrapper(mesh2, "lightning2", room, csVector3(0, 3, 4));
  mw2->SetRenderPriority (engine->GetRenderPriority ("alpha"));

  ///Lightning 3
  csRef<iMeshObjectFactory> LightningObjectFactory3 = type->NewFactory();
  csRef<iLightningFactoryState> LightningFactoryState3 = scfQueryInterface<iLightningFactoryState> (LightningObjectFactory3);

  LightningObjectFactory3->SetMaterialWrapper(engine->GetMaterialList()->FindByName("energy"));
  LightningObjectFactory3->SetMixMode(CS_FX_ADD);
  LightningFactoryState3->SetOrigin(csVector3(0, 0, 0));
  LightningFactoryState3->SetPointCount(30);
  LightningFactoryState3->SetLength(5);
  LightningFactoryState3->SetVibration(0.02f);
  LightningFactoryState3->SetWildness(0.09f);
  LightningFactoryState3->SetUpdateInterval(60);
  LightningFactoryState3->SetDirectional(csVector3(0, 1, 0));  
  LightningFactoryState3->SetBandWidth (0.6f);

  csRef<iMeshObject> mesh3 = LightningObjectFactory3->NewInstance();    
  csRef<iMeshWrapper> mw3 = engine->CreateMeshWrapper(mesh3, "lightning3", room, csVector3(2, 3, 4));
  mw3->SetRenderPriority (engine->GetRenderPriority ("alpha"));
}