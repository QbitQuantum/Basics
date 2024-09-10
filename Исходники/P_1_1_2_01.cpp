void P_1_1_2_01::keyDown( KeyEvent event ){
    char keyPressed = event.getChar();
    switch (keyPressed) {
        case '1':{
            segmentCount = 360.f;
            break;
        }
        case '2':{
            segmentCount = 36.f;
        }
            break;
        case '3':{
            segmentCount = 18.f;
        }
            break;
        case '4':{
            segmentCount = 12.f;
        }
            break;
        case '5':{
            segmentCount = 6.f;
        }
            break;
        case 's':
        case 'S':{
            vector<std::string> fileTypes;
            fileTypes.push_back("png");
            fs::path path = getSaveFilePath("", fileTypes);
            writeImage( path.string() , copyWindowSurface() );
            break;
        }
    }
}