    /**
     * @brief Renders the given texture.
     *
     * Renders the given texture using a proxy geometry, a quad the size of the viewport
     * to hold the texture.
     */
    void renderTexture (Texture& tex, Eigen::Vector2i viewport)
    {
        glViewport(0, 0, viewport[0], viewport[1]);

        shader.bind();
        shader.setUniform("imageTexture", tex.bind());
        shader.setUniform("viewportSize", viewport);
        quad.render();

        shader.unbind();
        tex.unbind();
    }