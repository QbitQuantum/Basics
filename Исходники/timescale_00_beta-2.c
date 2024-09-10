double g_psr_disk (double *k, size_t dim, void *params)
{   
    double rdd,zdd,r0,p0,beta,ita,h1,h2,H;
    double rd,zd;
    double xs,ys,xl,yl;
    double p_disk,p_pulsar;
    double A,a,B,E;
    double r1;
    double b,l;
    double Deff;
    double F;
    //double v,vl,vb,vrot,vrot_disk,sigma_y,sigma_z,mean_vl,mean_vb,sigma_vl,sigma_vb,vlfunc,vbfunc;
    double M;
    double alpha;
    double v,vl,vb,vol,vob,vdl,vdb,vsl,vsb,vdx,vdy,vdz,vsx,vsy,vsz,sigma_vdx,sigma_vdy,sigma_vdz,sigma_vsx,sigma_vsy,sigma_vsz,vdxfunc,vdyfunc,vdzfunc,vsxfunc,vsyfunc,vszfunc,vrot,vrot_disk;
    double d,R;
    double re,delta_func;

    r0=8.0; // kpc

    //l=k[8];
    //b=k[9];
    //b=-2.75*3.1415926/180.0;
    //l=1.16*3.1415926/180.0;
    b=0.000001;
    l=0.000001;
    //b=5.0*3.1415926/180.0;
    //l=5.0*3.1415926/180.0;

    if ( k[0] <= k[1] )
    {
        F=0.0;
    }
    else
    {
    d=k[1]*sin(b);
    R=sqrt(r0*r0+d*d-2.0*r0*d*cos(l));
    if ((d*d+R*R-r0*r0)/(2.0*d*R)>1.0)         alpha=acos(1);
    else if ((d*d+R*R-r0*r0)/(2.0*d*R)<-1.0)    alpha=acos(-1);
    else alpha=acos((d*d+R*R-r0*r0)/(2.0*d*R));
    if(sin(l)<0) alpha=-1*alpha;
    //alpha=acos( (d*d+R*R-r0*r0)/(2.0*d*R)>0.0 ? (d*d+R*R-r0*r0)/(2.0*d*R)-1e-8 : (d*d+R*R-r0*r0)/(2.0*d*R)+1e-8);
    //alpha=asin(r0*sin(l)/R);
    //alpha=2.0*3.1415926-asin(r0*sin(l)/R);

    M=1.4;

    // source distribution: disk
    rdd=sqrt(k[0]*k[0]*cos(b)*cos(b)-2.0*k[0]*r0*cos(b)*cos(l)+r0*r0);
    zdd=k[0]*sin(b);
    xs=-k[0]*cos(b)*cos(l)+r0;
    ys=k[0]*cos(b)*sin(l);

    //p0=0.0493*pow(10,9); // M*kpc^(-3)
    p0=1.388789*0.0493*pow(10.0,9.0); // kpc^(-3)
    //p0=1.3888*0.0493*pow(10.0,9.0); // kpc^(-3)
    //p0=0.0493*pow(10.0,9.0)/3.1; // kpc^(-3)
    beta=0.565;
    h1=0.270; // kpc
    h2=0.440; // kpc
    H=2.75; // kpc

    if (((rdd/9.025)+0.114)<=0.670)
    {
        ita=0.670;
    }
    else
    {
        ita=(rdd/9.025)+0.114;
    }

    //p_disk=(p0/ita)*exp(-(rdd-r0)/H)*((1.0-beta)*pow(cosh(zdd/(ita*h1)),-2.0)+beta*exp(-fabs(zdd)/(ita*h2)));  // :disk
    if (k[0]<5.0)
    {
        p_disk=(p0/ita)*exp(-(rdd-r0)/H)*((1.0-beta)*pow(cosh(zdd/(ita*h1)),-2.0)+beta*exp(-fabs(zdd)/(ita*h2)));  // :disk
    }
    else
    {
        p_disk=(1.0/pow(k[0],4.0))*(p0/ita)*exp(-(rdd-r0)/H)*((1.0-beta)*pow(cosh(zdd/(ita*h1)),-2.0)+beta*exp(-fabs(zdd)/(ita*h2)));  // :disk
    }

    // lens distribution: psr

    //A=41.0*1.6*pow(10.0,6.0); // kpc^(-2)
    //A=41.0*8.61*pow(10.0,6.0); // kpc^(-2)  by Lorimer 2006
    //A=2000.0*4.5*pow(10.0,5.0); // kpc^(-2)    by Kaspi 2006
    A=2000.0*10000/1.18; // kpc^(-2)    by Kaspi 2006
    //A=1.37*2000.0; // kpc^(-2)    by Kaspi 2006
    //A=2000.0*10000/5.15; // kpc^(-2)    by Kaspi 2006
    r1=0.55;  // kpc
    a=1.64;
    //B=9.01;
    B=4.01;
    E=0.05; // kpc

    rd=sqrt(k[1]*k[1]*cos(b)*cos(b)-2.0*k[1]*r0*cos(b)*cos(l)+r0*r0);
    zd=k[1]*sin(b);
    xl=-k[1]*cos(b)*cos(l)+r0;
    yl=k[1]*cos(b)*sin(l);

    p_pulsar=A*pow((rd+r1)/(r0+r1),a)*exp(-B*((rd-r0)/(r0+r1)))*exp(-fabs(zd)/E);  // pulsar density

    Deff=sqrt(k[1]*fabs(k[0]-k[1])/k[0]);

    // disk rotational velocity function
    vrot=220.0;

    // disk rotational velocity function
    //if ((xl*xl+yl*yl)<4.0)
    //{
    //    vrot_disk=220.0*xl; // 100km/s,x/kpc
    //}
    //else
    //{
          vrot_disk=220.0;
    //}

    // observor velocity
    vol=-220.0*cos(l);
    vob=220.0*sin(l)*sin(b);

    // deflector: disk velocity
    // vdx,vdy,vdz,sigma_dx=20.0,sigma_dy=30.0,sigma_dz=20
    vdx=k[2];
    vdy=k[3];
    vdz=k[4];
    vdl=vrot_disk*cos(alpha)+vdx*sin(l)-vdy*cos(l);
    vdb=-vrot_disk*sin(alpha)*sin(b)+vdx*cos(l)*sin(b)+vdy*sin(l)*sin(b)+vdz*cos(b);
    sigma_vdx=290.0;
    sigma_vdy=290.0;
    sigma_vdz=290.0;

    // source: disk velocity
    // vsx,vsy,vsz,sigma_sx=110.0,sigma_sy=82.5,sigma_sz=66.3
    vsx=k[5];
    vsy=k[6];
    vsz=k[7];
    vsl=vrot*cos(alpha)+vsx*sin(l)-vsy*cos(l);
    vsb=-vrot*sin(alpha)*sin(b)+vsx*cos(l)*sin(b)+vsy*sin(l)*sin(b)+vsz*cos(b);
    sigma_vsx=20.0;
    sigma_vsy=30.0;
    sigma_vsz=20.0;

    vl=vdl-vol+(vol-vsl)*(k[1]/k[0]);
    vb=vdb-vob+(vob-vsb)*(k[1]/k[0]);
    v=sqrt(vl*vl+vb*vb);

    //sigma_y=290.0;
    //sigma_z=290.0;
    //sigma_y=-5.625*pow(xl*xl+yl*yl,0.5)+75.0;
    //sigma_z=-3.75*pow(xl*xl+yl*yl,0.5)+50.0;
    // lens-source relative transverse velocity
    //vlb=(k[5]*cos(l)-k[4]*sin(l))/cos(b);
    //vlb=k[5]*cos(l)-k[4]*sin(l);
    //vbb=k[6]*cos(b)-tan(b)*(k[4]*cos(b)*cos(l)+k[5]*cos(b)*sin(l));
    //vlb=-k[4];
    ///////////////////////////////////////////////////////////////////
    //vld=k[3];
    //vbd=k[6];
    //vlb=k[4];
    //vbb=k[5];
    //vl=(vld+vrot_disk-220.0)+(220.0-vrot-vlb)*(k[1]/k[0]);
    //vl=k[3]+(220.0-vrot-vlb)*(k[1]/k[0]);
    //vb=vbd-vbb*(k[1]/k[0]);
    //v=pow(vl*vl+vb*vb,0.5);
    ////////////////////////////////////////////////////////////////////
    //vl=k[2];
    //vb=k[3];
    //mean_vl=(vrot_disk-220.0)+(220.0-vrot)*(k[1]/k[0]);
    //mean_vl=(220.0-vrot)*(k[1]/k[0]);
    //mean_vb=0.0;
    //sigma_vl=pow(sigma_y*sigma_y+82.5*82.5*k[1]*k[1]/(k[0]*k[0]),0.5);
    //sigma_vb=pow(sigma_z*sigma_z+66.3*66.3*k[1]*k[1]/(k[0]*k[0]),0.5);
    //v=pow(vl*vl+vb*vb,0.5);

    //if ((184.2*365.0*365.0*Deff*Deff*M/(t*t)-vl*vl)<=0)
    //{
    //    ifunc_vbd=0.0;
    //}
    //else
    //{
    //    ifunc_vbd=1.0;
    //}

    // vbd as a function of vlb,vx,vy,vz,M
    //vbd=pow(fabs(184.2*365.0*365.0*Deff*Deff*M/(t*t)-vl*vl),0.5)+vbb*(k[1]/k[0]);
    /////////////////////////////////////////////////////////////////////////////////////
    // vb as a function of vl
    //vb=pow(fabs(184.2*365.0*365.0*Deff*Deff*M/(t*t)-vl*vl),0.5);

    // f(vld),f(vbd),f(vx),f(vy),f(vx)
    //vldfunc=(1.0/(pow(2.0*3.1415926,0.5)*30.0))*exp(-0.5*vld*vld/900.0);
    //vyfunc=(1.0/(pow(2.0*3.1415926,0.5)*82.5))*exp(-0.5*vlb*vlb/(82.5*82.5));
    //vzfunc=(1.0/(pow(2.0*3.1415926,0.5)*66.3))*exp(-0.5*vbb*vbb/(66.3*66.3));
    //vbdfunc=(1.0/(pow(2.0*3.1415926,0.5)*20.0))*exp(-0.5*vbd*vbd/400.0);
    //vbdfunc=(1.0/(pow(2.0*3.1415926,0.5)*20.0))*exp(-0.5*vbd*vbd/400.0);
    ////////////////////////////////////////////////////////////////////////////////////////
    //vlfunc=(1.0/(pow(2.0*3.1415926,0.5)*sigma_vl))*exp(-0.5*(vl-mean_vl)*(vl-mean_vl)/(sigma_vl*sigma_vl));
    //vbfunc=(1.0/(pow(2.0*3.1415926,0.5)*sigma_vb))*exp(-0.5*(vb-mean_vb)*(vb-mean_vb)/(sigma_vb*sigma_vb));


    vdxfunc=(1.0/(sqrt(2.0*3.1415926)*sigma_vdx))*exp(-0.5*(vdx*vdx)/(sigma_vdx*sigma_vdx));
    vdyfunc=(1.0/(sqrt(2.0*3.1415926)*sigma_vdy))*exp(-0.5*(vdy*vdy)/(sigma_vdy*sigma_vdy));
    vdzfunc=(1.0/(sqrt(2.0*3.1415926)*sigma_vdz))*exp(-0.5*(vdz*vdz)/(sigma_vdz*sigma_vdz));
    vsxfunc=(1.0/(sqrt(2.0*3.1415926)*sigma_vsx))*exp(-0.5*(vsx*vsx)/(sigma_vsx*sigma_vsx));
    vsyfunc=(1.0/(sqrt(2.0*3.1415926)*sigma_vsy))*exp(-0.5*(vsy*vsy)/(sigma_vsy*sigma_vsy));
    vszfunc=(1.0/(sqrt(2.0*3.1415926)*sigma_vsz))*exp(-0.5*(vsz*vsz)/(sigma_vsz*sigma_vsz));

    re=4.28*pow(10.0,8.0)*Deff*sqrt(M);   // km
    //ve=365.0*13.57*Deff*pow(M,0.5);

    //vfunc=pow(59.6*Deff*Deff*k[2]/(t*t)-k[3]*k[3],0.5)*exp(0.5*0.002377*k[3]*k[3]);
    // delta_func
    delta_func=(1.0/(sqrt(2.0*3.1415926)*0.01))*exp(-0.5*(log10((re/v)/(24.0*60.0*60.0))-t)*(log10((re/v)/(24.0*60.0*60.0))-t)/(0.01*0.01));

        F=2.77*pow(10.0,-8.0)*k[0]*k[0]*cos(b)*p_disk*p_pulsar*(Deff)*(sqrt(M))*(v*vdxfunc*vdyfunc*vdzfunc*vsxfunc*vsyfunc*vszfunc)*1.02*pow(10.0,-9.0)*delta_func;
        //F=2.77*pow(10.0,-8.0)*k[0]*k[0]*cos(b)*pnum*exp(-rds)*p_pulsar*(Deff)*(pow(M,0.5))*(v*vlfunc*vbfunc)*1.02*pow(10.0,-9.0);
        //F=2.77*pow(10.0,-8.0)*k[0]*k[0]*cos(b)*pnum*exp(-rds)*p_disk*(Deff)*(pow(M,0.5)*mfunc)*(v*vldfunc*vbdfunc*vyfunc*vzfunc)*1.02*pow(10.0,-9.0)*delta_func/4.3656;
        //F=2.3*2.77*pow(10.0,-8.0)*k[0]*k[0]*cos(b)*pnum*exp(-rds)*p_disk*(Deff)*(pow(M,-0.5)*mfunc)*(v*vldfunc*vbdfunc*vyfunc*vzfunc)*1.02*pow(10.0,-9.0)/(0.1*4.3656);
        //F=2.3*2.77*pow(10.0,-8.0)*k[0]*k[0]*cos(b)*pnum*exp(-rds)*p_disk*(Deff)*(pow(M,0.5)*mfunc)*(v*vldfunc*vbdfunc*vyfunc*vzfunc)*1.02*pow(10.0,-9.0)/(0.1*4.3656);
        //F=2.3*pow(fabs(ve*ve-vl*vl),-0.5)*ve*ve*3.8375*pow(10,-16)*k[0]*k[0]*cos(b)*pnum*exp(-0.5*rds*rds)*p_disk*(Deff*Deff*365.0/t)*(M*mfunc)*(vbfunc*vlfunc);
        //F=2.3*pow(fabs(ve*ve-vl*vl),-0.5)*ve*ve*3.8375*pow(10,-14)*k[0]*k[0]*cos(b)*pnum*exp(-0.5*rds*rds)*p_disk*(Deff*Deff*365.0/t)*(mfunc)*M*(vbfunc*vlfunc)*ifunc*ifunc_vb;
        //F=pow(fabs(ve*ve-vl*vl),-0.5)*ve*ve*3.8375*pow(10,-16)*k[0]*k[0]*cos(b)*pnum*exp(-0.5*rds*rds)*p_disk*(Deff*Deff*365.0/t)*(M*mfunc)*(vbdfunc*vldfunc*vyfunc*vzfunc);
    }

    return F;
}