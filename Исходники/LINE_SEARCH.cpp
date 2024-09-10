//#####################################################################
// Function Line_Search_Quadratic_Golden_Section
//#####################################################################
template<class T> bool LINE_SEARCH<T>::
Line_Search_Golden_Section(NONLINEAR_FUNCTION<T(T)>& F,T a,T b,T& x,int max_iterations,T interval_tolerance) const
{
    PHYSBAM_ASSERT(a<=b);
    T tau=(T).5*(sqrt((T)5)-1),m=a+tau*(b-a),t;
    BRACKET s={a,m,b,F(a),F(m),F(b)};
    int i;
    interval_tolerance*=abs(s.a)+abs(s.b);
    for(i=1;i<=max_iterations;i++){
        if(abs(s.b-s.a)<interval_tolerance) break;
        t=s.a+s.b-s.m;
        Update_Interval(s,t,F(t));}
    x=Best_Value(s);
    return i<=max_iterations;
}