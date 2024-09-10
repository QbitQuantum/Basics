// *************************************************************************************************
// @fn          display_eggtimer
// @brief       eggtimer user routine.
// @param       u8 line		LINE2
//		u8 update	DISPLAY_LINE_UPDATE_PARTIAL, DISPLAY_LINE_UPDATE_FULL
// @return      none
// *************************************************************************************************
void display_eggtimer(u8 line, u8 update)
{
	u8 * str;
	
	// Partial line update only
	if (update == DISPLAY_LINE_UPDATE_PARTIAL)
	{
		// Check draw flag to minimize workload
		switch(sEggtimer.drawFlag) 
		{
		    case 3: // Hours changed
			str = _itoa(sEggtimer.hours, 2, 0);
			display_chars(LCD_SEG_L2_5_4, str, SEG_ON);
		    case 2: // Minutes changed
			str = _itoa(sEggtimer.minutes, 2, 0);
			display_chars(LCD_SEG_L2_3_2, str, SEG_ON);
		    case 1: // Seconds changed
			str = _itoa(sEggtimer.seconds, 2, 0);
			display_chars(LCD_SEG_L2_1_0, str, SEG_ON);
		}
		sEggtimer.drawFlag = 0; // Clear draw flag
	}
	// Redraw whole line
	else if (update == DISPLAY_LINE_UPDATE_FULL)	
	{
		// Display HH:MM:SS		
		str = _itoa(sEggtimer.hours, 2, 0);
		display_chars(LCD_SEG_L2_5_4, str, SEG_ON);
		str = _itoa(sEggtimer.minutes, 2, 0);
		display_chars(LCD_SEG_L2_3_2, str, SEG_ON);
		str = _itoa(sEggtimer.seconds, 2, 0);
		display_chars(LCD_SEG_L2_1_0, str, SEG_ON);
		
		display_symbol(LCD_SEG_L2_COL1, SEG_ON);
		display_symbol(LCD_SEG_L2_COL0, SEG_ON);
		
		if (sEggtimer.state != EGGTIMER_STOP) { // Blink if running or alarm triggered
			display_symbol(LCD_ICON_RECORD, SEG_ON_BLINK_ON);
		}
		else { // Solid on if not running
			display_symbol(LCD_ICON_RECORD, SEG_ON_BLINK_OFF);
		}
	}
	else if (update == DISPLAY_LINE_CLEAR)
	{
		// Stop blinking icon only if eggtimer isn't running
		if (sEggtimer.state == EGGTIMER_STOP) display_symbol(LCD_ICON_RECORD, SEG_OFF);
	}
}