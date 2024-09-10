void SeaSurface:: draw(){

    float globalOpacityMod = 1.0f;
    
    globalOpacityMod = -(offset.y + 6000) * 0.002f;
    if( globalOpacityMod >= 1.0f ) globalOpacityMod = 1.0f;
    
    for(int n = 0; n < rows.size(); n++){
        Path2d path;
        path.moveTo( paths.at(n).at(0) );
        for(int i = 1; i < paths.at(n).size(); i++ )
            path.lineTo( paths.at(n).at(i) );
        path.lineTo( vec2( cinder::app::getWindowWidth(), 0.0 ) );
        path.lineTo( vec2( 0.0, 0.0 ) );
        path.close();
        gl::color(ColorA8u(237,160, 135, rows.at(n)->depth * 20.0f * globalOpacityMod ) );
        gl::drawSolid(path);
        gl::draw(path);
    }
}