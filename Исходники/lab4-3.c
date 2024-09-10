void display(void)
{
    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4 total, modelView, camMatrix;

    printError("pre display");

    glUseProgram(program);

    // Build matrix
    lookAtPoint = VectorAdd(cam, camDir);
    camMatrix = lookAt(cam.x, cam.y, cam.z,
                       lookAtPoint.x, lookAtPoint.y, lookAtPoint.z,
                       0.0, 1.0, 0.0);
    modelView = IdentityMatrix();
    total = Mult(camMatrix, modelView);
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, total.m);

    glUniform3f(glGetUniformLocation(program, "camPos"), cam.x, cam.y, cam.z);

    glBindTexture(GL_TEXTURE_2D, tex1);         // Bind Our Texture tex1



    DrawModel(tm, program, "inPosition", "inNormal", "inTexCoord");

    /*modelView = T(10.f, 30.f, 10.f);
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, modelView.m);
    DrawModel(m, program, "inPosition", "inNormal", "inTexCoord");*/

    if (sphereInFrustum((vec3) {-10.f, 30.f, 10.f}, 10.f)) {
        modelView = T(-10.f, 30.f, 10.f);
        glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, modelView.m);
        DrawModel(m2, program, "inPosition", "inNormal", "inTexCoord");
        printf("foo\n");
    }

    printError("display 2");
    glutSwapBuffers();
}