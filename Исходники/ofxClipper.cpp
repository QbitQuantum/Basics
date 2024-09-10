//--------------------------------------------------------------
ClipperLib::Polygon ofxClipper::ofPolyline_to_Polygon(ofPolyline& polyline) {
	vector<ofPoint> verts = polyline.getVertices();
    vector<ofPoint>::iterator iter;
    ClipperLib::Polygon polygon;
    for(iter = verts.begin(); iter != verts.end(); iter++) {
        ClipperLib::IntPoint ip((*iter).x * clipperGlobalScale, 
                                (*iter).y * clipperGlobalScale);
        polygon.push_back(ip);
    }
    return polygon;
}