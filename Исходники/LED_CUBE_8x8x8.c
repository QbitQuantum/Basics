void LED_CUBE_Timer (void) {
	int j=0;
	static int cube_show_layer = 0;
	
	LED_CUBE_Layers_Set(0x00);
	
	__nop();
	
	for (j=0; j<8; j++) {
		LED_CUBE_Outputs_Set(~cube[cube_show_layer][j]);
		__nop();
		LED_CUBE_Clock_Set(j, TRUE);
		__nop();
		LED_CUBE_Clock_Set(j, FALSE);
		__nop();
	}

	LED_CUBE_Layer_Set(cube_show_layer, TRUE);
	Delay_us(100);
	LED_CUBE_Layers_Set(0x00);

	__nop();
	
	if (cube_show_layer < 7) {
		cube_show_layer++;
	} else {
		cube_show_layer = 0;
	}
}