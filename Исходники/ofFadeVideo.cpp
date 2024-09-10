void ofFadeVid::setup(string filename_in) {
    setPixelFormat(OF_PIXELS_RGBA);
    ofEnableAlphaBlending();
    alpha = 0.0f;
    alphaDest = 1.0f;
    loadMovie(filename_in);
}