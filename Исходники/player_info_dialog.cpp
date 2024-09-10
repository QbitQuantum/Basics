/** Changes this dialog to confirm the changes.
 */
void PlayerInfoDialog::showConfirmDialog()
{
    clearWindow();

    IGUIFont* font = GUIEngine::getFont();
    const int textHeight = GUIEngine::getFontHeight();
    const int buttonHeight = textHeight + 10;

    irr::core::stringw message =
        //I18N: In the player info dialog (when deleting)
        _("Do you really want to delete player '%s' ?", m_player->getName());


    if (PlayerManager::getCurrentPlayer() == m_player)
    {
        message = _("You cannot delete this player "
                    "because it is currently in use.");
    }

    core::rect< s32 > area_left(5, 0, m_area.getWidth()-5, m_area.getHeight()/2);

    // When there is no need to tab through / click on images/labels,
    // we can add irrlicht labels directly
    // (more complicated uses require the use of our widget set)
    IGUIStaticText* a = GUIEngine::getGUIEnv()->addStaticText( message.c_str(),
                                              area_left, false /* border */,
                                              true /* word wrap */,
                                              m_irrlicht_window);
    a->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);

    if (PlayerManager::getCurrentPlayer() != m_player)
    {
        ButtonWidget* widget = new ButtonWidget();
        widget->m_properties[PROP_ID] = "confirmremove";

        //I18N: In the player info dialog (when deleting)
        widget->setText( _("Confirm Remove") );

        const int textWidth =
            font->getDimension(widget->getText().c_str()).Width + 40;

        widget->m_x = m_area.getWidth()/2 - textWidth/2;
        widget->m_y = m_area.getHeight()/2;
        widget->m_w = textWidth;
        widget->m_h = buttonHeight;
        widget->setParent(m_irrlicht_window);
        m_widgets.push_back(widget);
        widget->add();
    }

    {
        ButtonWidget* widget = new ButtonWidget();
        widget->m_properties[PROP_ID] = "cancelremove";

        //I18N: In the player info dialog (when deleting)
        widget->setText( _("Cancel Remove") );

        const int textWidth =
            font->getDimension( widget->getText().c_str() ).Width + 40;

        widget->m_x = m_area.getWidth()/2 - textWidth/2;
        widget->m_y = m_area.getHeight()*3/4;
        widget->m_w = textWidth;
        widget->m_h = buttonHeight;
        widget->setParent(m_irrlicht_window);
        m_widgets.push_back(widget);
        widget->add();

        widget->setFocusForPlayer( PLAYER_ID_GAME_MASTER );
    }

}   // showConfirmDialog