// update Multipath ------------------------------------------------------------
void __fastcall TPlot::UpdateMp(void)
{
    AnsiString s;
    obsd_t *data;
    double lam1,lam2,I,C,B;
    int i,j,k,f1,f2,sat,sys,per,per_=-1,n;
    
    trace(3,"UpdateMp\n");
    
    for (i=0;i<NFREQ+NEXOBS;i++) {
        delete [] Mp[i]; Mp[i]=NULL;
    }
    if (Obs.n<=0) return;
    
    for (i=0;i<NFREQ+NEXOBS;i++) {
        Mp[i]=new double[Obs.n];
    }
    ReadWaitStart();
    ShowLegend(NULL);
    
    for (i=0;i<Obs.n;i++) {
        data=Obs.data+i;
        sys=satsys(data->sat,NULL);
        
        for (j=0;j<NFREQ+NEXOBS;j++) {
            Mp[j][i]=0.0;
            
            code2obs(data->code[j],&f1);
            
            if      (sys==SYS_GAL) f2=f1==1?3:1;
            else if (sys==SYS_CMP) f2=f1==2?5:2;
            else                   f2=f1==1?2:1;
            
            lam1=satwavelen(data->sat,f1-1,&Nav);
            lam2=satwavelen(data->sat,f2-1,&Nav);
            if (lam1==0.0||lam2==0.0) continue;
            
            if (data->P[j]!=0.0&&data->L[j]!=0.0&&data->L[f2-1]) {
                C=SQR(lam1)/(SQR(lam1)-SQR(lam2));
                I=lam1*data->L[j]-lam2*data->L[f2-1];
                Mp[j][i]=data->P[j]-lam1*data->L[j]+2.0*C*I;
            }
        }
    }
    for (sat=1;sat<=MAXSAT;sat++) for (i=0;i<NFREQ+NEXOBS;i++) {
        sys=satsys(sat,NULL);
        
        for (j=k=n=0,B=0.0;j<Obs.n;j++) {
            if (Obs.data[j].sat!=sat) continue;
            
            code2obs(Obs.data[j].code[i],&f1);
            
            if      (sys==SYS_GAL) f2=f1==1?3:1;
            else if (sys==SYS_CMP) f2=f1==2?5:2;
            else                   f2=f1==1?2:1;
            
            if ((Obs.data[j].LLI[i]&1)||(Obs.data[j].LLI[f2-1]&1)||
                fabs(Mp[i][j]-B)>THRES_SLIP) {
                
                for (;k<j;k++) if (Obs.data[k].sat==sat) Mp[i][k]-=B;
                B=Mp[i][j]; n=1; k=j;
            }
            else {
                if (n==0) k=j;
                B+=(Mp[i][j]-B)/++n;
            }
        }
        if (n>0) {
            for (;k<j;k++) if (Obs.data[k].sat==sat) Mp[i][k]-=B;
        }
        per=sat*100/MAXSAT;
        if (per!=per_) {
            ShowMsg(s.sprintf("updating multipath... (%d%%)",(per_=per)));
            Application->ProcessMessages();
        }
    }
    ReadWaitEnd();
}