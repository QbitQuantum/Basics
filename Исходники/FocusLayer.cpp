bool FocusLayer::onTouchBegan(Touch* t, Event* e)
{
    auto pt = t->getLocation();
    
    for(auto rc : _rectList) {
        if(rc.second._rect.containsPoint(pt)) {
            log("rect touch");
            if(rc.second._callback)
                rc.second._callback(rc.first);
            
            return false;
        }
    }
    
    for(auto circle : _circleList) {
        Vec2 pos = circle.second._pos;
        float radius = circle.second._radius;
        
        float distance = pos.distance(pt);
        if(distance < radius) {
            log("circle touch");
            if(circle.second._callback)
                circle.second._callback(circle.first);
            
            return false;
        }
    }
    
    return true;
}