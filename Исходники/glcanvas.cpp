wxGLContext::wxGLContext(wxGLCanvas *win, const wxGLContext* other)
{
    m_glContext = wglCreateContext(win->GetHDC());
    wxCHECK_RET( m_glContext, wxT("Couldn't create OpenGL context") );

    if ( other )
    {
        if ( !wglShareLists(other->m_glContext, m_glContext) )
            wxLogLastError(_T("wglShareLists"));
    }
}