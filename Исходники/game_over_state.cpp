 GameoverState(KulkiContext* context) :
     m_context { context }
 {
     m_message = m_context->m_gui.make_dialog_ok(
         "Game over",
         [this](){ t_transition_required = true; });
     m_message->align(
         {
             m_context->m_const.screen_w / 2.0,
             m_context->m_const.screen_h / 2.0
         },
         dick::GUI::Alignment::MIDDLE | dick::GUI::Alignment::CENTER);
 }