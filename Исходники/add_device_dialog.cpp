AddDeviceDialog::AddDeviceDialog() : ModalDialog(0.90f, 0.80f)
{
    doInit();

    ScalableFont* font = GUIEngine::getFont();
    const int textHeight = GUIEngine::getFontHeight();
    const int buttonHeight = textHeight + 10;

#ifdef ENABLE_WIIUSE
    const int nbButtons = 3;
#else
    const int nbButtons = 2;
#endif

    const int y_bottom = m_area.getHeight() - nbButtons*(buttonHeight + 10) - 10;
    const int y_stride = buttonHeight+10;
    int cur_y = y_bottom;

    core::rect<s32> text_area( 15, 15, m_area.getWidth()-15, y_bottom-15 );

    core::stringw msg =
        _("To add a new Gamepad/Joystick device, simply start SuperTuxKart "
          "with it connected and it will appear in the list.\n\nTo add a "
          "keyboard config, you can use the button below, HOWEVER please "
          "note that most keyboards only support a limited amount of "
          "simultaneous keypresses and are thus inappropriate for multiplayer "
          "gameplay. (You can, however, connect multiple keyboards to the "
          "computer. Remember that everyone still needs different keybindings "
          "in this case.)");
    IGUIStaticText* b =
        GUIEngine::getGUIEnv()->addStaticText(msg.c_str(),
                                              text_area,
                                              /*border*/false ,
                                              /*word wrap*/true,
                                              m_irrlicht_window);
    b->setTabStop(false);
    b->setRightToLeft(translations->isRTLLanguage());
    // because it looks like 'setRightToLeft' applies next time
    // setText is called only
    b->setText(msg.c_str());

#ifdef ENABLE_WIIUSE
    {
        ButtonWidget* widget = new ButtonWidget();
        widget->m_properties[PROP_ID] = "addwiimote";

        //I18N: In the 'add new input device' dialog
        widget->setText( _("Add Wiimote") );

        const int textWidth =
            font->getDimension( widget->getText().c_str() ).Width + 40;

        widget->m_x = m_area.getWidth()/2 - textWidth/2;
        widget->m_y = cur_y;
        widget->m_w = textWidth;
        widget->m_h = buttonHeight;
        widget->setParent(m_irrlicht_window);
        m_widgets.push_back(widget);
        widget->add();
        cur_y += y_stride;
    }
#endif  // ENABLE_WIIUSE

    {
        ButtonWidget* widget = new ButtonWidget();
        widget->m_properties[PROP_ID] = "addkeyboard";

        //I18N: In the 'add new input device' dialog
        widget->setText( _("Add Keyboard Configuration") );

        const int textWidth =
            font->getDimension( widget->getText().c_str() ).Width + 40;

        widget->m_x = m_area.getWidth()/2 - textWidth/2;
        widget->m_y = cur_y;
        widget->m_w = textWidth;
        widget->m_h = buttonHeight;
        widget->setParent(m_irrlicht_window);
        m_widgets.push_back(widget);
        widget->add();
        cur_y += y_stride;
    }
    {
        ButtonWidget* widget = new ButtonWidget();
        widget->m_properties[PROP_ID] = "cancel";
        widget->setText( _("Cancel") );

        const int textWidth =
            font->getDimension( widget->getText().c_str() ).Width + 40;

        widget->m_x = m_area.getWidth()/2 - textWidth/2;
        widget->m_y = cur_y;
        widget->m_w = textWidth;
        widget->m_h = buttonHeight;
        widget->setParent(m_irrlicht_window);
        m_widgets.push_back(widget);
        widget->add();
        cur_y += y_stride;

        widget->setFocusForPlayer( PLAYER_ID_GAME_MASTER );

    }

}   // AddDeviceDialog