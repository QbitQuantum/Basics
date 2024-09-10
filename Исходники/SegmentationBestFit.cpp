void SegmentationBestFit::accept()
{
    const Mesh::MeshObject* mesh = myMesh->Mesh.getValuePtr();
    const MeshCore::MeshKernel& kernel = mesh->getKernel();

    MeshCore::MeshSegmentAlgorithm finder(kernel);

    std::vector<MeshCore::MeshSurfaceSegment*> segm;
    if (ui->groupBoxCyl->isChecked()) {
        MeshCore::AbstractSurfaceFit* fitter;
        if (cylinderParameter.size() == 7) {
            std::vector<float>& p = cylinderParameter;
            fitter = new MeshCore::CylinderSurfaceFit(
                Base::Vector3f(p[0],p[1],p[2]),
                Base::Vector3f(p[3],p[4],p[5]),
                p[6]);
        }
        else {
            fitter = new MeshCore::CylinderSurfaceFit;
        }
        segm.push_back(new MeshCore::MeshDistanceGenericSurfaceFitSegment
            (fitter, kernel, ui->numCyl->value(), ui->tolCyl->value()));
    }
    if (ui->groupBoxSph->isChecked()) {
        MeshCore::AbstractSurfaceFit* fitter;
        if (sphereParameter.size() == 4) {
            std::vector<float>& p = sphereParameter;
            fitter = new MeshCore::SphereSurfaceFit(
                Base::Vector3f(p[0],p[1],p[2]),
                p[3]);
        }
        else {
            fitter = new MeshCore::SphereSurfaceFit;
        }
        segm.push_back(new MeshCore::MeshDistanceGenericSurfaceFitSegment
            (fitter, kernel, ui->numSph->value(), ui->tolSph->value()));
    }
    if (ui->groupBoxPln->isChecked()) {
        MeshCore::AbstractSurfaceFit* fitter;
        if (planeParameter.size() == 6) {
            std::vector<float>& p = planeParameter;
            fitter = new MeshCore::PlaneSurfaceFit(
                Base::Vector3f(p[0],p[1],p[2]),
                Base::Vector3f(p[3],p[4],p[5]));
        }
        else {
            fitter = new MeshCore::PlaneSurfaceFit;
        }
        segm.push_back(new MeshCore::MeshDistanceGenericSurfaceFitSegment
            (fitter, kernel, ui->numPln->value(), ui->tolPln->value()));
    }
    finder.FindSegments(segm);

    App::Document* document = App::GetApplication().getActiveDocument();
    document->openTransaction("Segmentation");

    std::string internalname = "Segments_";
    internalname += myMesh->getNameInDocument();
    App::DocumentObjectGroup* group = static_cast<App::DocumentObjectGroup*>(document->addObject
        ("App::DocumentObjectGroup", internalname.c_str()));
    std::string labelname = "Segments ";
    labelname += myMesh->Label.getValue();
    group->Label.setValue(labelname);
    for (std::vector<MeshCore::MeshSurfaceSegment*>::iterator it = segm.begin(); it != segm.end(); ++it) {
        const std::vector<MeshCore::MeshSegment>& data = (*it)->GetSegments();
        for (std::vector<MeshCore::MeshSegment>::const_iterator jt = data.begin(); jt != data.end(); ++jt) {
            Mesh::MeshObject* segment = mesh->meshFromSegment(*jt);
            Mesh::Feature* feaSegm = static_cast<Mesh::Feature*>(group->addObject("Mesh::Feature", "Segment"));
            Mesh::MeshObject* feaMesh = feaSegm->Mesh.startEditing();
            feaMesh->swap(*segment);
            feaSegm->Mesh.finishEditing();
            delete segment;

            std::stringstream label;
            label << feaSegm->Label.getValue() << " (" << (*it)->GetType() << ")";
            feaSegm->Label.setValue(label.str());
        }
        delete (*it);
    }
    document->commitTransaction();
}