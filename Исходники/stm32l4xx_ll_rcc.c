/**
  * @brief  Reset the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *         - MSI  ON and used as system clock source
  *         - HSE, HSI, PLL and PLLSAIxSource OFF
  *         - AHB, APB1 and APB2 prescaler set to 1.
  *         - CSS, MCO OFF
  *         - All interrupts disabled
  * @note   This function doesn't modify the configuration of the
  *         - Peripheral clocks
  *         - LSI, LSE and RTC clocks
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RCC registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_RCC_DeInit(void)
{
  uint32_t vl_mask = 0;

  /* Set MSION bit */
  LL_RCC_MSI_Enable();

  /* Insure MSIRDY bit is set before writing default MSIRANGE value */
  while (LL_RCC_MSI_IsReady() == 0)
  {
    __NOP();
  }

  /* Set MSIRANGE default value */
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_6);
  /* Set MSITRIM bits to the reset value*/
  LL_RCC_MSI_SetCalibTrimming(0);

  /* Set HSITRIM bits to the reset value*/
  LL_RCC_HSI_SetCalibTrimming(0x10);

  /* Reset CFGR register */
  LL_RCC_WriteReg(CFGR, 0x00000000);

  vl_mask = 0xFFFFFFFFU;

  /* Reset HSION, HSIKERON, HSIASFS, HSEON, PLLSYSON bits */
  CLEAR_BIT(vl_mask, (RCC_CR_HSION | RCC_CR_HSIASFS | RCC_CR_HSIKERON  | RCC_CR_HSEON |
  RCC_CR_PLLON));

  /* Reset PLLSAI1ON bit */
  CLEAR_BIT(vl_mask, RCC_CR_PLLSAI1ON);

#if defined(RCC_PLLSAI2_SUPPORT)
  /* Reset PLLSAI2ON bit */
  CLEAR_BIT(vl_mask, RCC_CR_PLLSAI2ON);
#endif /*RCC_PLLSAI2_SUPPORT*/

  /* Write new mask in CR register */
  LL_RCC_WriteReg(CR, vl_mask);

  /* Reset PLLCFGR register */
  LL_RCC_WriteReg(PLLCFGR, 16 << RCC_POSITION_PLLN);

  /* Reset PLLSAI1CFGR register */
  LL_RCC_WriteReg(PLLSAI1CFGR, 16 << RCC_POSITION_PLLSAI1N);

#if defined(RCC_PLLSAI2_SUPPORT)
  /* Reset PLLSAI2CFGR register */
  LL_RCC_WriteReg(PLLSAI2CFGR, 16 << RCC_POSITION_PLLSAI2N);
#endif /*RCC_PLLSAI2_SUPPORT*/

  /* Reset HSEBYP bit */
  LL_RCC_HSE_DisableBypass();

  /* Disable all interrupts */
  LL_RCC_WriteReg(CIER, 0x00000000);

  return SUCCESS;
}