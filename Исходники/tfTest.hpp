    /** * @brief Render the mesh given a camera and light, using a Phong shader 
     * @param mesh Given mesh
     * @param camera Given camera 
     * @param lightTrackball Given light camera 
     */
    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        tftest_shader.bind();
            // sets all uniform variables for the phong shader
            tftest_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
            tftest_shader.setUniform("modelMatrix", mesh.getModelMatrix());
            tftest_shader.setUniform("viewMatrix", camera.getViewMatrix());
            tftest_shader.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
            tftest_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
            tftest_shader.setUniform("default_color", default_color);
            tftest_shader.setUniform("tf", 1.0);

            cout << "set attrib TF\n";
            mesh.setAttributeLocation(tftest_shader);
            glEnable(GL_RASTERIZER_DISCARD);


            mesh.bindBuffers();

                glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mesh.getAttribute("nPos")->getBufferID());

                glBeginTransformFeedback(GL_POINTS);
                glEnable(GL_DEPTH_TEST);
                mesh.renderPoints();

                glEndTransformFeedback();
                glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);
                mesh.unbindBuffers();
            glDisable(GL_RASTERIZER_DISCARD);
        tftest_shader.unbind();
    printActiveAttribs(tftest_shader.getShaderProgram(), "TF");
    printActiveAttribs(tfrender.getShaderProgram(), "RENDER");
//        RENDERING

        tfrender.bind();
            // sets all uniform variables for the phong shader
            tfrender.setUniform("projectionMatrix", camera.getProjectionMatrix());
            tfrender.setUniform("modelMatrix", mesh.getModelMatrix());
            tfrender.setUniform("viewMatrix", camera.getViewMatrix());
            tfrender.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
            tfrender.setUniform("has_color", mesh.hasAttribute("in_Color"));
            tfrender.setUniform("default_color", default_color);
//            tfrender.setUniform("tf", 1.0);

            cout << "set attrib RENDER\n";
            mesh.setAttributeLocation(tfrender);
            mesh.bindBuffers();
            mesh.renderElements();
            mesh.unbindBuffers();
        tfrender.unbind();


    }