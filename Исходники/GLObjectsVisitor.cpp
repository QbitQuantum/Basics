void GLObjectsVisitor::compile(osg::Node& node)
{
    if (_renderInfo.getState())
    {
        node.accept(*this);

        if (_lastCompiledProgram.valid())
        {
            osg::State* state = _renderInfo.getState();
            osg::GLExtensions* extensions = state->get<osg::GLExtensions>();
            extensions->glUseProgram(0);
            _renderInfo.getState()->setLastAppliedProgramObject(0);
        }

        if (_checkGLErrors!=osg::State::NEVER_CHECK_GL_ERRORS) _renderInfo.getState()->checkGLErrors("after GLObjectsVisitor::compile(osg::Node& node)");
    }
}