int init_sdr14(void)
{
char ss[80];
char sn[80];
char s[80];
int i, line;
float t1;
FILE *sdr14_file;
int *sdr_pi;
char *looking;
looking="Looking for an SDR on the USB port.";
// Set device_no to appropriate values if some dedicated hardware
// is selected by the user.
//  ------------------------------------------------------------
// See if there is an SDR-14 or an SDR-IQ on the system.
settextcolor(12);
lir_text(10,10,looking);
SNDLOG"\n%s",looking);
lir_text(10,11,"Reset CPU, USB and SDR hardware if system hangs here.");
lir_refresh_screen();
open_sdr14();
settextcolor(7);
clear_lines(10,11);
lir_refresh_screen();
line=0;
if(sdr != -1)
  {
  SNDLOG"open_sdr14 sucessful.\n");
  lir_text(5,5,"An SDR is detected on the USB port.");
  lir_text(5,6,"Do you want to use it for RX input (Y/N)?");
qsdr:;
  await_processed_keyboard();
  if(kill_all_flag) goto sdr14_errexit;
  if(lir_inkey == 'Y')
    {
    sdr_target_name(sn);
    sprintf(s,"Target name: %s",sn);
    SNDLOG"%s\n",s);
    lir_text(5,10,s);
    if( strcmp(sdr14_name_string,sn) == 0)
      {
      ui.rx_addev_no=SDR14_DEVICE_CODE;
      }
    if( strcmp(sdriq_name_string,sn) == 0)
      {
      ui.rx_addev_no=SDRIQ_DEVICE_CODE;
      }
    if(ui.rx_addev_no == -1)  
      {
      lir_text(5,12,"Unknown hardware, can not use.");
      lir_text(5,13,press_any_key);
      await_keyboard();
      if(kill_all_flag) goto sdr14_errexit;
      clear_screen();
      }
    else
      {
      ui.rx_input_mode=IQ_DATA+DIGITAL_IQ;
      ui.rx_rf_channels=1;
      ui.rx_ad_channels=2;
      ui.rx_admode=0;
      sdr_target_serial_number(ss);
      sprintf(s,"Serial no: %s",ss);
      lir_text(5,11,s);
      sdr_target_interface_version(ss);
      i=(short int)ss[0];
      sprintf(s,"Interface version: %d.%02d",i/100,i%100);
      lir_text(5,12,s);
      sdr_target_boot_version(ss);
      i=(short int)ss[0];
      sprintf(s,"PIC boot version: %d.%02d",i/100,i%100);
      lir_text(5,13,s);
      sdr_target_firmware_version(ss);
      i=(short int)ss[0];
      sprintf(s,"PIC firmware version: %d.%02d",i/100,i%100);
      lir_text(5,14,s);
      lir_text(10,16,"PRESS ANY KEY");
restart_sdr14par:;
      await_processed_keyboard();
      if(kill_all_flag) goto sdr14_errexit;
      clear_screen();
      sprintf(s,"%s selected for input",sn);
      lir_text(10,line,s);
      line++;
      if(ui.newcomer_mode == 0)
        {
        lir_text(5,line,"Set CIC2 decimation (2 - 16)");
        sdr14.m_cic2=lir_get_integer(35, line, 2, 2,16);
        if(kill_all_flag)goto sdr14_errexit;
        t1=SDR14_SAMPLING_CLOCK/sdr14.m_cic2;
        sprintf(s,"clk=%.2f MHz",t1);
        lir_text(39,line,s);
        line++;
        lir_text(5,line,"Set CIC5 decimation (2 - 32)");
        sdr14.m_cic5=lir_get_integer(35, line, 2, 2,32);
        if(kill_all_flag)goto sdr14_errexit;
        t1/=sdr14.m_cic5;
        sprintf(s,"clk=%.4f MHz",t1);
        lir_text(39,line,s);
        line++;
        lir_text(5,line,"Set RCF decimation (2 - 32)");
        sdr14.m_rcf=lir_get_integer(35, line, 2, 2,32);
        if(kill_all_flag)goto sdr14_errexit;
        t1/=sdr14.m_rcf;
        ui.rx_ad_speed=t1*1000000;
        if(ui.rx_ad_speed > MAX_SDR14_SPEED)
          {
          line++;
          settextcolor(12);
          lir_text(5,line,
                "ERROR The sampling speed is far too high for USB 1.0");
          line++;
          lir_text(5,line,press_any_key);
          settextcolor(7);
          goto restart_sdr14par;
          }
        }
      else
        {
        sdr14.m_cic2=10;
        t1=SDR14_SAMPLING_CLOCK/sdr14.m_cic2;
        sdr14.m_cic5=10;
        t1/=sdr14.m_cic5;
        line++;
        for(i=4; i<8; i++)
          {
          sprintf(s,"RCF= %d  Speed %f kHz",i,1000*t1/i);
          lir_text(0,line,s);
          line++; 
          }
        line++;  
        lir_text(5,line,"Set RCF decimation (4 - 7)");
        sdr14.m_rcf=lir_get_integer(35, line, 2, 4,7);
        if(kill_all_flag)goto sdr14_errexit;
        t1/=sdr14.m_rcf;
        ui.rx_ad_speed=t1*1000000;
        }
      sprintf(s,"clk=%.2f kHz",t1*1000);
      lir_text(39,line,s);
      line++;
      lir_text(5,line,"Set RCF output shift (0 - 7)");
      sdr14.ol_rcf=lir_get_integer(35, line, 2, 0,7);
      if(kill_all_flag)goto sdr14_errexit;
      line++;
      if(ui.newcomer_mode == 0)
        {
        lir_text(5,line,"Set sampling clock shift (Hz)");
        sdr14.clock_adjust=lir_get_integer(35, line, 6,-10000,10000);
        if(kill_all_flag)goto sdr14_errexit;
        line++;
        }
      else
        {
        sdr14.clock_adjust=0;
        }
      adjusted_sdr_clock=SDR14_SAMPLING_CLOCK+0.000001*sdr14.clock_adjust,
      ui.rx_ad_speed=1000000.*adjusted_sdr_clock/(M_CIC2*M_CIC5*M_RCF);
      if(ui.rx_addev_no == SDR14_DEVICE_CODE)
        {
        lir_text(5,line,"Select direct input (0 - 1)");
        sdr14.input=lir_get_integer(35, line, 2, 0, 1);
        if(kill_all_flag)return 0;
        }
      else
        {
        if(ui.newcomer_mode == 0)
          {
          lir_text(5,line,"Attenuation below which to use 10dB (10 - 25)");
          sdr14.input=lir_get_integer(52, line, 2, 10, 25);
          if(kill_all_flag)return 0;
          }
        else
          {
          sdr14.input=20;  
          }
        }
      sdr14_file=fopen("par_sdr14","w");
      if(sdr14_file == NULL)
        {
        lirerr(381264);
sdr14_errexit:;
        close_sdr14();
        clear_screen(); 
        return 0;
        }
      sdr14.check=SDR14PAR_VERNR;
      sdr_pi=(void*)(&sdr14);
      for(i=0; i<MAX_SDR14_PARM; i++)
        {
        fprintf(sdr14_file,"%s [%d]\n",sdr14_parm_text[i],sdr_pi[i]);
        }
      parfile_end(sdr14_file);
      }
    }