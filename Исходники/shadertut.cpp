void ShaderTut::CreateRoom ()
{
  // Load the texture from the standard library.  This is located in
  // CS/data/standard.zip and mounted as /lib/std using the Virtual
  // File System (VFS) plugin.
  if (!loader->LoadTexture ("brick", "/lib/std/castle/brick1_d.jpg"))
    ReportError("Error loading %s texture!",
		CS::Quote::Single ("brick1_d"));

  iMaterialWrapper* tm = engine->GetMaterialList ()->FindByName ("brick");
  
  /* Shader variables are identified by numeric IDs for performance reasons.
   * The shader var string set translates string IDs to numeric IDs. */
  csRef<iShaderVarStringSet> svStrings =
    csQueryRegistryTagInterface<iShaderVarStringSet> (GetObjectRegistry(),
      "crystalspace.shader.variablenameset");
  
  // Add a normal map to the material.
  {
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
  // Set a specular reflection color.
  {
    csShaderVariable* svSpecColor =
      tm->GetMaterial()->GetVariableAdd (svStrings->Request ("specular"));
    svSpecColor->SetValue (csColor (0.8f));
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
}