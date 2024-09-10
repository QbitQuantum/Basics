void ImposterTest::CreateRoom ()
{
    // Load the texture from the standard library.  This is located in
    // CS/data/standard.zip and mounted as /lib/std using the Virtual
    // File System (VFS) plugin.
    if (!loader->LoadTexture ("stone", "/lib/std/stone4.gif"))
        ReportError("Error loading %s texture!",
                    CS::Quote::Single ("stone4"));

    iMaterialWrapper* tm = engine->GetMaterialList ()->FindByName ("stone");

    // We create a new sector called "room".
    room = engine->CreateSector ("room");

    // First we make a primitive for our geometry.
    using namespace CS::Geometry;
    DensityTextureMapper mapper (0.3f);
    TesselatedBox box (csVector3 (-6, -6, -6), csVector3 (6, 6, 6));
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

    light = engine->CreateLight(0, csVector3(-3, 3, 0), 10, csColor(1, 0, 0));
    ll->Add (light);

    light = engine->CreateLight(0, csVector3(3, 3,  0), 10, csColor(0, 0, 1));
    ll->Add (light);

    light = engine->CreateLight(0, csVector3(0, 3, -3), 10, csColor(0, 1, 0));
    ll->Add (light);

    // Load shader required for this test app.
    loader->LoadShader("/shader/lighting/lighting_imposter.xml");
}