    void m_rebuild_ui()
    {
        auto head_widget = m_make_ball_spin();
        auto content_widget = m_make_score_container();
        auto done_button = m_context->m_gui.make_button(
            m_context->m_gui.make_label_ex(
                "Done",
                m_context->m_const.menu_font),
            [this]()
            {
                t_transition_required = true;
            });

        auto container = m_context->m_gui.make_container_box(
             dick::GUI::Direction::DOWN,
             20.0);
        container->insert(std::move(head_widget));
        container->insert(std::move(content_widget));
        container->insert(std::move(done_button));

        m_ui = m_context->m_gui.make_container_panel();
        m_ui->insert(std::unique_ptr<dick::GUI::Widget> { container.release() });
        m_ui->align(
            {
                m_context->m_const.screen_w / 2.0,
                m_context->m_const.screen_h / 2.0
            },
            dick::GUI::Alignment::CENTER | dick::GUI::Alignment::MIDDLE);
    }