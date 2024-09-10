void cnoid::savePCD(SgPointSet* pointSet, const std::string& filename, const Affine3& viewpoint)
{
    if(!pointSet->hasVertices()){
        throw empty_data_error() << error_info_message(_("Empty pointset"));
    }

    ofstream ofs;
    ofs.open(filename.c_str());

    ofs <<
        "# .PCD v.7 - Point Cloud Data file format\n"
        "VERSION .7\n"
        "FIELDS x y z\n"
        "SIZE 4 4 4\n"
        "TYPE F F F\n"
        "COUNT 1 1 1\n";

    const SgVertexArray& points = *pointSet->vertices();
    const int numPoints = points.size();
    ofs << "WIDTH " << numPoints << "\n";
    ofs << "HEIGHT 1\n";

    ofs << "VIEWPOINT ";
    Affine3::ConstTranslationPart t = viewpoint.translation();
    ofs << t.x() << " " << t.y() << " " << t.z() << " ";
    const Quaternion q(viewpoint.rotation());
    ofs << q.w() << " " << q.x() << " " << q.y() << " " << q.z() << "\n";

    ofs << "POINTS " << numPoints << "\n";
    
    ofs << "DATA ascii\n";

    for(int i=0; i < numPoints; ++i){
        const Vector3f& p = points[i];
        ofs << p.x() << " " << p.y() << " " << p.z() << "\n";
    }

    ofs.close();
}