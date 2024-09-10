SoPickedPoint* ViewProvider::getPointOnRay(const SbVec3f& pos,const SbVec3f& dir, const View3DInventorViewer* viewer) const
{
    // Note: There seems to be a  bug with setRay() which causes SoRayPickAction
    // to fail to get intersections between the ray and a line
    
    //first get the path to this node and calculate the current setTransformation
    SoSearchAction sa;
    sa.setNode(pcRoot);
    sa.setSearchingAll(true);
    sa.apply(viewer->getSoRenderManager()->getSceneGraph());
    SoGetMatrixAction gm(viewer->getSoRenderManager()->getViewportRegion());
    gm.apply(sa.getPath());
    
    // build a temporary scenegraph only keeping this viewproviders nodes and the accumulated 
    // transformation
    SoTransform* trans = new SoTransform;
    trans->ref();
    trans->setMatrix(gm.getMatrix());
    
    SoSeparator* root = new SoSeparator;
    root->ref();
    root->addChild(viewer->getSoRenderManager()->getCamera());
    root->addChild(trans);
    root->addChild(pcRoot);
    
    //get the picked point
    SoRayPickAction rp(viewer->getSoRenderManager()->getViewportRegion());
    rp.setRay(pos,dir);
    rp.setRadius(viewer->getPickRadius());
    rp.apply(root);
    root->unref();
    trans->unref();

    // returns a copy of the point
    SoPickedPoint* pick = rp.getPickedPoint();
    //return (pick ? pick->copy() : 0); // needs the same instance of CRT under MS Windows
    return (pick ? new SoPickedPoint(*pick) : 0);
}