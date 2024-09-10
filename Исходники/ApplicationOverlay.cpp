// Draws the FBO texture for 3DTV.
void ApplicationOverlay::displayOverlayTexture3DTV(Camera& whichCamera, float aspectRatio, float fov) {
    if (_alpha == 0.0f) {
        return;
    }
    
    Application* application = Application::getInstance();
    
    MyAvatar* myAvatar = application->getAvatar();
    const glm::vec3& viewMatrixTranslation = application->getViewMatrixTranslation();
    
    glActiveTexture(GL_TEXTURE0);
    
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_CONSTANT_ALPHA, GL_ONE);
    _overlays.bindTexture();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glLoadIdentity();
    // Transform to world space
    glm::quat rotation = whichCamera.getRotation();
    glm::vec3 axis2 = glm::axis(rotation);
    glRotatef(-glm::degrees(glm::angle(rotation)), axis2.x, axis2.y, axis2.z);
    glTranslatef(viewMatrixTranslation.x, viewMatrixTranslation.y, viewMatrixTranslation.z);
    
    // Translate to the front of the camera
    glm::vec3 pos = whichCamera.getPosition();
    glm::quat rot = myAvatar->getOrientation();
    glm::vec3 axis = glm::axis(rot);
    
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(glm::degrees(glm::angle(rot)), axis.x, axis.y, axis.z);
    
    glColor4f(1.0f, 1.0f, 1.0f, _alpha);
    
    //Render
    const GLfloat distance = 1.0f;
    
    const GLfloat halfQuadHeight = distance * tan(fov);
    const GLfloat halfQuadWidth = halfQuadHeight * aspectRatio;
    const GLfloat quadWidth = halfQuadWidth * 2.0f;
    const GLfloat quadHeight = halfQuadHeight * 2.0f;
    
    GLfloat x = -halfQuadWidth;
    GLfloat y = -halfQuadHeight;
    glDisable(GL_DEPTH_TEST);
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + quadHeight, -distance);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + quadWidth, y + quadHeight, -distance);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + quadWidth, y, -distance);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, -distance);
    
    glEnd();
    
    if (_crosshairTexture == 0) {
        _crosshairTexture = Application::getInstance()->getGLWidget()->bindTexture(QImage(Application::resourcesPath() + "images/sixense-reticle.png"));
    }
    
    //draw the mouse pointer
    glBindTexture(GL_TEXTURE_2D, _crosshairTexture);
    
    const float reticleSize = 40.0f / application->getGLWidget()->width() * quadWidth;
    x -= reticleSize / 2.0f;
    y += reticleSize / 2.0f;
    const float mouseX = (application->getMouseX() / (float)application->getGLWidget()->width()) * quadWidth;
    const float mouseY = (1.0 - (application->getMouseY() / (float)application->getGLWidget()->height())) * quadHeight;
    
    glBegin(GL_QUADS);
    
    glColor3f(RETICLE_COLOR[0], RETICLE_COLOR[1], RETICLE_COLOR[2]);
    
    glTexCoord2d(0.0f, 0.0f); glVertex3f(x + mouseX, y + mouseY, -distance);
    glTexCoord2d(1.0f, 0.0f); glVertex3f(x + mouseX + reticleSize, y + mouseY, -distance);
    glTexCoord2d(1.0f, 1.0f); glVertex3f(x + mouseX + reticleSize, y + mouseY - reticleSize, -distance);
    glTexCoord2d(0.0f, 1.0f); glVertex3f(x + mouseX, y + mouseY - reticleSize, -distance);
    
    glEnd();
    
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    
    glDepthMask(GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_CONSTANT_ALPHA, GL_ONE);
    glEnable(GL_LIGHTING);
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}