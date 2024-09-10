bool GuiScrollBar::onEvent(const GEvent& event) {
    if (! m_visible) {
        return false;
    }
    float m = maxValue();
        Rect2D topB;
        Rect2D bottomB; 
        Rect2D barBounds;
        Rect2D thumbBounds;

        getAllBounds(topB, bottomB, barBounds, thumbBounds);
    if (event.type == GEventType::MOUSE_BUTTON_DOWN) {
       
        const Vector2& mouse = Vector2(event.button.x, event.button.y);
      
        if(bottomB.contains(mouse)) {
            *m_value = min<float>( m * m_extent, *m_value + m_extent * BUTTON_PRESS_SCROLL);
            m_state = ARROW_DOWN_SCROLLING;
            GEvent response;

            response.gui.type = GEventType::GUI_CHANGE;
            response.gui.control = m_eventSource;
            m_gui->fireEvent(response);

            fireEvent(GEventType::GUI_ACTION);
            return true;

        } else if (topB.contains(mouse)) {

            *m_value = max<float>( 0.0f, *m_value - m_extent*BUTTON_PRESS_SCROLL);

            m_state = ARROW_UP_SCROLLING;

            GEvent response;
            response.gui.type = GEventType::GUI_CHANGE;
            response.gui.control = m_eventSource;
            m_gui->fireEvent(response);

            fireEvent(GEventType::GUI_ACTION);
            return true;

        } else if (thumbBounds.contains(mouse)) {
            m_state = IN_DRAG;
            m_dragStart = mouse;
            m_dragStartValue = floatValue();
            
            GEvent response;
            response.gui.type = GEventType::GUI_DOWN;
            response.gui.control = m_eventSource;
            m_gui->fireEvent(response);

            response.gui.type = GEventType::GUI_CHANGE;
            response.gui.control = m_eventSource;
            m_gui->fireEvent(response);

            return true;

        } else if (barBounds.contains(mouse)) {
            // Jump to this position
            float p;
            if(m_vertical) {
                p =  ( mouse.y - (float)barBounds.y0() ) / ((float)barBounds.height()/(m + 1)) - .5f;
            } else {
                p = ( mouse.x - (float)barBounds.x0() ) / ((float)barBounds.width()/(m + 1)) - .5f;
            }
            p = max<float>(0, p);
            p = min<float>(p, m);
            setFloatValue(p);

            m_state = NONE;

            GEvent response;
            response.gui.type = GEventType::GUI_CHANGE;
            response.gui.control = m_eventSource;
            m_gui->fireEvent(response);

            fireEvent(GEventType::GUI_ACTION);
            return true;
        }

        return false;

    } else if (event.type == GEventType::MOUSE_BUTTON_UP) {

        m_state = NONE;

        fireEvent(GEventType::GUI_ACTION);
        if (m_state == IN_DRAG) {
            // End the drag

            fireEvent(GEventType::GUI_DOWN);
            fireEvent(GEventType::GUI_ACTION);

            return true;
        }

    } else if (event.type == GEventType::MOUSE_MOTION) {

        // We'll only receive these events if we have the keyFocus, but we can't
        // help receiving the key focus if the user clicked on the control!

        const Vector2& mouse = Vector2(event.button.x, event.button.y);

        if (m_state == IN_DRAG) {    
            float delta;
            if(m_vertical) {
                delta = (mouse.y - m_dragStart.y) / (barBounds.height()/(m + 1));
            } else {
                delta = (mouse.x - m_dragStart.x) / (barBounds.width()/(m + 1));
            }
            float p = m_dragStartValue + delta;
            p = max<float>(0, p);
            p = min<float>(p, m);
            setFloatValue(p);
    
            GEvent response;
            response.gui.type = GEventType::GUI_CHANGE;
            response.gui.control = m_eventSource;
            m_gui->fireEvent(response);

             return true;
        } else if  (m_state == ARROW_UP_SCROLLING || m_state == ARROW_UP) {
            if(topB.contains(mouse)) {
                m_state = ARROW_UP_SCROLLING;
            } else {
                m_state = ARROW_UP;
            }
            return true;
        } else if (m_state == ARROW_DOWN_SCROLLING || m_state == ARROW_DOWN)  {       
            if(bottomB.contains(mouse)) {
                m_state = ARROW_DOWN_SCROLLING;
            } else {
                m_state = ARROW_DOWN;
            }
            return true;
        }
    } 
    return false;
    }