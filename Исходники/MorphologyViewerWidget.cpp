void
MorphologyViewerWidget::_get_transformation( unsigned int index
                                           , osg::Vec3d  & eye
                                           , osg::Vec3d  & center
                                           , double      & distance
                                           , osg::Vec3d  & up
                                           , osg::Vec3d  & look
                                           , osg::Vec3d  & side
                                           )
{
    osgViewer::View * view = _viewer -> getView(index);
    osgGA::TrackballManipulator * manipulator = dynamic_cast<osgGA::TrackballManipulator *>(view -> getCameraManipulator());
    manipulator -> getTransformation(eye, center, up);
    up.normalize();
    look = center - eye;
    distance = look.normalize();
    side = look ^ up;
    side.normalize();
}