void Obstacle::on_addToScene()
{
    node_ = SceneGraph::addModel(name_, model_);
    size_t batchCnt = 0;
    TriangleBatch const *triBatch = model_->batches(&batchCnt);
    size_t boneCnt = 0;
    Bone const *bone = model_->bones(&boneCnt);
    size_t vSize = model_->vertexSize();
    char const * vertex = (char const *)model_->vertices();
    unsigned int const *index = (unsigned int const *)model_->indices();
    for (size_t bi = 0; bi != batchCnt; ++bi)
    {
        dTriMeshDataID tmd = dGeomTriMeshDataCreate();
        dGeomTriMeshDataBuildSingle(tmd, vertex, vSize, triBatch[bi].maxVertexIndex + 1, 
            index + triBatch[bi].firstTriangle * 3, triBatch[bi].numTriangles * 3, 12);
        dGeomID geom = dCreateTriMesh(gStaticSpace, tmd, 0, 0, 0);
        tmd_.push_back(tmd);
        geom_.push_back(geom);
        Matrix bx;
        get_bone_transform(bone, triBatch[bi].bone, bx);
        Vec3 p(bx.translation());
        addTo(p, pos());
        dGeomSetPosition(geom, p.x, p.y, p.z);
        dGeomSetRotation(geom, bx.rows[0]);
    }
}