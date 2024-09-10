void ADC_Test(void)
{
	int tem[2];
//	char *c = value;

//	AD_value=ADC_GetConversionValue(ADC1);
	tem[0] = (int)ADC_ValueTab[0]*331/4096;
    tem[1] = (int)ADC_ValueTab[1]*331/4096;
	IntToChar(tem[0]);
    IntToChar(tem[1]);
//	TFTShowString24(50,250,c,BLUE,0);
    SetEditTmp(&MAIN_WIN_ADC,tem[0]);
    SetEditTmp(&MAIN_WIN_ADC1,tem[1]);
	#ifdef DEBUG
//    printf("ADC: %.3f \r\n",(float)ADC_ValueTab[1]*336/409600);
    printf("ADC: %d \r\n",ADC_ValueTab[0]);
    printf("ADC: %d \r\n",ADC_ValueTab[1]);
    #endif
}