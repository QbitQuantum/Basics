bool ObjLoaderDemo::init()
{
    if(RenderCore::init() == false)
    {
        return false;
    }

    //
    // Must init Effects first since InputLayouts depend on shader signatures.
    //
    EffectMgr::initAll(md3dDevice);
    InputLayoutMgr::initAll(md3dDevice);
    RenderStateMgr::initAll(md3dDevice);
    
    TextureMgr::initAll(md3dDevice);
    TextureMgr::addPath(std::wstring(L"../Models/"));
    TextureMgr::addPath(std::wstring(L"../Textures/"));

    mpModel = new Model(md3dDevice, md3dImmediateContext);
    //mpModel->loadObj(L"../Models/cup.obj");
    mpModel->loadObj(L"../Models/clock_triangulate.obj", true);
    //mpModel->loadObj(L"../Models/PM3D_Cylinder3D.obj");

    XMFLOAT4X4 world, texTransform;
    XMMATRIX scale = XMMatrixScaling(1.f, 1.f, 1.f);
    XMMATRIX translation = XMMatrixTranslation(0.f, 0.f, 0.f);
    XMStoreFloat4x4(&world, XMMatrixMultiply(scale, translation));
    XMStoreFloat4x4(&texTransform, XMMatrixIdentity());
    mpModel->update(world, texTransform);

    return true;
}