    /** * @brief Render the mesh given a camera and light, using a Phong shader 
     * @param mesh Given mesh
     * @param camera Given camera 
     * @param lightTrackball Given light camera 
     */
    void render (PointCloud& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        particletf_shader.bind();

        glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, 0);

        // Transform feedback 0
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[0]);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,0,mesh.getAttribute("in_Position")->getBufferID());
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,1,mesh.getAttribute("in_Velocity")->getBufferID());
        // posBuf[0] -> mesh.getAttribute("in_Position")->getBufferID()

        // Transform feedback 1
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[1]);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,0,mesh.getAttribute("in_Position")->getBufferID());
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,1,mesh.getAttribute("in_Velocity")->getBufferID());
//        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,1,velBuf[1]);
//        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,2,startTime[1]);

        // sets all uniform variables for the phong shader
        particletf_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
        particletf_shader.setUniform("modelMatrix", mesh.getModelMatrix());
        particletf_shader.setUniform("viewMatrix", camera.getViewMatrix());
        particletf_shader.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        particletf_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
        particletf_shader.setUniform("default_color", default_color);

        // Disable rendering
        glEnable(GL_RASTERIZER_DISCARD);
        int drawBuf = 0;
        // Bind the feedback object for the buffers to be drawn next
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[drawBuf]);

        mesh.setAttributeLocation(particletf_shader);

        glEnable(GL_DEPTH_TEST);
        mesh.render();

        particletf_shader.unbind();
//        glEndTransformFeedback();
    }