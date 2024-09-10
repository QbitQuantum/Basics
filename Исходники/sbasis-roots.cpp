static void multi_roots_internal(SBasis const &f,
				 SBasis const &df,
				 std::vector<double> const &levels,
				 std::vector<std::vector<double> > &roots,
				 double htol,
				 double vtol,
				 double a,
				 double fa,
				 double b,
				 double fb){
    
    if (f.size()==0){
        int idx;
        idx=upper_level(levels,0,vtol);
        if (idx<(int)levels.size()&&fabs(levels.at(idx))<=vtol){
            roots[idx].push_back(a);
            roots[idx].push_back(b);
        }
        return;
    }
////usefull? 
//     if (f.size()==1){
//         int idxa=upper_level(levels,fa);
//         int idxb=upper_level(levels,fb);
//         if (fa==fb){
//             if (fa==levels[idxa]){
//                 roots[a]=idxa;
//                 roots[b]=idxa;
//             }
//             return;
//         }
//         int idx_min=std::min(idxa,idxb);
//         int idx_max=std::max(idxa,idxb);
//         if (idx_max==levels.size()) idx_max-=1;
//         for(int i=idx_min;i<=idx_max; i++){
//             double t=a+(b-a)*(levels[i]-fa)/(fb-fa);
//             if(a<t&&t<b) roots[t]=i;
//         }
//         return;
//     }
    if ((b-a)<htol){
        //TODO: use different tol for t and f ?
        //TODO: unsigned idx ? (remove int casts when fixed)
        int idx=std::min(upper_level(levels,fa,vtol),upper_level(levels,fb,vtol));
        if (idx==(int)levels.size()) idx-=1;
        double c=levels.at(idx);
        if((fa-c)*(fb-c)<=0||fabs(fa-c)<vtol||fabs(fb-c)<vtol){
            roots[idx].push_back((a+b)/2);
        }
        return;
    }
    
    int idxa=upper_level(levels,fa,vtol);
    int idxb=upper_level(levels,fb,vtol);

    Interval bs = bounds_local(df,Interval(a,b));

    //first times when a level (higher or lower) can be reached from a or b.
    double ta_hi,tb_hi,ta_lo,tb_lo;
    ta_hi=ta_lo=b+1;//default values => no root there.
    tb_hi=tb_lo=a-1;//default values => no root there.

    if (idxa<(int)levels.size() && fabs(fa-levels.at(idxa))<vtol){//a can be considered a root.
        //ta_hi=ta_lo=a;
        roots[idxa].push_back(a);
        ta_hi=ta_lo=a+htol;
    }else{
        if (bs.max()>0 && idxa<(int)levels.size())
            ta_hi=a+(levels.at(idxa  )-fa)/bs.max();
        if (bs.min()<0 && idxa>0)
            ta_lo=a+(levels.at(idxa-1)-fa)/bs.min();
    }
    if (idxb<(int)levels.size() && fabs(fb-levels.at(idxb))<vtol){//b can be considered a root.
        //tb_hi=tb_lo=b;
        roots[idxb].push_back(b);
        tb_hi=tb_lo=b-htol;
    }else{
        if (bs.min()<0 && idxb<(int)levels.size())
            tb_hi=b+(levels.at(idxb  )-fb)/bs.min();
        if (bs.max()>0 && idxb>0)
            tb_lo=b+(levels.at(idxb-1)-fb)/bs.max();
    }
    
    double t0,t1;
    t0=std::min(ta_hi,ta_lo);    
    t1=std::max(tb_hi,tb_lo);
    //hum, rounding errors frighten me! so I add this +tol...
    if (t0>t1+htol) return;//no root here.

    if (fabs(t1-t0)<htol){
        multi_roots_internal(f,df,levels,roots,htol,vtol,t0,f(t0),t1,f(t1));
    }else{
        double t,t_left,t_right,ft,ft_left,ft_right;
        t_left =t_right =t =(t0+t1)/2;
        ft_left=ft_right=ft=f(t);
        int idx=upper_level(levels,ft,vtol);
        if (idx<(int)levels.size() && fabs(ft-levels.at(idx))<vtol){//t can be considered a root.
            roots[idx].push_back(t);
            //we do not want to count it twice (from the left and from the right)
            t_left =t-htol/2;
            t_right=t+htol/2;
            ft_left =f(t_left);
            ft_right=f(t_right);
        }
        multi_roots_internal(f,df,levels,roots,htol,vtol,t0     ,f(t0)   ,t_left,ft_left);
        multi_roots_internal(f,df,levels,roots,htol,vtol,t_right,ft_right,t1    ,f(t1)  );
    }
}