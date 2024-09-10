static 
void updateSpecialParameter(
    OSG::SHLChunk::GetUniformLocProc  getUniformLocation,
    OSG::DrawEnv                     *action, 
    GLuint                            program           )
{
#if 0
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("updateSpecialParameter : Can't update OSGSpecialParameter"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    // uploads the camera orientation.
    OSG::Matrix m;
    action->getCamera()->getViewing(m,
                                action->getViewport()->getPixelWidth(),
                                action->getViewport()->getPixelHeight());
    m.invert();
    m[3].setValues(0, 0, 0, 1);

    //std::cout << "uploading matrix " << m << std::endl;

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = 
        reinterpret_cast<OSGGLUNIFORMMATRIXFVARBPROC>(
            action->getWindow()->getFunction(
                OSG::SHLChunk::getFuncUniformMatrix4fv()));

    GLint location = getUniformLocation(program, "OSGSpecialParameter");

    if(location != -1)
        uniformMatrix4fv(location, 1, GL_FALSE, m.getValues());
#endif
}