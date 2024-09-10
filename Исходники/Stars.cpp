void Stars::render(float fovY, float aspect, float nearZ, float alpha) {
    // determine length of screen diagonal from quadrant height and aspect ratio
    float quadrantHeight = nearZ * tanf(RADIANS_PER_DEGREE * fovY * 0.5f);
    float halfDiagonal = sqrt(quadrantHeight * quadrantHeight * (1.0f + aspect * aspect));

    // determine fov angle in respect to the diagonal
    float fovDiagonal = atanf(halfDiagonal / nearZ) * 2.0f;

    // pull the modelview matrix off the GL stack
    glm::mat4 view;
    glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(view));

    _controller->render(fovDiagonal, aspect, glm::affineInverse(view), alpha);
}