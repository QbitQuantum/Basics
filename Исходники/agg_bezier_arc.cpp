    //------------------------------------------------------------------------
    void bezier_arc::init(real x,  real y, 
                          real rx, real ry, 
                          real start_angle, 
                          real sweep_angle)
    {
        start_angle = FMOD(start_angle, 2.0f * pi);
        if(sweep_angle >=  2.0f * pi) sweep_angle =  2.0f * pi;
        if(sweep_angle <= -2.0f * pi) sweep_angle = -2.0f * pi;

        if(FABS(sweep_angle) < 1e-10)
        {
            m_num_vertices = 4;
            m_cmd = path_cmd_line_to;
            m_vertices[0] = x + rx * (real)cos(start_angle);
            m_vertices[1] = y + ry * (real)sin(start_angle);
            m_vertices[2] = x + rx * (real)cos(start_angle + sweep_angle);
            m_vertices[3] = y + ry * (real)sin(start_angle + sweep_angle);
            return;
        }

        real total_sweep = 0.0f;
        real local_sweep = 0.0f;
        real prev_sweep;
        m_num_vertices = 2;
        m_cmd = path_cmd_curve4;
        bool done = false;
        do
        {
            if(sweep_angle < 0.0f)
            {
                prev_sweep  = total_sweep;
                local_sweep = -pi * 0.5f;
                total_sweep -= pi * 0.5f;
                if(total_sweep <= sweep_angle + bezier_arc_angle_epsilon)
                {
                    local_sweep = sweep_angle - prev_sweep;
                    done = true;
                }
            }
            else
            {
                prev_sweep  = total_sweep;
                local_sweep =  pi * 0.5f;
                total_sweep += pi * 0.5f;
                if(total_sweep >= sweep_angle - bezier_arc_angle_epsilon)
                {
                    local_sweep = sweep_angle - prev_sweep;
                    done = true;
                }
            }

            arc_to_bezier(x, y, rx, ry, 
                          start_angle, 
                          local_sweep, 
                          m_vertices + m_num_vertices - 2);

            m_num_vertices += 6;
            start_angle += local_sweep;
        }
        while(!done && m_num_vertices < 26);
    }