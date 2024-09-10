void lcd_print(char *str)
{
	int len1 = strlen(str);
	int len2 = 0;
	char line1[17] = "                ";
	char line2[17] = "                ";

	if(len1 > 32)
		len2 = 16;
	else if(len1 > 16)
		len2 = len1 - 16;

	strncpy(line1, str, len1);
	grove_lcd.setCursor(0, 0);
	grove_lcd.print(line1);

	if(len2) {
		strncpy(line2, str+16, len2);
	}
	grove_lcd.setCursor(0, 1);
	grove_lcd.print(line2);
	
}