void HeadsUpDisplay::tick(Ogre::Real timeDelta)
{
    // window dimensions may have changed
    Application &app = Application::getSingleton();
    Ogre::Real windowWidth = (Ogre::Real)app.getWindowWidth();
    Ogre::Real windowHeight = (Ogre::Real)app.getWindowHeight();

    // get mouse cursor and update absolute position from relative change
    OIS::Mouse *mouse = app.getMouse();
    if (mouse != nullptr)
    {
        OIS::MouseState mouseState = mouse->getMouseState();
        m_cursorX += mouseState.X.rel;
        m_cursorY += mouseState.Y.rel;
        m_cursorX = Math::clamp(m_cursorX, 0, windowWidth);
        m_cursorY = Math::clamp(m_cursorY, 0, windowHeight);

        // normalize cursor position and size from 0 to 1
        Ogre::Real cursorX = m_cursorX / windowWidth;
        Ogre::Real cursorY = m_cursorY / windowHeight;
        m_cursorContainer->setPosition(cursorX, cursorY);
        m_cursorContainer->setWidth(CURSOR_WIDTH / windowWidth);
        m_cursorContainer->setHeight(CURSOR_HEIGHT / windowHeight);
        m_cursorContainer->show();

        // project cursor ray into scene and get query results
        if (!m_mouseLeftLastDown && mouseState.buttonDown(OIS::MouseButtonID::MB_Left))
        {
            Ogre::Ray mouseRay;
            getCamera()->getCameraToViewportRay(cursorX, cursorY, &mouseRay);
            m_rayQuery->setRay(mouseRay);
            m_objectFound = false;
            m_rayQuery->execute(this);

            if (!m_objectFound && (m_currentSelection != nullptr))
            {
                // user selected nothing so clear current selection
                m_currentSelection->onDeselect();
            }
        }

        if ((m_currentSelection != nullptr) && !m_mouseRightLastDown && mouseState.buttonDown(OIS::MouseButtonID::MB_Right))
        {
            Ogre::Ray mouseRay;
            getCamera()->getCameraToViewportRay(cursorX, cursorY, &mouseRay);
            Ogre::Plane plane(Ogre::Vector3(0, 1, 0), Ogre::Vector3::ZERO);
            auto intersectResult = mouseRay.intersects(plane);
            if (intersectResult.first)
            {
                Ogre::Vector3 destination = mouseRay.getPoint(intersectResult.second);
                m_currentSelection->onMoveOrder(destination);
            }
        }
        
        m_mouseLeftLastDown = mouseState.buttonDown(OIS::MouseButtonID::MB_Left);
        m_mouseRightLastDown = mouseState.buttonDown(OIS::MouseButtonID::MB_Right);
    }
    else
    {
        m_cursorContainer->hide();
    }
}