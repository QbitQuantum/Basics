iSector* CsBench::CreateRoom (const char* name, const char* meshname,
                              const csVector3& p1, const csVector3& p2)
{
    iSector* room2 = engine->CreateSector (name);

    using namespace CS::Geometry;
    DensityTextureMapper mapper (0.3f);
    TesselatedBox box (p1, p2);
    box.SetLevel (3);
    box.SetMapper (&mapper);
    box.SetFlags (Primitives::CS_PRIMBOX_INSIDE);

    // Now we make a factory and a mesh at once.
    csRef<iMeshWrapper> walls = GeneralMeshBuilder::CreateFactoryAndMesh (
                                    engine, room2, meshname, meshname, &box);
    walls->GetMeshObject ()->SetMaterialWrapper (material);

    using namespace CS::Lighting;
    SimpleStaticLighter::ShineLights (walls, engine, 4);

    return room2;
}