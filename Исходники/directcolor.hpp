    /** * @brief Render the mesh given a camera 
     * @param mesh Given mesh
     * @param camera Given camera
     */
    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera)
    {

        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        directcolor_shader.bind();

        // sets all uniform variables for the phong shader
        directcolor_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
        directcolor_shader.setUniform("modelMatrix", mesh.getModelMatrix());
        directcolor_shader.setUniform("viewMatrix", camera.getViewMatrix());
        directcolor_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
		directcolor_shader.setUniform("default_color", default_color);

        mesh.setAttributeLocation(directcolor_shader);

        glEnable(GL_DEPTH_TEST);
        mesh.render();

        directcolor_shader.unbind();
    }