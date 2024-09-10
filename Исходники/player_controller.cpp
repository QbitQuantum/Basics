/** Handles steering for a player kart.
 */
void PlayerController::steer(float dt, int steer_val)
{
    if(UserConfigParams::m_gamepad_debug)
    {
        Log::debug("PlayerController", "steering: steer_val %d ", steer_val);
        RaceGUIBase* gui_base = World::getWorld()->getRaceGUI();
        gui_base->clearAllMessages();
        gui_base->addMessage(StringUtils::insertValues(L"steer_val %i", steer_val), m_kart, 1.0f,
                             video::SColor(255, 255, 0, 255), false);
    }

    if(stk_config->m_disable_steer_while_unskid &&
        m_controls->m_skid==KartControl::SC_NONE &&
       m_kart->getSkidding()->getVisualSkidRotation()!=0)
    {
        m_controls->m_steer = 0;
    }


    // Amount the steering is changed for digital devices.
    // If the steering is 'back to straight', a different steering
    // change speed is used.
    const float STEER_CHANGE = ( (steer_val<=0 && m_controls->m_steer<0) ||
                                 (steer_val>=0 && m_controls->m_steer>0)   )
                     ? dt/m_kart->getKartProperties()->getTimeResetSteer()
                     : dt/m_kart->getTimeFullSteer(fabsf(m_controls->m_steer));
    if (steer_val < 0)
    {
        // If we got analog values do not cumulate.
        if (steer_val > -32767)
            m_controls->m_steer = -steer_val/32767.0f;
        else
            m_controls->m_steer += STEER_CHANGE;
    }
    else if(steer_val > 0)
    {
        // If we got analog values do not cumulate.
        if (steer_val < 32767)
            m_controls->m_steer = -steer_val/32767.0f;
        else
            m_controls->m_steer -= STEER_CHANGE;
    }
    else
    {   // no key is pressed
        if(m_controls->m_steer>0.0f)
        {
            m_controls->m_steer -= STEER_CHANGE;
            if(m_controls->m_steer<0.0f) m_controls->m_steer=0.0f;
        }
        else
        {   // m_controls->m_steer<=0.0f;
            m_controls->m_steer += STEER_CHANGE;
            if(m_controls->m_steer>0.0f) m_controls->m_steer=0.0f;
        }   // if m_controls->m_steer<=0.0f
    }   // no key is pressed
    if(UserConfigParams::m_gamepad_debug)
    {
        Log::debug("PlayerController", "  set to: %f\n", m_controls->m_steer);
    }

    m_controls->m_steer = std::min(1.0f, std::max(-1.0f, m_controls->m_steer));

}   // steer