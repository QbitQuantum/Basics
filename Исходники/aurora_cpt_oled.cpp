void aurora_cpt_oled::init()
{
	oled1.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	oled1.clearDisplay();   // clears the screen and buffer
	oled1.display();
	oled1.setTextSize(1);
	oled1.setTextColor(WHITE);
}