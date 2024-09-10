void PGCicrcleTaskPt::Optimize(const ProjPt& prev, const ProjPt& next, double Alt) {
    if(m_Radius == 0.0){
        return;
    }
    
    if (!m_Optimized) {
        // first run : init m_Optimized with center ...
        m_Optimized = m_Center;
    }

    if (!CrossPoint(prev, next ? next : m_Center, m_Optimized)) {
        OptimizedDistance Fmin(prev, m_Center, next, m_Radius);
        double x0 = 0;
        double d1 = min_newuoa<double, OptimizedDistance > (1, &x0, Fmin, PI, 0.01 / m_Radius);
        if (m_bExit) {
            double x1 = x0 + PI;
            double d2 = min_newuoa<double, OptimizedDistance > (1, &x1, Fmin, PI, 0.01 / m_Radius);

            x0 = (std::min(d1, d2) == d1) ? x0 : x1;
        }
        m_Optimized = ProjPt(m_Center.m_X + m_Radius * cos(x0), m_Center.m_Y + m_Radius * sin(x0));
    }
}