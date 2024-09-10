bool CameraControls::handleEvent(const Window::Event& ev)
{
    if (!m_commonControls)
        fail("CameraControls attached to a window without CommonControls!");
    CommonControls& cc = *m_commonControls;
    FW_ASSERT(m_window == ev.window || ev.type == Window::EventType_AddListener);

    // Initialize movement.

    Mat3f orient = getOrientation();
    Vec3f rotate = 0.0f;
    Vec3f move   = 0.0f;

    // Handle events.

    switch (ev.type)
    {
    case Window::EventType_AddListener:
        FW_ASSERT(!m_window);
        m_window = ev.window;
        m_timer.unstart();
        m_dragLeft = false;
        m_dragMiddle = false;
        m_dragRight = false;

        cc.addStateObject(this);
        addGUIControls();
        repaint();
        return false;

    case Window::EventType_RemoveListener:
        cc.removeStateObject(this);
        removeGUIControls();
        repaint();
        m_window = NULL;
        return false;

    case Window::EventType_KeyDown:
        if (ev.key == FW_KEY_MOUSE_LEFT)    m_dragLeft = true;
        if (ev.key == FW_KEY_MOUSE_MIDDLE)  m_dragMiddle = true;
        if (ev.key == FW_KEY_MOUSE_RIGHT)   m_dragRight = true;
        if (ev.key == FW_KEY_WHEEL_UP)      m_speed *= 1.2f;
        if (ev.key == FW_KEY_WHEEL_DOWN)    m_speed /= 1.2f;
        break;

    case Window::EventType_KeyUp:
        if (ev.key == FW_KEY_MOUSE_LEFT)    m_dragLeft = false;
        if (ev.key == FW_KEY_MOUSE_MIDDLE)  m_dragMiddle = false;
        if (ev.key == FW_KEY_MOUSE_RIGHT)   m_dragRight = false;
        break;

    case Window::EventType_Mouse:
        {
            Vec3f delta = Vec3f((F32)ev.mouseDelta.x, (F32)-ev.mouseDelta.y, 0.0f);
            if (m_dragLeft)     rotate += delta * s_mouseRotateSpeed;
            if (m_dragMiddle)   move += delta * m_speed * s_mouseStrafeSpeed;
            if (m_dragRight)    move += Vec3f(0.0f, 0.0f, (F32)ev.mouseDelta.y) * m_speed * s_mouseStrafeSpeed;
        }
        break;

    case Window::EventType_Paint:
        {
            F32     timeDelta   = m_timer.end();
            F32     boost       = cc.getKeyBoost();
            Vec3f   rotateTmp   = 0.0f;
            bool    alt         = m_window->isKeyDown(FW_KEY_ALT);

            if (m_window->isKeyDown(FW_KEY_A) || (m_window->isKeyDown(FW_KEY_LEFT) && alt))     move.x -= 1.0f;
            if (m_window->isKeyDown(FW_KEY_D) || (m_window->isKeyDown(FW_KEY_RIGHT) && alt))    move.x += 1.0f;
            if (m_window->isKeyDown(FW_KEY_F) || m_window->isKeyDown(FW_KEY_PAGE_DOWN))         move.y -= 1.0f;
            if (m_window->isKeyDown(FW_KEY_R) || m_window->isKeyDown(FW_KEY_PAGE_UP))           move.y += 1.0f;
            if (m_window->isKeyDown(FW_KEY_W) || (m_window->isKeyDown(FW_KEY_UP) && alt))       move.z -= 1.0f;
            if (m_window->isKeyDown(FW_KEY_S) || (m_window->isKeyDown(FW_KEY_DOWN) && alt))     move.z += 1.0f;

            if (m_window->isKeyDown(FW_KEY_LEFT) && !alt)                                       rotateTmp.x -= 1.0f;
            if (m_window->isKeyDown(FW_KEY_RIGHT) && !alt)                                      rotateTmp.x += 1.0f;
            if (m_window->isKeyDown(FW_KEY_DOWN) && !alt)                                       rotateTmp.y -= 1.0f;
            if (m_window->isKeyDown(FW_KEY_UP) && !alt)                                         rotateTmp.y += 1.0f;
            if (m_window->isKeyDown(FW_KEY_E) || m_window->isKeyDown(FW_KEY_HOME))              rotateTmp.z -= 1.0f;
            if (m_window->isKeyDown(FW_KEY_Q) || m_window->isKeyDown(FW_KEY_INSERT))            rotateTmp.z += 1.0f;

            move *= timeDelta * m_speed * boost;
            rotate += rotateTmp * timeDelta * s_keyRotateSpeed * boost;
        }
        break;

    default:
        break;
    }

    // Apply movement.

    if (m_enableMovement)
    {
    if (!move.isZero())
        m_position += orient * move;

    if (rotate.x != 0.0f || rotate.y != 0.0f)
    {
        Vec3f tmp = orient.col(2) * cos(rotate.x) - orient.col(0) * sin(rotate.x);
        m_forward = (orient.col(1) * sin(rotate.y) - tmp * cos(rotate.y)).normalized();
        if (!m_keepAligned)
            m_up = (orient.col(1) * cos(rotate.y) + tmp * sin(rotate.y)).normalized();
        else if (-m_forward.cross(m_up).dot(tmp.cross(m_up).normalized()) < s_inclinationLimit)
            m_forward = -tmp.normalized();
    }

    if (rotate.z != 0.0f && !m_keepAligned)
    {
        Vec3f up = orient.transposed() * m_up;
        m_up = orient * Vec3f(up.x * cos(rotate.z) - sin(rotate.z), up.x * sin(rotate.z) + up.y * cos(rotate.z), up.z);
    }
    }

    // Apply alignment.

    if (m_alignY)
        m_up = Vec3f(0.0f, 1.0f, 0.0f);
    m_alignY = false;

    if (m_alignZ)
        m_up = Vec3f(0.0f, 0.0f, 1.0f);
    m_alignZ = false;

    // Update stereo mode.

    if (hasFeature(Feature_StereoControls))
    {
        GLContext::Config config = m_window->getGLConfig();
        config.isStereo = (m_enableStereo && GLContext::isStereoAvailable());
        m_window->setGLConfig(config);
    }

    // Repaint continuously.

    if (ev.type == Window::EventType_Paint)
        repaint();
    return false;
}