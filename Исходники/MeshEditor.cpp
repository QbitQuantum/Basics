void MeshFaceAddition::addFace()
{
    Mesh::Feature* mf = static_cast<Mesh::Feature*>(faceView->mesh->getObject());
    App::Document* doc = mf->getDocument();
    doc->openTransaction("Add triangle");
    Mesh::MeshObject* mesh = mf->Mesh.startEditing();
    MeshCore::MeshFacet f;
    f._aulPoints[0] = faceView->index[0];
    f._aulPoints[1] = faceView->index[1];
    f._aulPoints[2] = faceView->index[2];
    std::vector<MeshCore::MeshFacet> faces;
    faces.push_back(f);
    mesh->addFacets(faces);
    mf->Mesh.finishEditing();
    doc->commitTransaction();

    clearPoints();
}