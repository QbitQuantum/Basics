// This sets up "OpenGL" for us -- If an error occurs the method returns false
// otherwise the method returns true
bool CGLObj::init(HDC win_hdc, GLint colorBits, GLint depthBits)
{
    // Error check
    if(!win_hdc)
        return false;

    // DO NOT allow double initialization
    if(hglrc)
        return false;

    hdc = win_hdc; // Save off the window's HDC

    // Set the pixel format
    if(!setPixelFormat(colorBits, depthBits))
        return false;

    // Set the render context
    if(!setRenderContext())
        return false;

    // Enable flags we want
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    return true; // OpenGL is up and running :)
}