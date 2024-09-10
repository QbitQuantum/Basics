shared_vec osc_operation( shared_vec q , shared_vec q_l , shared_vec q_r , shared_vec dpdt )
{
    using std::pow;
    using std::abs;
    using boost::math::sign;

    const size_t M = q->size();

    double coupling = pow( abs((*q_l)[q_l->size()-1]-(*q)[0]) , LAMBDA-1 ) * sign((*q_l)[q_l->size()-1]-(*q)[0]);

    // (*dpdt)[0] = -pow( abs((*q)[0]) , KAPPA-1 ) * sign( (*q)[0] )
    //     - pow( abs((*q)[0]-(*q)[1]) , LAMBDA-1 ) * sign( (*q)[0]-(*q)[1] )
    //     - pow( abs((*q)[0]-(*q_l)[q_l->size()-1]) , LAMBDA-1 ) * sign((*q)[0]-(*q_l)[q_l->size()-1]);

    for( size_t i=0 ; i<M-1 ; ++i )
    {
        (*dpdt)[i] = -pow( abs((*q)[i]) , KAPPA-1 ) * sign((*q)[i])
            + coupling;
        coupling = pow( abs((*q)[i]-(*q)[i+1]) , LAMBDA-1 ) * sign((*q)[i]-(*q)[i+1]);
        (*dpdt)[i] -= coupling;
    }

    (*dpdt)[M-1] = -pow( abs((*q)[M-1]) , KAPPA-1 ) * sign((*q)[M-1]) 
        - pow( abs((*q)[M-1] - (*q_r)[0]) , LAMBDA-1 ) * sign((*q)[M-1]-(*q_r)[0])
        + coupling;

    return dpdt;
}