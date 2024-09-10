/*! \brief The main function.
 *
 */
int main(void)
{
  aes_config_t      AesConf;        // AES config structure
  int               i;
  static const gpio_map_t USART_GPIO_MAP =      // USART GPIO map
  {
    {DMACA_AES_EVAL_USART_RX_PIN, DMACA_AES_EVAL_USART_RX_FUNCTION},
    {DMACA_AES_EVAL_USART_TX_PIN, DMACA_AES_EVAL_USART_TX_FUNCTION}
  };
  static const usart_options_t USART_OPTIONS =  // USART options.
  {
    .baudrate     = DMACA_AES_EVAL_USART_BAUDRATE,
    .charlength   = 8,
    .paritytype   = USART_NO_PARITY,
    .stopbits     = USART_1_STOPBIT,
    .channelmode  = USART_NORMAL_CHMODE
  };


#if BOARD == EVK1104
  if( PM_FREQ_STATUS_FAIL==pm_configure_clocks(&pm_freq_param) )
    while(1);
#endif

  init_hmatrix();

  // Assign GPIO to USART.
  gpio_enable_module(USART_GPIO_MAP,
                     sizeof(USART_GPIO_MAP) / sizeof(USART_GPIO_MAP[0]));

  // Initialize USART in RS232 mode.
  usart_init_rs232(DMACA_AES_EVAL_USART, &USART_OPTIONS, DMACA_AES_EVAL_CPU_FREQ);
  print(DMACA_AES_EVAL_USART, "\x1B[2J\x1B[H.: Using the AES with the DMACA at ");
  print_ulong(DMACA_AES_EVAL_USART, DMACA_AES_EVAL_CPU_FREQ);
  print(DMACA_AES_EVAL_USART, "Hz :.\r\n\r\n");

  //****************************************************************************
  //               CIPHER IN DMA MODE: RAM -> AES -> RAM
  //  - 256bit cryptographic key
  //  - CBC cipher mode
  //  - No counter measures
  //****************************************************************************

  // Init the input array.
  for(i=0; i<DMACA_AES_EVAL_BUF_SIZE; i+=DMACA_AES_EVAL_REFBUF_SIZE)
  {
    memcpy(InputData+i, RefInputData, DMACA_AES_EVAL_REFBUF_SIZE*sizeof(unsigned int));
  }

  //====================
  // Configure the AES.
  //====================
  AesConf.ProcessingMode = AES_PMODE_CIPHER;  // Cipher
  AesConf.ProcessingDelay = 0;                // No delay: best performance
  AesConf.StartMode = AES_START_MODE_DMA;     // DMA mode
  AesConf.KeySize = AES_KEY_SIZE_256;         // 256bit cryptographic key
  AesConf.OpMode = AES_CBC_MODE;              // CBC cipher mode
  AesConf.LodMode = 0;                        // LODMODE == 0 : the end of the
  // encryption is notified by the DMACA transfer complete interrupt. The output
  // is available in the OutputData[] buffer.
  AesConf.CFBSize = 0;                        // Don't-care because we're using the CBC mode.
  AesConf.CounterMeasureMask = 0;             // Disable all counter measures.
  aes_configure(&AVR32_AES, &AesConf);


  //****************************************************************************
  //  - input of 16 32bit words in CPUSRAM
  //  - output of 16 32bit words in CPUSRAM
  //****************************************************************************
  print(DMACA_AES_EVAL_USART, "\r\n---------------------------------------------------\r\n");
  print(DMACA_AES_EVAL_USART, "------ Cipher in DMA Mode: CPUSRAM -> AES -> CPUSRAM ------\r\n");
  print(DMACA_AES_EVAL_USART, "       - 256bit cryptographic key\r\n");
  print(DMACA_AES_EVAL_USART, "       - CBC cipher mode\r\n");
  print(DMACA_AES_EVAL_USART, "       - No counter measures\r\n");
  print(DMACA_AES_EVAL_USART, "       - input of 16 32bit words in CPUSRAM\r\n");
  print(DMACA_AES_EVAL_USART, "       - output of 16 32bit words in CPUSRAM\r\n");
  print(DMACA_AES_EVAL_USART, "---------------------------------------------------\r\n");

  test_ram_aes_ram(16, (unsigned int *)InputData, (unsigned int *)OutputData);
  gpio_clr_gpio_pin(DMACA_AES_EVAL_LED1);

  //****************************************************************************
  //  - input of 256 32bit words in CPUSRAM
  //  - output of 256 32bit words in CPUSRAM
  //****************************************************************************
  print(DMACA_AES_EVAL_USART, "\r\n---------------------------------------------------\r\n");
  print(DMACA_AES_EVAL_USART, "------ Cipher in DMA Mode: CPUSRAM -> AES -> CPUSRAM ------\r\n");
  print(DMACA_AES_EVAL_USART, "       - 256bit cryptographic key\r\n");
  print(DMACA_AES_EVAL_USART, "       - CBC cipher mode\r\n");
  print(DMACA_AES_EVAL_USART, "       - No counter measures\r\n");
  print(DMACA_AES_EVAL_USART, "       - input of 256 32bit words in CPUSRAM\r\n");
  print(DMACA_AES_EVAL_USART, "       - output of 256 32bit words in CPUSRAM\r\n");
  print(DMACA_AES_EVAL_USART, "---------------------------------------------------\r\n");

  test_ram_aes_ram(256, (unsigned int *)InputData, (unsigned int *)OutputData);
  gpio_clr_gpio_pin(DMACA_AES_EVAL_LED2);

  //****************************************************************************
  //  - input of 256 32bit words in HSBSRAM0
  //  - output of 256 32bit words in HSBSRAM1
  //****************************************************************************
  print(DMACA_AES_EVAL_USART, "\r\n---------------------------------------------------\r\n");
  print(DMACA_AES_EVAL_USART, "------ Cipher in DMA Mode: HSBSRAM0 -> AES -> HSBSRAM1 ------\r\n");
  print(DMACA_AES_EVAL_USART, "       - 256bit cryptographic key\r\n");
  print(DMACA_AES_EVAL_USART, "       - CBC cipher mode\r\n");
  print(DMACA_AES_EVAL_USART, "       - No counter measures\r\n");
  print(DMACA_AES_EVAL_USART, "       - Input of 256 32bit words in HSBSRAM0\r\n");
  print(DMACA_AES_EVAL_USART, "       - Output of 256 32bit words in HSBSRAM1\r\n");
  print(DMACA_AES_EVAL_USART, "---------------------------------------------------\r\n");

  // Set the Src and Dst array addresses to respectively HSBSRAM0 & HSBRAM1.
  pSrcData_HsbSram = (unsigned int *)AVR32_INTRAM0_ADDRESS;
  pDstData_HsbSram = (unsigned int *)AVR32_INTRAM1_ADDRESS;

  // Init the input array.
  for(i=0; i<DMACA_AES_EVAL_BUF_SIZE; i+=DMACA_AES_EVAL_REFBUF_SIZE)
  {
    memcpy(pSrcData_HsbSram+i, RefInputData, DMACA_AES_EVAL_REFBUF_SIZE*sizeof(unsigned int));
  }

  test_ram_aes_ram(256, pSrcData_HsbSram, (unsigned int *)pDstData_HsbSram);
  gpio_clr_gpio_pin(DMACA_AES_EVAL_LED3);
  print(DMACA_AES_EVAL_USART, "\r\nDone!");

  // End of tests: go to sleep.
  SLEEP(AVR32_PM_SMODE_STATIC);
  while (true);
}