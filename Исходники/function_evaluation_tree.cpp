returnValue FunctionEvaluationTree::makeImplicit( int dim_ ){

    int run1;
    int var_counter = indexList->makeImplicit(dim_);

    for( run1 = 0; run1 < dim_; run1++ ){

        Operator *tmp = f[run1]->clone();
        delete f[run1];
        Projection pp;
        pp.variableType   = VT_DDIFFERENTIAL_STATE;
        pp.vIndex         = run1                  ;
        pp.variableIndex  = var_counter-dim_+run1  ;

        f[run1] = new Subtraction( pp.clone(), tmp->clone() );
        delete tmp;
    }

    return SUCCESSFUL_RETURN;
}