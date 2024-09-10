// blink a specific LED (at x,y) "n" times
void blinkn(uint8_t n)
{
	uint8_t del;
	uint8_t x = 0;
	uint8_t y = 1;
	uint8_t i;

	/* blink LED6 (at 0,1) "n" times */

	del = 25;
	for (i = 0; i < n; i++) {
		setpixel(x, y, 1);	// LED(x,y) on
		mydelay10(del);
		setpixel(x, y, 0);	// LED(x,y) off
		mydelay10(del);
	}
}