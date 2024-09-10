void CloudsVisualSystemLSystem::buildLSystem(){
    //  Clear
    //
    lsysLines.clear();
    lsysLines.push_back(ofPolyline());
    lsysNodes.clear();
    lsysOriginal.clear();
    
    LSystem sys;
    sys.initialPos.set(0,0);
    sys.unoise = 0.0;
    sys.utime = 0.0;
    
    sys.ds = lsysScale;
    sys.setAngle( lsysAngle );
    sys.addAxion( lsysAxiom );
    sys.addRule( lsysRule1 );
    if (lsysRule2.size() > 0){
        sys.addRule( lsysRule2);
    }

    sys.make( lsysDepth );
    
    lsysOriginal = sys.mesh;
    
    if ( lsysOriginal.getVertices().size() > 2){
        lineTo( lsysOriginal.getVertices()[0] );
        addNode( lsysOriginal.getVertices()[0] );
        
        for (int i = 1; i < lsysOriginal.getVertices().size();i++){
            if ( i%2 == 1){
                lineTo( lsysOriginal.getVertices()[i]);
            } else {
                if ( lsysOriginal.getVertices()[i] != lsysOriginal.getVertices()[i-1]){
                    lsysLines.push_back(ofPolyline());
                    lineTo( lsysOriginal.getVertices()[i] );
                    addNode( lsysOriginal.getVertices()[i] );
                }
            }
        }
    }
    
    if ( lsysNodes.size() > 0){
        lsysNodes[0].startTime = 0;
    }
}