void event_device::handle_input_event(const boost::system::error_code& e, size_t /*bytes_read*/)
{
   if (e)
   {
      if (m_stopped && e == boost::asio::error::operation_aborted)
      {
         LINFO(m_log, "stopped");
      }
      else
      {
         LERROR(m_log, "async read failed: " << e.message());
      }

      return;
   }

#ifndef NDEBUG
   if (m_log(log_level::DEBUG))
   {
      debug_input_event();
   }
#endif

   switch (m_iev.type)
   {
      case EV_KEY:
         {
            event_code::type code = event_code::KEYBOARD_ACTIVITY;

            switch (m_iev.code)
            {
               case KEY_LEFTCTRL:
                  setmod(M_CTRL, m_iev.value > 0);
                  break;

               case KEY_LEFTSHIFT:
                  setmod(M_SHIFT, m_iev.value > 0);
                  break;

               case KEY_LEFTALT:
                  setmod(M_ALT, m_iev.value > 0);
                  break;

               case KEY_LEFTMETA:
                  setmod(M_META, m_iev.value > 0);
                  break;

               case KEY_BRIGHTNESSUP:
                  code = m_mod == M_CTRL ? event_code::DISPLAY_BRIGHTNESS_UP_SLOW : event_code::DISPLAY_BRIGHTNESS_UP;
                  break;

               case KEY_BRIGHTNESSDOWN:
                  code = m_mod == M_CTRL ? event_code::DISPLAY_BRIGHTNESS_DOWN_SLOW : event_code::DISPLAY_BRIGHTNESS_DOWN;
                  break;

               case KEY_KBDILLUMUP:
                  code = m_mod == M_CTRL ? event_code::KEYBOARD_BRIGHTNESS_UP_SLOW : event_code::KEYBOARD_BRIGHTNESS_UP;
                  break;

               case KEY_KBDILLUMDOWN:
                  code = m_mod == M_CTRL ? event_code::KEYBOARD_BRIGHTNESS_DOWN_SLOW : event_code::KEYBOARD_BRIGHTNESS_DOWN;
                  break;
            }

            m_handler->handle_event(code);
         }

      case EV_SW:
         switch (m_iev.code)
         {
            case SW_LID:
               m_handler->handle_event(m_iev.value > 0 ? event_code::LID_CLOSED : event_code::LID_OPENED);
               break;
         }

      default:
         break;
   }

   read_next_event();
}