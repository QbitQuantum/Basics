    /* Third order Runge-Kutta for velocity integration in time */
    void rungeKutta3(double &x, double &y, double timestep, const FluidQuantity &u, const FluidQuantity &v) const {
        double firstU = u.lerp(x, y)/_hx;
        double firstV = v.lerp(x, y)/_hx;

        double midX = x - 0.5*timestep*firstU;
        double midY = y - 0.5*timestep*firstV;

        double midU = u.lerp(midX, midY)/_hx;
        double midV = v.lerp(midX, midY)/_hx;

        double lastX = x - 0.75*timestep*midU;
        double lastY = y - 0.75*timestep*midV;

        double lastU = u.lerp(lastX, lastY);
        double lastV = v.lerp(lastX, lastY);
        
        x -= timestep*((2.0/9.0)*firstU + (3.0/9.0)*midU + (4.0/9.0)*lastU);
        y -= timestep*((2.0/9.0)*firstV + (3.0/9.0)*midV + (4.0/9.0)*lastV);
    }