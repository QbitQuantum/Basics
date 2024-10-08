void Action_Port_Cfg(char *Str)
{
	char *P=Str,*T;
	GPIO_InitTypeDef GPIO_InitStructure; 
	uint32_t RCC_APB2Periph_GPIOx; 
  GPIO_InitStruct List;
	List.GPIO_Pin=12;
	T=Strstr(P,"p");
	if(T)
	{
		switch(T[1])
		{
			case 'a':List.GPIOx=GPIOA;RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOA;break;
			case 'b':List.GPIOx=GPIOB;RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOB;break;
			case 'c':List.GPIOx=GPIOC;RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOC;break;
			case 'd':List.GPIOx=GPIOD;RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOD;break;
			case 'e':List.GPIOx=GPIOE;RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOE;break;
			case 'f':List.GPIOx=GPIOF;RCC_APB2Periph_GPIOx=RCC_APB2Periph_GPIOF;break;
		}
		List.GPIO_Pin=1<<(T[2]-'0');
		if(Strstr(T,"out"))List.GPIO_Mode=GPIO_Mode_Out_PP;
		else if(Strstr(T,"ipd"))List.GPIO_Mode=GPIO_Mode_IPD;
		else if(Strstr(T,"ipu"))List.GPIO_Mode=GPIO_Mode_IPU;
		else if(Strstr(T,"ain"))List.GPIO_Mode=GPIO_Mode_AIN;
		else if(Strstr(T,"inf"))List.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin=List.GPIO_Pin; 
		GPIO_InitStructure.GPIO_Mode=List.GPIO_Mode;
		GPIO_Init(List.GPIOx, &GPIO_InitStructure);
	}
}