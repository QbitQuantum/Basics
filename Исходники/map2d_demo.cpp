    virtual double getCost(const MatX& q, size_t body_index,
                           MatX& dx_dq, MatX& cgrad ) 
    {
        assert( (q.rows() == 2 && q.cols() == 1) ||
                (q.rows() == 1 && q.cols() == 2) );

        dx_dq.resize(3, 2);
        dx_dq.setZero();

        dx_dq << 1, 0, 0, 1, 0, 0;

        cgrad.resize(3, 1);

        vec3f g;
        
        float c = map->sampleCost(vec3f(q(0), q(1), 0.0), g);

        cgrad << g[0], g[1], 0.0;

        return c;
    }