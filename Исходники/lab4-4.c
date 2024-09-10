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

    calculateCullingFrustum(camMatrix);
    
	modelView = IdentityMatrix();
	total = Mult(camMatrix, modelView);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, total.m);

    glUniform3f(glGetUniformLocation(program, "camPos"), cam.x, cam.y, cam.z);

	glBindTexture(GL_TEXTURE_2D, tex1);		// Bind Our Texture tex1
	DrawModel(tm, program, "inPosition", "inNormal", "inTexCoord");

    /*

    mat4 foobar = Mult(modelView, camMatrix);
    */
    GLfloat ballY = GetMapHeight(tm,ttex.width, ttex.height, ballX, ballZ);
    if (sphereInFrustum((vec3) {ballX, ballY, ballZ}, 10.0f)) {
        modelView = T(ballX, ballY, ballZ);
        total = Mult(camMatrix, modelView);
        glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, total.m);
        DrawModel(m2, program, "inPosition", "inNormal", "inTexCoord");
        printf("foo\n");
    }
	printError("display 2");
	glutSwapBuffers();
}