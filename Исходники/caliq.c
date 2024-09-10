void cal_iqbalance(void)
{
char s[80];
int seg,color;
int ia,ib;
int i,j,k,m,n,mm,errskip;
float z[2*MAX_ADCHAN];
float t1,t2,t3;
caliq_clear_flag=TRUE;
clear_fft1_filtercorr();
bal_updflag=-1;
bal_segments=32;
bal_screen=screen_width;
make_power_of_two(&bal_screen);
if(bal_screen > screen_width)bal_screen>>=1;
mm=twice_rxchan;
restart:;
thread_status_flag[THREAD_CAL_IQBALANCE]=THRFLAG_ACTIVE;
if(bal_segments > BAL_MAX_SEG)bal_segments = BAL_MAX_SEG;
if(bal_segments > fft1_size/4)bal_segments = fft1_size/4;
if(bal_segments < 8)bal_segments = 8;
cal_initscreen();
lir_text(0,1,"Connect signal generator to antenna input(s).");
sprintf(s,"The frequency range is split in %d segments.",bal_segments);
lir_text(0,2,s);
lir_text(0,3,"Tune and wait for each segment to become green.");
settextcolor(14);
lir_text(5,4,"+/- => Change no of segments");
lir_text(7,5,  "S => Save current RAM contents to disk");
lir_text(7,6,  "C => Clear RAM");
lir_text(7,7,  "U => Compute new calibration and store in RAM");
settextcolor(7);
if(caliq_clear_flag)
  {
  for(i=0; i<=bal_segments; i++)bal_flag[i]=0;
  }
lir_refresh_screen();
while(thread_command_flag[THREAD_CAL_IQBALANCE] == THRFLAG_ACTIVE)
  {
  clear_lines(8,9);
  errskip=0;
  for(j=0; j<ui.rx_ad_channels; j++)
    {
    t1=(100*ad_maxamp[j])/0x8000;
    if(t1>90)
      {
      settextcolor(12);
      lir_text(10,8,"O V E R L O A D");
      errskip=1;
      }
    if(t1<5)
      {
      settextcolor(12);
      lir_text(10,8,"Signal too weak");
      errskip=1; 
      }
    sprintf(s,"A/D(%d) %.2f%%",j,t1);
    lir_text(20*j,9,s);
    settextcolor(7);
    }
  workload_reset_flag++;
  while(fft1_pb==fft1_px &&
                thread_command_flag[THREAD_CAL_IQBALANCE] == THRFLAG_ACTIVE)
    {     
    lir_sem_wait(SEM_FFT1);
    }
// Skip old data in case the cpu is a bit slow.
  while( ((fft1_pb-fft1_px+fft1_mask+1)&fft1_mask) > 2*fft1_block &&
                thread_command_flag[THREAD_CAL_IQBALANCE] == THRFLAG_ACTIVE)
    {
    lir_sem_wait(SEM_FFT1);
    fft1_nx=(fft1_nx+1)&fft1n_mask;
    fft1_px=fft1_nx*fft1_block;
    }
// Convert complex amplitudes to power and phase, store in cal_buf.
// Get the point of maximum. 
  t2=0;
  k=0;
  for(i=0; i<fft1_size; i++)
    {
    t1=0;
    for(j=0; j<mm; j+=2)
      {
      cal_buf[mm*i+j]=pow(fft1_float[fft1_px+mm*i+j  ],2.0)+
                       pow(fft1_float[fft1_px+mm*i+j+1],2.0);
      t1+=cal_buf[mm*i+j];
      cal_buf[mm*i+j+1]=atan2(fft1_float[fft1_px+mm*i+j+1],
                               fft1_float[fft1_px+mm*i+j  ]);
      }
    if(t2<t1)
      {
      t2=t1;
      k=i;
      }
    }
  fft1_nx=(fft1_nx+1)&fft1n_mask;
  fft1_px=(fft1_px+fft1_block)&fft1_mask;
  if(errskip==1) goto skipdat; 
  if(k<2)k=2;
  if(k>fft1_size-3)k=fft1_size-3;
// Since we use a sin power 4 window a peak will be a few points wide.
// collect the average amplitude ratio and average phase sum 
// Use power as weight factor in averaging.
  clear_lines(10,10);
  for(j=0; j<mm; j+=2)
    {
    z[2*j]=z[2*j+1]=z[2*j+2]=z[2*j+3]=0;
    for(i=k-2; i<=k+2; i++)
      {
      m=fft1_size-i;
      t1=cal_buf[mm*m+j+1]+cal_buf[mm*i+j+1];
      if(t1<-PI_L)t1+=2*PI_L;
      if(t1>PI_L)t1-=2*PI_L;
      t3=cal_buf[mm*i+j];
      t2=sqrt(cal_buf[mm*m+j]/cal_buf[mm*i+j]);
      z[2*j]+=t3;
      z[2*j+1]+=t3*t2;
      z[2*j+2]+=t3*t1;
      z[2*j+3]+=t3*i;
      }
    z[2*j+1]/=z[2*j];
    z[2*j+2]/=z[2*j];
    z[2*j+3]/=z[2*j];
    ia=z[2*j+3]+0.5;
    ib=ia+4;
    ia=ia-4;
    if(ia<0)ia=0;
    if(ib>fft1_size)ib=fft1_size;
    if(cal_buf[mm*ia+j]+cal_buf[mm*ib+j]>0.02*cal_buf[mm*k+j])
      {
      lir_text(0,10,"Signal too unstable");
      goto skipdat;
      }
    }
  clear_lines(10,10);
  seg=(bal_segments*z[3])/fft1_size+0.5;
  if(seg > bal_segments)seg=bal_segments;
  for(j=2; j<mm; j+=2)
    {
    k=(bal_segments*z[2*j+3])/fft1_size+0.5;
    if(seg != k )
      {
      lir_text(0,10,"Channels differ");
      goto skipdat;
      }
    }    
  if(bal_flag[seg]==BAL_AVGNUM)
    {
    sprintf(s,"Segment %d ok",seg);
    lir_text(0,10,s);
    goto skipdat_a;
    }
  k=(bal_flag[seg]*bal_segments+seg)*ui.rx_rf_channels;  
  for(j=0; j<ui.rx_rf_channels; j++)
    {
    bal_pos[k+j]=z[4*j+3]+0.5;
    bal_phsum[k+j]=z[4*j+2];
    bal_amprat[k+j]=z[4*j+1];
    }
  bal_flag[seg]++;
  skipdat_a:;
  for(j=0; j<ui.rx_rf_channels; j++)
    {
    sprintf(s,"Ch(%d) A=%f ph=%f",j,z[4*j+1],z[4*j+2]);
    lir_text(30*j,11,s);
    }
skipdat:;
  m=fft1_size/bal_screen;
  for(j=0; j<mm; j+=2)
    {
    for(i=0; i<bal_screen; i++)
      {
      lir_setpixel(i, cal_graph[bal_screen*j+i], 0);  
      k=i*m;
      if(k>fft1_size-m)k=fft1_size-m;
      t2=0;
      for(n=0;n<m;n++)t2+=cal_buf[mm*(k+n-m/2)+j];
      t2/=m;
      t2=0.03*log10(t2)-0.05;   
      if(t2 <-0.28)t2=-0.28;
      if(t2 > 0.28)t2= 0.28;
      if(j>0)t2-=.2;
      cal_graph[bal_screen*j+i]=screen_height*(0.5-t2);
      seg=(float)(bal_segments*k)/fft1_size+0.5;    
      color=13;
      if(bal_flag[seg]==0) color=15;
      if(bal_flag[seg]==BAL_AVGNUM)color=10;
      lir_setpixel(i, cal_graph[bal_screen*j+i], color);  
      }
    }
  lir_refresh_screen();
  }
if(thread_command_flag[THREAD_CAL_IQBALANCE]==THRFLAG_IDLE)
  {
  thread_status_flag[THREAD_CAL_IQBALANCE]=THRFLAG_IDLE;
  while(thread_command_flag[THREAD_CAL_IQBALANCE]==THRFLAG_IDLE)
    {
    lir_sem_wait(SEM_FFT1);
    fft1_nx=(fft1_nx+1)&fft1n_mask;
    fft1_px=fft1_nx*fft1_block;
    }
  if(thread_command_flag[THREAD_CAL_IQBALANCE]==THRFLAG_ACTIVE)goto restart;
  }  
thread_status_flag[THREAD_CAL_IQBALANCE]=THRFLAG_RETURNED;
while(thread_command_flag[THREAD_CAL_IQBALANCE] != THRFLAG_NOT_ACTIVE)
  {
  lir_sleep(1000);
  }
}