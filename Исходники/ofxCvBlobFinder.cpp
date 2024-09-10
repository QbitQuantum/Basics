//----------------------------------------------------------------------------------
void ofxCvBlobFinder::draw(float x, float y, float w, float h) {
    
    // draw blobs
    //ofxCvContourFinder::draw(x, y, w, h);
    // scale blob
    float scalex = 0.0f;
    float scaley = 0.0f;
    
    if (_width != 0) {
        scalex = w / _width;
    }
    else {
        scalex = 1.0f;
    }
    
    if (_height != 0) {
        scaley = h / _height;
    }
    else {
        scaley = 1.0f;
    }
    
    
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    // apply transformation
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(scalex, scaley, 0.0);
    
    
#define DRAW_BLOB_VECTOR(points) do{ \
ofBeginShape(); \
for(int i = 0; i < (points).size(); i++){ \
ofVertex((points[i]).x, (points[i]).y); \
} \
ofEndShape(true); \
} while(0)
    
    ofNoFill();
    for (int j = 0; j < blobz.size(); j++) {
        ofSetHexColor(0xFF0000);
        DRAW_BLOB_VECTOR( blobz[j].getPoints());
        
        ofSetHexColor(0x00FF00);
        DRAW_BLOB_VECTOR(blobz[j].getHullPoints());
        
        ofSetHexColor(0x0000FF);
        DRAW_BLOB_VECTOR( blobz[j].getApproxPoints());
        
        ofSetHexColor(0x00ffae);
        ofRectangle c = blobz[j].getBoundingBox();
        
        
        // draw bounding box
        ostringstream s;
        s << j << "Area = " << blobz[j].getArea();
        
        ofDrawBitmapString(s.str(), c.x, c.y + 50);
        ofRect(c.x, c.y, c.width, c.height);
        
        // get convexity defects
        vector<ofxCvConvexityDefect> cd = blobz[j].getConvexityDefects();
        ofSetHexColor(0x00effe);
        for(int i=0; i < cd.size(); i++){
            ofLine(cd[i].start.x, cd[i].start.y, cd[i].end.x, cd[i].end.y);
            ofCircle(cd[i].defect.x, cd[i].defect.y, 2);
            float angle = atan2f( ( (float) (cd[i].end.y - cd[i].start.y) ) , ( (float) (cd[i].end.x - cd[i].start.x)));
            float x = cd[i].defect.x - sinf(angle) * cd[i].length;
            float y = cd[i].defect.y + cosf(angle) * cd[i].length;
            ofSetHexColor(0xF0F0F0);
            ofLine(cd[i].defect.x, cd[i].defect.y, x, y);
        }
    }
    
    for (int k = 0; k < blobParams.size(); k++){
        ofDrawBitmapString("Blob:" + ofToString(blobParams[k].id), blobParams[k].position);
    }
    
    glPopMatrix();
}