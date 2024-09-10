void CreditsWnd::Render() {
    if (!m_render)
        return;
    GG::Pt ul = UpperLeft(), lr = LowerRight();
    if (m_display_list_id == 0) {
        // compile credits
        m_display_list_id = glGenLists(1);
        glNewList(m_display_list_id, GL_COMPILE);
        DrawCredits(ul.x + m_cx, ul.y + m_cy, ul.x + m_cx + m_cw, ul.y + m_cy + m_ch, 255);
        glEndList();
    }
    //time passed
    int ticks_delta = GG::GUI::GetGUI()->Ticks() - m_start_time + m_scroll_offset;

    //draw background
    GG::FlatRectangle(ul, lr, GG::FloatClr(0.0f, 0.0f, 0.0f, 0.5f), GG::CLR_ZERO, 0);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    // define clip area
    glEnable(GL_SCISSOR_TEST);
    glScissor(Value(ul.x + m_cx), Value(GG::GUI::GetGUI()->AppHeight() - lr.y), m_cw, m_ch);

    // move credits
    glTranslatef(0, m_co - ticks_delta/40, 0);

    if (m_display_list_id != 0) {
        // draw credits using prepared display list
        // !!! in order for the display list to be valid, the font object (m_font) may not be destroyed !!!
        glCallList(m_display_list_id);
    } else {
        // draw credits directly
        DrawCredits(ul.x + m_cx, ul.y + m_cy, ul.x + m_cx + m_cw, ul.y + m_cy + m_ch, 255);
    }

    glPopMatrix();
    glPopAttrib();

    //check if we are done
    if (m_credits_height + m_ch < m_co + ticks_delta/40)
        OnExit();
}