// *************************************************************************************************
// @fn          display_altitude
// @brief       Display routine. Supports display in meters and feet. 
// @param       u8 line         LINE1
//              u8 update       DISPLAY_LINE_UPDATE_FULL, DISPLAY_LINE_UPDATE_PARTIAL, DISPLAY_LINE_CLEAR
// @return      none
// *************************************************************************************************
void display_altitude(u8 line, u8 update)
{
    u8 * str;
    s16 ft;
    
    // redraw whole screen
    if (update == DISPLAY_LINE_UPDATE_FULL) 
    {
        // Enable pressure measurement
        sAlt.state = MENU_ITEM_VISIBLE;

        // Start measurement
        start_altitude_measurement();
        
        // Display altitude
        display_altitude(LINE1, DISPLAY_LINE_UPDATE_PARTIAL);
    }
    else if (update == DISPLAY_LINE_UPDATE_PARTIAL)
    {
        // Update display only while measurement is active
        if (sAlt.timeout > 0)
        {
            // Altitude view
            if (PressDisplay == DISPLAY_DEFAULT_VIEW)
            {
                display_symbol(LCD_SEG_L1_DP1, SEG_OFF);
                if (sys.flag.use_metric_units)
                {
                    // Display "m" symbol
                    display_symbol(LCD_UNIT_L1_M, SEG_ON);
                    // Display altitude in xxxx m format, allow 3 leading blank digits
                    if (sAlt.altitude >= 0)
                    {
                        str = itoa(sAlt.altitude, 4, 3);
                        display_symbol(LCD_SYMB_ARROW_UP, SEG_ON);
                        display_symbol(LCD_SYMB_ARROW_DOWN, SEG_OFF);
                    }
                    else
                    {
                        str = itoa(sAlt.altitude*(-1), 4, 3);
                        display_symbol(LCD_SYMB_ARROW_UP, SEG_OFF);
                        display_symbol(LCD_SYMB_ARROW_DOWN, SEG_ON);
                    }
                }
                else
                {
                    // Display "ft" symbol
                    display_symbol(LCD_UNIT_L1_FT, SEG_ON);                 
                    
                    // Convert from meters to feet
                    ft = convert_m_to_ft(sAlt.altitude);
                    
                    // Limit to 9999ft (3047m)
                    if (ft > 9999) ft = 9999;
                    
                    // Display altitude in xxxx ft format, allow 3 leading blank digits
                    if (ft >= 0)
                    {
                        str = itoa(ft, 4, 3);
                        display_symbol(LCD_SYMB_ARROW_UP, SEG_ON);
                        display_symbol(LCD_SYMB_ARROW_DOWN, SEG_OFF);
                    }
                    else
                    {
                        str = itoa(ft*(-1), 4, 3);
                        display_symbol(LCD_SYMB_ARROW_UP, SEG_OFF);
                        display_symbol(LCD_SYMB_ARROW_DOWN, SEG_ON);
                    }               
                }
            }
            // Pressure view, unit: milliBar = hectoPascal
            else if (PressDisplay == DISPLAY_ALTERNATIVE_VIEW)
            {
                display_symbol(LCD_SEG_L1_DP1, SEG_OFF);
                display_symbol(LCD_UNIT_L1_M, SEG_OFF);
                display_symbol(LCD_UNIT_L1_FT, SEG_OFF);
                display_symbol(LCD_SYMB_ARROW_UP, SEG_OFF);
                display_symbol(LCD_SYMB_ARROW_DOWN, SEG_OFF);
                str = itoa(AmbientPressure, 4, 3);
            }
            // Pressure view, unit: PSI (Pound-force per square inch absolute) 1mbar = 0.01450377 PSI
            else  // DISPLAY_ALTERNATIVE_VIEW_2
            {
                str = itoa((u32)AmbientPressure * 10000L / 6895L, 4, 3);
                display_symbol(LCD_SEG_L1_DP1, SEG_ON);
            }
            display_chars(LCD_SEG_L1_3_0, str, SEG_ON);
        }
    }
    else if (update == DISPLAY_LINE_CLEAR)
    {
        // Disable pressure measurement
        sAlt.state = MENU_ITEM_NOT_VISIBLE;

        // Stop measurement
        stop_altitude_measurement();
        
        // Clean up function-specific segments before leaving function
        display_symbol(LCD_SEG_L1_DP1, SEG_OFF);
        display_symbol(LCD_UNIT_L1_M, SEG_OFF);
        display_symbol(LCD_UNIT_L1_FT, SEG_OFF);
        display_symbol(LCD_SYMB_ARROW_UP, SEG_OFF);
        display_symbol(LCD_SYMB_ARROW_DOWN, SEG_OFF);
    }
}