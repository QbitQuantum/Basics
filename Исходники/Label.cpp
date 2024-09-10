void Label::update()
{
    updateText();
    blendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    
    if (getObject()) {
        m_transform->copy(getObject()->getTransInWorld());
    }
    else {
        m_transform->copy(GLCanvas::GetInstance()->getGlobalTrans());
    }
    float lastX=0;
    for (TextFrame* frame : m_allTextFrames) {
        Transform orgin;
        orgin.copy(m_transform);
        Transform offst;
        offst.setX(lastX);
        offst.setY(m_fontSize-frame->getBearingY());
        offst.flush();
        orgin.setWidth(frame->getWidth());
        orgin.setHeight(frame->getHeight());
        orgin.transform(&offst);
        
        GLCanvas::GetInstance()->paint(frame, &orgin, &m_color, m_program);
        lastX += frame->getAdvance();
    }
}