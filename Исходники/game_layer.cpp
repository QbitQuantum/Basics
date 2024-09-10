void GameLayer::showConnectPath(const Path& path) {
    set<string> isShown;
    isShown.insert(positionToKey(path.getPath().front()->getX(), path.getPath().front()->getY()));
    isShown.insert(positionToKey(path.getPath().back()->getX(), path.getPath().back()->getY()));
    
    setConnectAnimationCount(0);
    
    for (auto iterator=path.getPath().end()-1; iterator > path.getPath().begin(); iterator--) {
        PathElement* p1 = (*iterator);
        PathElement* p2 = (*(iterator-1));
        
        CCASSERT(p1->getX()==p2->getX()||p1->getY()==p2->getY(), "");
        if (p1->getX() == p2->getX()) {
            int minY = min(p1->getY(), p2->getY());
            int maxY = max(p1->getY(), p2->getY());
            for (int y=minY; y <= maxY; y++) {
                string key = positionToKey(p1->getX(), y);
                if (std::find(isShown.begin(), isShown.end(), key) != isShown.end()) {
                    continue;
                }

                isShown.insert(key);
                
                Node* layerColor = createConnectBackgroundTile(p1->getX(), y);
                m_backgroundLayer->addChild(layerColor);
            }
        } else {
            int minX = min(p1->getX(), p2->getX());
            int maxX = max(p1->getX(), p2->getX());
            for (int x=minX; x <= maxX; x++) {
                string key = positionToKey(x, p1->getY());
                if (std::find(isShown.begin(), isShown.end(), key) != isShown.end()) {
                    continue;
                }
                isShown.insert(key);
                
                Node* layerColor = createConnectBackgroundTile(x, p1->getY());
                
                m_backgroundLayer->addChild(layerColor);
            }
        }
    }
}