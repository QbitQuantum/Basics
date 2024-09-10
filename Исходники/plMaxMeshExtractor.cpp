static void MakeDummyMesh(plMaxNode* node, plMaxMeshExtractor::NeutralMesh& mesh)
{
    hsPoint3 minV, maxV;

    Object* thisObj = node->GetObjectRef();
    DummyObject* thisDummy = (DummyObject*)thisObj;
    Box3 thisBoundSurface = thisDummy->GetBox();
    minV.fX = thisBoundSurface.Min().x;
    minV.fY = thisBoundSurface.Min().y;
    minV.fZ = thisBoundSurface.Min().z;
    maxV.fX = thisBoundSurface.Max().x;
    maxV.fY = thisBoundSurface.Max().y;
    maxV.fZ = thisBoundSurface.Max().z;

    MakeBoxMesh(node, mesh, minV, maxV);
}