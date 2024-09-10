    //------------------------------------------------------------------------
    void trans_warp_magnifier::inverse_transform(real* x, real* y) const
    {
        // New version by Andrew Skalkin
        //-----------------
        real dx = *x - m_xc;
        real dy = *y - m_yc;
        real r = SQRT(dx * dx + dy * dy);

        if(r < m_radius * m_magn) 
        {
            *x = m_xc + dx / m_magn;
            *y = m_yc + dy / m_magn;
        }
        else
        {
            real rnew = r - m_radius * (m_magn - 1.0f);
            *x = m_xc + rnew * dx / r; 
            *y = m_yc + rnew * dy / r;
        }

        // Old version
        //-----------------
        //trans_warp_magnifier t(*this);
        //t.magnification(1.0f / m_magn);
        //t.radius(m_radius * m_magn);
        //t.transform(x, y);
    }