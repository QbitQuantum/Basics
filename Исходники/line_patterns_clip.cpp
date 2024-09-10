    the_application(agg::pix_format_e format, bool flip_y) :
        agg::platform_support(format, flip_y),
        m_ctrl_color(agg::rgba(0, 0.3, 0.5, 0.3)),
        m_line1(5),
        m_scale_x(5.0,   5.0, 240.0, 12.0, !flip_y),
        m_start_x(250.0, 5.0, 495.0, 12.0, !flip_y)
    {
        m_line1.line_color(m_ctrl_color);
        m_line1.xn(0) = 20;
        m_line1.yn(0) = 20;
        m_line1.xn(1) = 500-20;
        m_line1.yn(1) = 500-20;
        m_line1.xn(2) = 500-60;
        m_line1.yn(2) = 20;
        m_line1.xn(3) = 40;
        m_line1.yn(3) = 500-40;
        m_line1.xn(4) = 100;
        m_line1.yn(4) = 300;
        m_line1.close(false);

        add_ctrl(m_line1);
        m_line1.transform(m_scale);

        m_scale_x.label("Scale X=%.2f");
        m_scale_x.range(0.2, 3.0);
        m_scale_x.value(1.0);
        add_ctrl(m_scale_x);
        m_scale_x.no_transform();

        m_start_x.label("Start X=%.2f");
        m_start_x.range(0.0, 10.0);
        m_start_x.value(0.0);
        add_ctrl(m_start_x);
        m_start_x.no_transform();
    }