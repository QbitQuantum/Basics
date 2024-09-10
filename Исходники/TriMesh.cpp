void TriMesh::computeFaceGrad(const VectorXd& vertForm, std::vector<Vec3>& faceVector) const
{
    faceVector.resize(numFaces());
    for (unsigned face = 0; face < numFaces(); ++face) 
    {
        std::vector<unsigned> fVert;
        getFaceVerts(face, fVert);
        assert(fVert.size() == 3);

        Vec3 pos[3];
        double val[3];
        for (unsigned i = 0; i < 3; ++i) 
        {
            val[i] = vertForm(fVert[i]);
            pos[i] = getVertPos(fVert[i]);
        }

        Vec3 X = Vec3::Zero();
        for (unsigned i = 0; i < 3; ++i) 
        {
            unsigned j = (i + 1) % 3;
            unsigned k = (i + 2) % 3;
            X += val[i] * (pos[k] - pos[j]);
        }

        Vec3 n = (pos[1]-pos[0]).cross(pos[2]-pos[1]);
        double twice_area = n.norm();
        n /= twice_area;

        faceVector[face] = n.cross(X) / twice_area;
    }
}