void SE_NewGeometry::updateWorldTransform()
{
    SE_Spatial::updateWorldTransform();
    SE_Matrix4f localM;
    localM.set(getLocalRotate().toMatrix3f(), getLocalScale(), getLocalTranslate());
    mWorldTransform = getPrevMatrix().mul(localM).mul(getPostMatrix());
    SE_NewGeometry::_Impl::SimObjectList::iterator it;
    for(it = mImpl->attachObject.begin() ; it != mImpl->attachObject.end() ; it++)
    {
        (*it)->doTransform(getWorldTransform());
    }
    std::list<SE_Spatial*>::iterator itchild = mImplchild->children.begin();
    for(; itchild != mImplchild->children.end() ; itchild++)
    {
        SE_Spatial* s = *itchild;
        s->updateWorldTransform();
    }
}