void Manutencao(Button bUp, Button bDown, Button bOk){
	Manutencao_Init();
	
	LCD_WriteString("MODO DE");
	LCD_Goto(1,6);
	LCD_WriteString("Manutencao");
	TMR0_Delay(3000);
	
	LCD_Clear();
	
	getSubMenu();
	
	while(1){
		if(BUTTON_getState(bUp){
			executeAction(MUP);
		}
		if(BUTTON_getState(bDown){
			executeAction(MDOWN);
		}
		if(BUTTON_getState(bOk){
			//SAIR DO MODO DE MANUTENCAO
			if(m.currSubMenu == 6)
				return;
			executeAction(MOK);
		}
	}
}