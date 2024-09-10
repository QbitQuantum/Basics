double BlockConstraint::_basicCostGrad(Eigen::Vector2d& grad_c, const Vector2d &config)
{
    Eigen::Vector2d p = _tfinv*(config-_center);
//    std::cout << p.transpose() << "\t|\t" << scales[0] << ", " << scales[1] << std::endl;
    
    assert( buffer > 0 && "We only support positive-valued buffer sizes!");
    
    double c = INFINITY;
    for(size_t i=0; i<2; ++i)
    {
        if(fabs(p[i]) >= fabs(scales[i])+fabs(buffer))
        {
            grad_c.setZero();
            return 0;
        }
        else if(fabs(p[i]) >= fabs(scales[i]))
        {
            double dist = buffer-(fabs(p[i])-fabs(scales[i]));
            double ctemp = dist*dist/(2*buffer);
            if(ctemp < c)
            {
                c = ctemp;
                grad_c.setZero();
                grad_c[i] = -(fabs(p[i])-fabs(scales[i])-buffer)/buffer*sign(p[i]);
            }
        }
        else
        {
            double ctemp = scales[i]-p[i] + buffer/2;
            if(ctemp < c)
            {
                c = ctemp;
                grad_c.setZero();
                grad_c[i] = -sign(p[i]);
            }
        }
    }
    
    return c;
}