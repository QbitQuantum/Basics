void IndexMap::predictIndices(const Eigen::Matrix4f & pose,
                              const int & time,
                              const std::pair<GLuint, GLuint> & model,
                              const float depthCutoff,
                              const int timeDelta)
{
    indexFrameBuffer.Bind();

    glPushAttrib(GL_VIEWPORT_BIT);

    glViewport(0, 0, indexRenderBuffer.width, indexRenderBuffer.height);

    glClearColor(0, 0, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    indexProgram->Bind();

    Eigen::Matrix4f t_inv = pose.inverse();

    Eigen::Vector4f cam(Intrinsics::getInstance().cx() * IndexMap::FACTOR,
                  Intrinsics::getInstance().cy() * IndexMap::FACTOR,
                  Intrinsics::getInstance().fx() * IndexMap::FACTOR,
                  Intrinsics::getInstance().fy() * IndexMap::FACTOR);

    indexProgram->setUniform(Uniform("t_inv", t_inv));
    indexProgram->setUniform(Uniform("cam", cam));
    indexProgram->setUniform(Uniform("maxDepth", depthCutoff));
    indexProgram->setUniform(Uniform("cols", (float)Resolution::getInstance().cols() * IndexMap::FACTOR));
    indexProgram->setUniform(Uniform("rows", (float)Resolution::getInstance().rows() * IndexMap::FACTOR));
    indexProgram->setUniform(Uniform("time", time));
    indexProgram->setUniform(Uniform("timeDelta", timeDelta));

    glBindBuffer(GL_ARRAY_BUFFER, model.first);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, Vertex::SIZE, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, Vertex::SIZE, reinterpret_cast<GLvoid*>(sizeof(Eigen::Vector4f)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, Vertex::SIZE, reinterpret_cast<GLvoid*>(sizeof(Eigen::Vector4f) * 2));

    glDrawTransformFeedback(GL_POINTS, model.second);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    indexFrameBuffer.Unbind();

    indexProgram->Unbind();

    glPopAttrib();

    glFinish();
}