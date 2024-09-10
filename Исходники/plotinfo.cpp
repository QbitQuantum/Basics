// update information for current-cursor position ---------------------------
void __fastcall TPlot::UpdatePoint(int x, int y)
{
    gtime_t time;
    TPoint p(x,y);
    double enu[3]={0},rr[3],pos[3],xx,yy,r,xl[2],yl[2],q[2],az,el,snr;
    int i;
    char tstr[64];
    AnsiString msg;
    
    trace(4,"UpdatePoint: x=%d y=%d\n",x,y);
    
    if (PlotType==PLOT_TRK) { // track-plot
        
        if (norm(OPos,3)>0.0) {
            GraphT->ToPos(p,enu[0],enu[1]);
            ecef2pos(OPos,pos);
            enu2ecef(pos,enu,rr);
            for (i=0;i<3;i++) rr[i]+=OPos[i];
            ecef2pos(rr,pos);
            msg=LatLonStr(pos,8);
        }
    }
    else if (PlotType==PLOT_SKY||PlotType==PLOT_MPS) { // sky-plot
        
        GraphS->GetLim(xl,yl);
        GraphS->ToPos(p,q[0],q[1]);
        r=(xl[1]-xl[0]<yl[1]-yl[0]?xl[1]-xl[0]:yl[1]-yl[0])*0.45;
        
        if ((el=90.0-90.0*norm(q,2)/r)>0.0) {
            az=el>=90.0?0.0:ATAN2(q[0],q[1])*R2D;
            if (az<0.0) az+=360.0;
            msg.sprintf("AZ=%5.1f" CHARDEG " EL=%4.1f" CHARDEG,az,el);
        }
    }
    else if (PlotType==PLOT_SNRE) { // snr-el-plot
        GraphE[0]->ToPos(p,q[0],q[1]);
        msg.sprintf("EL=%4.1f " CHARDEG,q[0]);
    }
    else {
        GraphG[0]->ToPos(p,xx,yy);
        time=gpst2time(Week,xx);
        if      (TimeLabel==2) time=utc2gpst(time); // UTC
        else if (TimeLabel==3) time=timeadd(gpst2utc(time),-9*3600.0); // JST
        TimeStr(time,0,1,tstr);
        msg=tstr;
    }
    Panel22->Visible=true;
    Message2->Caption=A2U(msg);
}