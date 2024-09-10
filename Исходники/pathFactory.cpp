void pathFactory::mousePointerStraight(ofPath &p, float x_dim, float y_dim, float t_size){

    vector<ofPoint> tpoints;

    float tw = 0.3;
    float sw = 0.074;
    float cl = 1;
    float al = 0.74;
    float bl = 0.55;

    tpoints.push_back(ofPoint(0,0));
    tpoints.push_back(ofPoint(-tw,al));//a1
    tpoints.push_back(ofPoint(-sw,bl)); // b1
    tpoints.push_back(ofPoint(-sw,cl)); //c1
    tpoints.push_back(ofPoint(sw,cl));//c2
    tpoints.push_back(ofPoint(sw,bl)); // b2
    tpoints.push_back(ofPoint(tw,al)); //a2
    tpoints.push_back(ofPoint(0,0));


    for(int i = 0; i < tpoints.size(); i++){
        tpoints[i] *= ofVec2f(x_dim, y_dim);
        tpoints[i] *= t_size;
        p.lineTo(tpoints[i]);
    }

    p.close();

}