//--------------------------------------------------------------
void ofxFatLine::pushNewVertex(ofVec3f v, ofVec3f p, ofVec3f r1, ofVec3f r2, float maxLength, int index, float cos, bool bFlipped){
    
    ofFloatColor c(colors[index]);
    c.a =0;
    if (cos == 0){
        cos = FLT_EPSILON;
    }
    r1.normalize();
    r2.normalize();
    bool bAligned = false;
    if (abs(cos) == 1) {
        bAligned = true;
        p = r1;
    }
    cos = 1/cos;
    
    midVectors.push_back(p);
    if (bFlipped) {
        p *=-1;
    }
    flippepMidVectors.push_back(p);
    if (bAligned) {
		cout << "vertexAligned" << endl;
		pushNewAnchors(v, p*-1, colors[index], weights[index], feathering, true);
        pushNewAnchor(v, colors[index]);
        pushNewAnchors(v, p, colors[index], weights[index], feathering, false);
        if (index != 0) {
            if (meshVertices.size() >5) {
                for (int i = meshVertices.size()-4; i<meshVertices.size(); i++) {
                    pushQuadIndices(i);
                }
            }
        }
        
    }else{
        
        if (midVectors.back().dot(r1)>0) {
            r1 *=-1;
        }
        if (midVectors.back().dot(r2)>0) {
            r2 *=-1;
        }    
        float midLength = weights[index]*cos;
        if (midLength > maxLength) {
            midLength = maxLength;
        }
        if (bFlipped) {
            pushNewAnchors(v, r1, colors[index], weights[index], feathering, !bFlipped);
            pushNewAnchors(v, midVectors.back(), colors[index], midLength, feathering*cos, bFlipped);
            pushNewAnchor(v, colors[index]);
            pushNewAnchors(v, r2, colors[index], weights[index], feathering, !bFlipped);
            
            
        }else{
            pushNewAnchors(v, r1, colors[index], weights[index], feathering, !bFlipped);
            pushNewAnchors(v, r2, colors[index], weights[index], feathering, !bFlipped);
            pushNewAnchor(v, colors[index]);
            pushNewAnchors(v, midVectors.back(), colors[index], midLength, feathering*cos, bFlipped);        
        }
        int l = meshVertices.size();
        if (l >11) {
            if (bFlipped) {
                pushQuadIndices(l - 12, l -11, l - 5, l - 4);
                pushQuadIndices(l - 11, l -10, l - 4, l - 3);
                pushQuadIndices(l - 10, l - 9, l - 3, l - 7);
                pushQuadIndices(l -  9, l - 8, l - 7, l - 6);
            }else{
                pushQuadIndices(l - 12, l -11, l - 7, l - 6);
                pushQuadIndices(l - 11, l -10, l - 6, l - 3);
                pushQuadIndices(l - 10, l - 9, l - 3, l - 2);
                pushQuadIndices(l -  9, l - 8, l - 2, l - 1);
            }
        }
        updateJoint(index,bFlipped);
    }

    /*
     ofVec3f pp = p * 50 * cos;
     ofVec3f pa = pp + p * 2 * cos;
     
     meshVertices.push_back(pa + v);
     meshColors.push_back(c);
     
     meshVertices.push_back(pp + v);
     meshColors.push_back(colors[index]); 
     
     meshVertices.push_back(v);
     meshColors.push_back(colors[index]);
     
     meshVertices.push_back(v - pp);
     meshColors.push_back(colors[index]);
     
     meshVertices.push_back(v - pa);
     meshColors.push_back(c);
     
     if (meshVertices.size() >5) {
     for (int i = meshVertices.size()-4; i<meshVertices.size(); i++) {
     pushQuadIndices(i);
     }
     }
     //*/
    
}