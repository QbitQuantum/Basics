int ROSURDFImporter::convertLinkVisualShapes(int linkIndex, const char* pathPrefix, const btTransform& inertialFrame) const
{
    btAlignedObjectArray<GLInstanceVertex> vertices;
    btAlignedObjectArray<int> indices;
    btTransform startTrans; startTrans.setIdentity();
    int graphicsIndex = -1;
        
    for (int v = 0; v < (int)m_data->m_links[linkIndex]->visual_array.size(); v++)
    {
        const Visual* vis = m_data->m_links[linkIndex]->visual_array[v].get();
        btVector3 childPos(vis->origin.position.x, vis->origin.position.y, vis->origin.position.z);
        btQuaternion childOrn(vis->origin.rotation.x, vis->origin.rotation.y, vis->origin.rotation.z, vis->origin.rotation.w);
        btTransform childTrans;
        childTrans.setOrigin(childPos);
        childTrans.setRotation(childOrn);
            
        ROSconvertURDFToVisualShape(vis, pathPrefix, inertialFrame.inverse()*childTrans, vertices, indices);
            
    }
        
    if (vertices.size() && indices.size())
    {
        graphicsIndex  = m_data->m_guiHelper->registerGraphicsShape(&vertices[0].xyzw[0], vertices.size(), &indices[0], indices.size());
    }
        
    return graphicsIndex;
        
}