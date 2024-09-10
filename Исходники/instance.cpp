void Instance::prepare(std::vector< GeometricObject* > &objects)
{
    m_bounds = objects[m_meshId]->getBounds();
    Vec3 min = m_bounds.min();
    Vec3 max = m_bounds.max();
    Vec3 verts[8];
    verts[0] = Vec3(min[0], min[1], min[2]);
    verts[1] = Vec3(min[0], min[1], max[2]);
    verts[2] = Vec3(min[0], max[1], max[2]);
    verts[3] = Vec3(min[0], max[1], min[2]);
    verts[4] = Vec3(max[0], min[1], min[2]);
    verts[5] = Vec3(max[0], min[1], max[2]);
    verts[6] = Vec3(max[0], max[1], max[2]);
    verts[7] = Vec3(max[0], max[1], min[2]);
    min = Vec3(FLT_MAX);
    max = Vec3(-FLT_MAX);
    m_transform *= objects[m_meshId]->getTransform();
    Matrix4x4 invTrans = m_transform;
    invTrans.invert();
    for(int i=0;i<8;i++){
        invTrans.multVecMatrix(verts[i],verts[i]);
        for(int ii=0;ii<3;ii++){
            if(verts[i][ii] < min[ii]){
                min[ii] = verts[i][ii];
            }
            if(verts[i][ii] > max[ii]){
                max[ii] = verts[i][ii];
            }
        }
    }
    m_bounds.setMin(min);
    m_bounds.setMax(max);
    m_bvh = objects[m_meshId]->getBVH();
    m_normalinvTransform = m_transform;
    m_normalinvTransform.transpose();
}