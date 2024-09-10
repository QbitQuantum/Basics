void SgMesh::transform(const Affine3f& T)
{
    if(hasVertices()){
        auto& v = *vertices();
        for(size_t i=0; i < v.size(); ++i){
            v[i] = T.linear() * v[i] + T.translation();
        }
        if(hasNormals()){
            auto& n = *normals();
            for(size_t i=0; i < n.size(); ++i){
                n[i] = T.linear() * n[i];
            }
        }
    }
    setPrimitive(MESH); // clear the primitive information
}