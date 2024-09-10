    /** * @brief Render the mesh given a camera and light, using a Phong shader 
     * @param mesh Given mesh
     * @param camera Given camera 
     * @param lightTrackball Given light camera 
     */
    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {

        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        depthmap_shader.bind();

        // sets all uniform variables for the phong shader
        depthmap_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
        depthmap_shader.setUniform("modelMatrix", mesh.getModelMatrix());
        depthmap_shader.setUniform("viewMatrix", camera.getViewMatrix());
        depthmap_shader.setUniform("near", 0.1);
        depthmap_shader.setUniform("far", 10000.0);

//        std::cout << "Model" << std::endl;
//        std::cout << mesh.getModelMatrix().matrix() << std::endl;

//        std::cout << "View" << std::endl;
//        std::cout << camera.getViewMatrix().matrix() << std::endl;

        mesh.setAttributeLocation(depthmap_shader);

        glEnable(GL_DEPTH_TEST);
        mesh.render();

        depthmap_shader.unbind();
    }