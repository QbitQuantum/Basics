bool CalibModule::createTargets(const Vector &c, const Vector &size)
{
    if ((c.length()<3) || (size.length()<2))
        return false;
    
    double a=std::max(fabs(size[0]),0.04);
    double b=std::max(fabs(size[1]),0.02);

    Vector ax1(4,0.0);
    ax1[2]=1.0;
    ax1[3]=90.0*CTRL_DEG2RAD;

    Matrix H=axis2dcm(ax1);
    H(0,3)=c[0];
    H(1,3)=c[1];
    H(2,3)=c[2];
    H(3,3)=1.0;

    targets.clear();
    for (int i=0; i<2; i++)
    {
        for (double theta=0.0; theta<=2.0*M_PI; theta+=(2.0*M_PI)/50.0)
        {
            Vector x(4);
            x[0]=a*cos(theta);
            x[1]=b*sin(theta);
            x[2]=0.0;
            x[3]=1.0;
            x=H*x;
            x.pop_back();
            targets.push_back(x);
            yInfo("created point #%d=(%s)",(int)targets.size(),x.toString(3,3).c_str());
        }

        Vector ax2(4,0.0);
        ax2[1]=1.0;
        ax2[3]=90.0*CTRL_DEG2RAD;
        H=axis2dcm(ax2)*axis2dcm(ax1);
        H(0,3)=c[0];
        H(1,3)=c[1];
        H(2,3)=c[2];
        H(3,3)=1.0;
    }

    curExplorationCenter=c;
    return true;
}