    /** * @brief Render the mesh given a camera and light, using a Phong shader
     * @param mesh Given mesh
     * @param camera Given camera
     * @param lightTrackball Given light camera
     */
    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {

        if (read_va == NULL)
        {
            read_va = mesh.getAttribute("positions1");
            write_va = mesh.getAttribute("positions2");
        }

        if (read_va == NULL || write_va == NULL)
            qDebug() << "AHHH morri";

        updateTF(mesh, camera, lightTrackball);
        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
        simple.bind();
        // sets all uniform variables for the phong shader

        simple.setUniform("projectionMatrix", camera.getProjectionMatrix());
        simple.setUniform("modelMatrix", mesh.getModelMatrix());
        simple.setUniform("viewMatrix", camera.getViewMatrix());

        glEnable(GL_DEPTH_TEST);
        //mesh.setAttributeLocation(simple);
        mesh.bindBuffers();
//            mesh.resetLocations();
        //qDebug() << mesh.getAttribute("nPos")->getLocation();
        read_va->disable();
        write_va->enable(simple.getAttributeLocation("inPos"));


        mesh.setAttributeLocation("nColor",  simple.getAttributeLocation("inColor"));

        mesh.renderPoints();
        mesh.unbindBuffers();

        simple.unbind();

        VertexAttribute *tmp_va;
        tmp_va = read_va;
        read_va = write_va;
        write_va = tmp_va;
    }