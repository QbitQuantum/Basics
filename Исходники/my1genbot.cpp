//------------------------------------------------------------------------------
int main(void)
{
	my1TestBot cTestBot;
	int count = 0;
	srand(time(0x0));
	// main drive loop
	while(1)
	{
		cTestBot.CaptureView();
		cTestBot.ColorDirect();
		cTestBot.CaptureSens();
		cTestBot.Evaluate();
		if(cTestBot.ZeroDrive()) break;
		cTestBot.MoveDrive();
		count++;
		if(count==MAX_COUNT) break;
	}
	return 0;
}