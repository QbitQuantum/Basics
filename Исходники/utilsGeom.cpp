 //-------------------------------------------------------------------
 static ofVec2f getTriangleCenter(ofVec2f v1, ofVec2f v2, ofVec2f v3) {
     
     float a = v2.distance(v3);
     float b = v1.distance(v3);
     float c = v1.distance(v2);
     float d = a+b+c;
     
     float ix = ((a * v1.x) + (b * v2.x) + (c * v3.x)) / d;
     float iy = ((a * v1.y) + (b * v2.y) + (c * v3.y)) / d;
     
     return ofVec2f(ix, iy);
 }