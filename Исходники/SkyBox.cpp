  void onFrame() {

    if (camera.isTransformed) {
      camera.transform();
    }

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cmt.bind(GL_TEXTURE0); {

      skyboxProgram.bind(); {
        glUniformMatrix4fv(skyboxProgram.uniform("view"), 1, 0, ptr(camera.view));
        glUniformMatrix4fv(skyboxProgram.uniform("proj"), 1, 0, ptr(camera.projection));
        glUniform1i(skyboxProgram.uniform("cube_texture"), 0);

        skyboxMeshBuffer.draw();
      } skyboxProgram.unbind();

      vec3 totals = rotateBehavior.tick(now()).totals();
      cubeModel = glm::mat4();
      cubeModel = glm::translate(cubeModel, vec3(12.0,0.0,40.0));
      cubeModel = glm::rotate(cubeModel, totals.x, vec3(1.0f,0.0f,0.0f));
      cubeModel = glm::rotate(cubeModel, totals.y, vec3(0.0f,1.0f,0.0f));

      dragonModel = glm::mat4();
      dragonModel = glm::translate(dragonModel, vec3(-12.0,-15.0,40.0));
      dragonModel = glm::rotate(dragonModel, totals.y, vec3(0.0f,1.0f,0.0f));


      environmentMappingProgram.bind(); {
        glUniformMatrix4fv(environmentMappingProgram.uniform("view"), 1, 0, ptr(camera.view));
        glUniformMatrix4fv(environmentMappingProgram.uniform("proj"), 1, 0, ptr(camera.projection));
        glUniform1i(environmentMappingProgram.uniform("cube_texture"), 0);

        //set dragon specific variables and draw dragon
        glUniformMatrix4fv(environmentMappingProgram.uniform("model"), 1, 0, ptr(dragonModel));
        glUniform4f(environmentMappingProgram.uniform("baseColor"), 0.0, 0.0, 0.1, 1.0);
        dragonMeshBuffer.draw();

        //set cube specific variables and draw cube
        glUniformMatrix4fv(environmentMappingProgram.uniform("model"), 1, 0, ptr(cubeModel));
        glUniform4f(environmentMappingProgram.uniform("baseColor"), 0.1, 0.0, 0.0, 1.0);
        cubeMeshBuffer.draw();
      } environmentMappingProgram.unbind();

    } cmt.unbind(GL_TEXTURE0);

  }