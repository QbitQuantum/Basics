ofPoint SuperGlyph::getGetClosePath(ofPoint _pos){
    
    ofPoint normal;
    ofPoint target;
    float minDist = 1000000;
    
    for (int i = 0; i < insidePath.getVertices().size()-1; i++) {
        
        ofPoint a = insidePath.getVertices()[i];
        ofPoint b = insidePath.getVertices()[i+1];
        
        ofPoint normalPoint = getNormalPoint(_pos, a, b);
        
        if (normalPoint.x < a.x || normalPoint.x > b.x) {
            normalPoint = b;
        }
        
        float distance = _pos.distance(normalPoint);
        
        if (distance < minDist) {
            minDist = distance;
            
            normal = normalPoint;
            
            ofPoint dir = b - a;
            dir.normalize();
            
            dir *= 10;
            target = normalPoint;
            target += dir;
        }
    }
    
    return target;
}