void CLineComputeView::glDrawCnString(CString str, GLfloat *position) {
    int len = str.GetLength();
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);

    // 逐个输出字符
    glTranslatef(position[0], position[1], position[2]);
    glRasterPos2f(0.0f, 0.05f);
    for(int i=0; i<len; ++i)
    {
        wglUseFontBitmapsW(hDC, str[i], 1, list);
        glCallList(list);
    }
    glTranslatef(-position[0], -position[1], -position[2]);
    glDeleteLists(list, 1);
}