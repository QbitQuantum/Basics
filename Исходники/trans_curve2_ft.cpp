    virtual void on_init()
    {
        m_poly1.xn(0) =  10 + 50;
        m_poly1.yn(0) = -10 + 50;
        m_poly1.xn(1) =  10 + 150 + 20;
        m_poly1.yn(1) = -10 + 150 - 20;
        m_poly1.xn(2) =  10 + 250 - 20;
        m_poly1.yn(2) = -10 + 250 + 20;
        m_poly1.xn(3) =  10 + 350 + 20;
        m_poly1.yn(3) = -10 + 350 - 20;
        m_poly1.xn(4) =  10 + 450 - 20;
        m_poly1.yn(4) = -10 + 450 + 20;
        m_poly1.xn(5) =  10 + 550;
        m_poly1.yn(5) = -10 + 550;

        m_poly2.xn(0) = -10 + 50;
        m_poly2.yn(0) =  10 + 50;
        m_poly2.xn(1) = -10 + 150 + 20;
        m_poly2.yn(1) =  10 + 150 - 20;
        m_poly2.xn(2) = -10 + 250 - 20;
        m_poly2.yn(2) =  10 + 250 + 20;
        m_poly2.xn(3) = -10 + 350 + 20;
        m_poly2.yn(3) =  10 + 350 - 20;
        m_poly2.xn(4) = -10 + 450 - 20;
        m_poly2.yn(4) =  10 + 450 + 20;
        m_poly2.xn(5) = -10 + 550;
        m_poly2.yn(5) =  10 + 550;
    }