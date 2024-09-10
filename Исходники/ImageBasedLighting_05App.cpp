void ImageBasedLighting_05App::keyDown(KeyEvent event) {
    if(event.getChar() == 's') {
        std::string s = std::to_string(count);
        count++;
        writeImage("pbr"+s+".png", copyWindowSurface());
    }
}