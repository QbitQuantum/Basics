bool HUDSettings::getInverseModelViewMatrix(osg::Matrix& matrix, osg::NodeVisitor* nv) const
{
    osg::Matrix modelView;
    getModelViewMatrix(modelView,nv);
    matrix.invert(modelView);
    return true;
}