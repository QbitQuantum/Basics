//-------------------------------------------------------------------------------
bool CEditableMeshEditor::_pickVertex(Ogre::Ray& ray)
{
    Ogre::Real distance = 999999.0f;
    mCurrentVertex = 0;

    Ogre::Vector3 nodePos = mHandle->_getDerivedPosition();
    Ogre::Vector3 vertexPos;

    for(unsigned int i = 0;i < mVertexes.size();i++)
    {
        vertexPos = nodePos + mVertexes[i];
        Ogre::AxisAlignedBox box(vertexPos.x - 0.1f, vertexPos.y - 0.1f, vertexPos.z - 0.1f, vertexPos.x + 0.1f, vertexPos.y + 0.1f, vertexPos.z + 0.1f);
        std::pair<bool, Ogre::Real> result = ray.intersects(box);
        if(result.first && result.second < distance)
        {
            distance = result.second;
            mCurrentVertex = &(mVertexes[i]);
        }
    }
    
    if(distance < 999999.0f)
        return true;

    return false;
}