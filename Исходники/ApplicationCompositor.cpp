// Draws the FBO texture for Oculus rift.
void ApplicationCompositor::displayOverlayTextureHmd(RenderArgs* renderArgs, int eye) {
    if (_alpha == 0.0f) {
        return;
    }

    GLuint texture = qApp->getApplicationOverlay().getOverlayTexture();
    if (!texture) {
        return;
    }

    updateTooltips();

    vec2 canvasSize = qApp->getCanvasSize();
    _textureAspectRatio = aspect(canvasSize);

    renderArgs->_context->syncCache();
    auto geometryCache = DependencyManager::get<GeometryCache>();

    gpu::Batch batch;
    geometryCache->useSimpleDrawPipeline(batch);
    batch._glDisable(GL_DEPTH_TEST);
    batch._glDisable(GL_CULL_FACE);
    batch._glBindTexture(GL_TEXTURE_2D, texture);
    batch._glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    batch._glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    batch.setViewTransform(Transform());
    batch.setProjectionTransform(qApp->getEyeProjection(eye));

    mat4 eyePose = qApp->getEyePose(eye);
    glm::mat4 overlayXfm = glm::inverse(eyePose);

#ifdef DEBUG_OVERLAY
    {
        batch.setModelTransform(glm::translate(mat4(), vec3(0, 0, -2)));
        geometryCache->renderUnitQuad(batch, glm::vec4(1));
    }
#else
    {
        batch.setModelTransform(overlayXfm);
        drawSphereSection(batch);
    }
#endif

    // Doesn't actually render
    renderPointers(batch);
    vec3 reticleScale = vec3(Cursor::Manager::instance().getScale() * reticleSize);

    bindCursorTexture(batch);

    MyAvatar* myAvatar = DependencyManager::get<AvatarManager>()->getMyAvatar();
    //Controller Pointers
    for (int i = 0; i < (int)myAvatar->getHand()->getNumPalms(); i++) {
        PalmData& palm = myAvatar->getHand()->getPalms()[i];
        if (palm.isActive()) {
            glm::vec2 polar = getPolarCoordinates(palm);
            // Convert to quaternion
            mat4 pointerXfm = glm::mat4_cast(quat(vec3(polar.y, -polar.x, 0.0f))) * glm::translate(mat4(), vec3(0, 0, -1));
            mat4 reticleXfm = overlayXfm * pointerXfm;
            reticleXfm = glm::scale(reticleXfm, reticleScale);
            batch.setModelTransform(reticleXfm);
            // Render reticle at location
            geometryCache->renderUnitQuad(batch, glm::vec4(1), _reticleQuad);
        }
    }

    //Mouse Pointer
    if (_reticleActive[MOUSE]) {
        glm::vec2 projection = screenToSpherical(glm::vec2(_reticlePosition[MOUSE].x(),
            _reticlePosition[MOUSE].y()));
        mat4 pointerXfm = glm::mat4_cast(quat(vec3(-projection.y, projection.x, 0.0f))) * glm::translate(mat4(), vec3(0, 0, -1));
        mat4 reticleXfm = overlayXfm * pointerXfm;
        reticleXfm = glm::scale(reticleXfm, reticleScale);
        batch.setModelTransform(reticleXfm);
        geometryCache->renderUnitQuad(batch, glm::vec4(1), _reticleQuad);
    }
    
    renderArgs->_context->render(batch);
}