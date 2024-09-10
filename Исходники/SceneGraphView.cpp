void SceneGraphViewImpl::onSceneGraphUpdated(const SgUpdate& update)
{
    if(update.action() & (SgUpdate::ADDED)){
        parentItem = rootItem;
        SgUpdate::Path path = update.path();
        if(path.size() > 1){
            for(SgUpdate::Path::reverse_iterator it = ++path.rbegin(); it != path.rend(); ++it){
                parentItem = findItem(parentItem, *it);
                if(!parentItem)
                    return;
            }
        }

        SgObject* parent = update.path().front();
        SgGroup* group = dynamic_cast<SgGroup*>(parent);
        if(group){
            SgNode* node = findAddNode(group);
            if(node){
                node->accept(*this);
            }
        }
    }
    if(update.action() & (SgUpdate::REMOVED)){
        parentItem = rootItem;
        SgUpdate::Path path = update.path();
        if(path.size() > 1){
            for(SgUpdate::Path::reverse_iterator it = ++path.rbegin(); it != path.rend(); ++it){
                parentItem = findItem(parentItem, *it);
                if(!parentItem)
                    return;
            }
        }

        SgObject* parent = update.path().front();
        SgGroup* group = dynamic_cast<SgGroup*>(parent);
        if(group){
            SgvItem* item = findRemoveItem(group);
            if(item){
                removeItem(item);
            }
        }
    }
}