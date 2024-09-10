//--------------------------------------------------
void ofPolyline::calcData(int index, ofVec3f &tangent, float &angle, ofVec3f &rotation, ofVec3f &normal) const {
    int i1 = getWrappedIndex(index - 1);
    int i2 = getWrappedIndex(index);
    int i3 = getWrappedIndex(index + 1);
    
    ofPoint p1(points[i1]);
    ofPoint p2(points[i2]);
    ofPoint p3(points[i3]);
    
    ofVec3f v1(p1 - p2); // vector to previous point
    ofVec3f v2(p3 - p2); // vector to next point
    v1.normalize();
    v2.normalize();
    
    tangent = (v2 - v1);
    tangent.normalize();
    
    rotation = v1.getCrossed(v2);
    angle = 180 - ofRadToDeg(acos(ofClamp(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z, -1, 1)));

    normal = rightVector.getCrossed(tangent);
    normal.normalize();
}