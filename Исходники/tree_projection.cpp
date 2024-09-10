TreeProjection& TreeProjection::operator=( const Operator &arg ){

    if( this != &arg ){

        if( argument != 0 ){
            if( argument->nCount == 0 ){
                delete argument;
                argument = 0;
            }
            else{
                argument->nCount--;
            }
        }

        Operator *tmp = arg.passArgument();

        if( tmp == 0 ) argument = arg.clone() ;
        else           argument = tmp->clone();

        vIndex         = count++;
        variableIndex  = vIndex ;

        curvature      = CT_UNKNOWN; // argument->getCurvature();
        monotonicity   = MT_UNKNOWN; // argument->getMonotonicity();

        ne = argument->isOneOrZero();

        if( curvature == CT_CONSTANT )
            scale = argument->getValue();
    }

    return *this;
}