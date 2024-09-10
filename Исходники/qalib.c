Static void
INIT_DEFAULTS(int Echo)
{

/* These can be removed, they are not used functionally.  Only to keep
   some having to change some function parameters.
*/
char Device[30];
    Test_Com = __default_test_term;
    Ref_Com = __default_ref_term;
    Aux_A_Com = __default_aux_a;
    Aux_B_Com = __default_aux_b;
    __Refpres = (__default_ref_term != 0);
    __Aux_A_Pres = (__default_aux_a != 0);
    __Aux_B_Pres = (__default_aux_b != 0);
    __Data_Com[0] = __default_datacom_rec;
    __Data_Com[1] = __default_datacom_rec;
    __Data_Com[2] = __default_datacom_rec;
    __Data_Com[3] = __default_datacom_rec;
    /* __Rs_Time_Out = false;               */
/* ****************************************************************/ 

    /* Open /dev/tty and obtain file descriptor and FILE pointer. */
    if((fd_test = open("/dev/tty", O_RDWR)) < 0) {
      (void) perror("INIT_DEFAULTS: /dev/tty open:");
      (void) exit(1);
    }

    f_test = fdopen(fd_test, "w"); 
    (void) setvbuf(f_test, (char *) 0, _IONBF, 0);

    /* get struct termio for later restoration and use for setting defaults */
    if(tcgetattr(fd_test, &termio_orig) < 0) {
      (void) perror("INIT_DEFAULTS: tcgetattr:");
      (void) exit(1);
    }
    
    /* Default settings determined from PANACOM tests, and translated to
       HP_UX environment. Along with default settings using struct termios. */

/* Canonical Input is OFF  */

    termio_test = termio_orig;
    termio_test.c_iflag &= ~(ICRNL | IUCLC | IXANY);
    termio_test.c_iflag |= (IXON | IXOFF);  
    termio_test.c_lflag &= ~(ICANON | ECHO);
    termio_test.c_cflag |= (CS8 | CREAD);
    termio_test.c_cc[VMIN] = 1;    
    termio_test.c_cc[VTIME] = 0;  
  
   
/* Canonical Input is ON  */
/*
   termio_test = termio_orig;
   termio_test.c_iflag |= (IXON | IXOFF);
   termio_test.c_lflag |= (ICANON);
   termio_test.c_lflag &= ~(ECHO);
   termio_test.c_cflag |= CS8; 
   termio_test.c_cc[VINTR] = _POSIX_VDISABLE;
   termio_test.c_cc[VQUIT] = _POSIX_VDISABLE;
   termio_test.c_cc[VERASE] = _POSIX_VDISABLE;
   termio_test.c_cc[VKILL] = _POSIX_VDISABLE;
   termio_test.c_cc[VEOF] = _POSIX_VDISABLE;
*/
     


/* turn on signal handlers... */
    (void) signal(SIGHUP, cleanup);
    (void) signal(SIGINT, cleanup);
    (void) signal(SIGQUIT, cleanup);
    (void) signal(SIGTERM, cleanup);

    /* set a 2 minute timeout... */
    (void) signal(SIGALRM, timeout);
    /* (void) alarm(240);  */


    /* set new terminal control attributes */
    if(tcsetattr(fd_test,TCSADRAIN,&termio_test) < 0) {
      (void) perror("tcsetattr New");
      (void) exit(1);
    }

    /* default terminal settings  */
    SPEEDTEST(B9600);
    PARITYTEST("4");                  /* 8 bit no parity */
    HANDSHAKE_COM("X");               /* IXON and IXOFF  */
    if (Echo) ECHO_COM("ON");         /* echoing on     */
    else ECHO_COM("OFF");         /* echoing off     */

}