    virtual void on_init()
    {
        m_quad1.xn(0) = 50;
        m_quad1.yn(0) = 200 - 20;
        m_quad1.xn(1) = width() / 2 - 25;
        m_quad1.yn(1) = 200;
        m_quad1.xn(2) = width() / 2 - 25;
        m_quad1.yn(2) = height() - 50 - 20;
        m_quad1.xn(3) = 50;
        m_quad1.yn(3) = height() - 50;

        m_quad2.xn(0) = width() / 2 + 25;
        m_quad2.yn(0) = 200 - 20;
        m_quad2.xn(1) = width() - 50;
        m_quad2.yn(1) = 200;
        m_quad2.xn(2) = width() - 50;
        m_quad2.yn(2) = height() - 50 - 20;
        m_quad2.xn(3) = width() / 2 + 25;
        m_quad2.yn(3) = height() - 50;
    }