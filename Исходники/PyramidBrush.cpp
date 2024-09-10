vector<ofVec2f> PyramidBrush::sortClosest(ofVec2f p, vector<ofVec2f> coords){
    vector<ofVec2f> pos;
    float maxDist = ofGetWidth();
    int closestIndex = 0;
    for (int i = 0; i < coords.size(); i++) {
        float dist = p.distance(coords[i]);
        if (dist < maxDist){
            maxDist = dist;
            pos.push_back(coords[i]);
        }
    }
    return pos;
}