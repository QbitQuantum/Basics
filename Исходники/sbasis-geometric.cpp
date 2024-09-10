static OptInterval
find_bounds_for_lambda0(double aa0,double aa1,double cc0,double cc1,
    int insist_on_speeds_signs){

    double a0=aa0,a1=aa1,c0=cc0,c1=cc1;
    Interval result;
    bool flip = a1<0;
    if (a1<0){a1=-a1; c1=-c1;}
    if (a0<0){a0=-a0; c0=-c0;}
    double a = (a0<a1 ? a0 : a1);
    double c = (c0<c1 ? c0 : c1);
    double delta = 1-4*a*c;
    if ( delta < 0 )
        return OptInterval();//return empty interval
    double lambda_max = (1+std::sqrt(delta))/2/a;
    
    result = Interval(c,lambda_max);
    if (flip) 
        result *= -1;
    if (insist_on_speeds_signs == 1){
        if (result.max() < 0)//Caution: setMin with max<new min...
            return OptInterval();//return empty interval
        result.setMin(0);
    }
    result = Interval(result.min()-.1,result.max()+.1);//just in case all our approx. were exact...
    return result;
}