/**
  * @brief  Enables ADC DMA request after last transfer (Single-ADC mode) and enables ADC peripheral  
  * @param  hadc: pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @param  pData: The destination Buffer address.
  * @param  Length: The length of data to be transferred from ADC peripheral to memory.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
{
  uint16_t i = 0;
  
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
  assert_param(IS_ADC_EXT_TRIG_EDGE(hadc->Init.ExternalTrigConvEdge));
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Enable ADC overrun interrupt */
  __HAL_ADC_ENABLE_IT(hadc, ADC_IT_OVR);
  
  /* Enable ADC DMA mode */
  hadc->Instance->CR2 |= ADC_CR2_DMA;
  
  /* Set the DMA transfer complete callback */
  hadc->DMA_Handle->XferCpltCallback = ADC_DMAConvCplt;
  
  /* Set the DMA half transfer complete callback */
  hadc->DMA_Handle->XferHalfCpltCallback = ADC_DMAHalfConvCplt;
     
  /* Set the DMA error callback */
  hadc->DMA_Handle->XferErrorCallback = ADC_DMAError ;
  
  /* Enable the DMA Stream */
  HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&hadc->Instance->DR, (uint32_t)pData, Length);
  
  /* Change ADC state */
  hadc->State = HAL_ADC_STATE_BUSY_REG;
   
  /* Check if ADC peripheral is disabled in order to enable it and wait during 
     Tstab time the ADC's stabilization */
  if((hadc->Instance->CR2 & ADC_CR2_ADON) != ADC_CR2_ADON)
  {  
    /* Enable the Peripheral */
    __HAL_ADC_ENABLE(hadc);
    
    /* Delay inserted to wait during Tstab time the ADC's stabilazation */
    for(; i <= 540; i++)
    {
      __NOP();
    }
  }
  
  /* if no external trigger present enable software conversion of regular channels */
  if (hadc->Init.ExternalTrigConvEdge == ADC_EXTERNALTRIGCONVEDGE_NONE)
  {
    /* Enable the selected ADC software conversion for regular group */
    hadc->Instance->CR2 |= ADC_CR2_SWSTART;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return HAL_OK;
}