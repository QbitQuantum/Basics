void display(void)
{

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // glViewport(0,0,VOXELNUM,VOXELNUM);
    shader.bind();

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_3D, texID[0]);

    glUniform1i(shader.shaderUniform("my_color_texture"), 0);
    glUniformMatrix4fv(shader.shaderUniform("Transform"), 1, GL_FALSE, glm::value_ptr(MVP));

    glBindVertexArray(gVAO);
    glDrawArrays(GL_POINTS, 0, 4);
    glDrawArrays(GL_POINTS, 4, 4);
    glBindVertexArray(0); // Unbind our Vertex Array Object
    utilCheckGLError("3");

    shader.unbind();

    glutSwapBuffers();
}