    /**
     * @brief Render the mesh given a camera and light trackball, using a Toon shader
     * @param mesh Given mesh
     * @param cameraTrackball Given camera trackball
     * @param lightTrackball Given light trackball
     */
    virtual void render (Tucano::Mesh& mesh, const Tucano::Trackball& cameraTrackball, const Tucano::Trackball& lightTrackball)
	{       

        Eigen::Vector4f viewport = cameraTrackball.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        toon_shader.bind();

        toon_shader.setUniform("projectionMatrix", cameraTrackball.getProjectionMatrix());
        toon_shader.setUniform("modelMatrix", mesh.getModelMatrix());
        toon_shader.setUniform("viewMatrix", cameraTrackball.getViewMatrix());
        toon_shader.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        toon_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
        toon_shader.setUniform("quantizationLevel", quantization_level);

        mesh.setAttributeLocation(toon_shader);
		mesh.render();

        toon_shader.unbind();
	}