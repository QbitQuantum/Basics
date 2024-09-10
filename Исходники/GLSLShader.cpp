GLvoid CGLES3Context::CreateProgramObject(GLuint progId)
{
    CProgramObj *pProgram = FindProgram(progId);

    if (pProgram)
    {
        ClearProgram(pProgram);
        return;
    }

    pProgram = new CProgramObj(progId);
    if (pProgram)
    {
        programMap.insert(std::make_pair(progId, pProgram));
    }
    else
    {
        Abort("Cannot allocate program object.\n");
    }
}