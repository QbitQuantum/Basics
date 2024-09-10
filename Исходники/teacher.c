void process()
{
	static int n;
	printf("process %d: f1=%f i1=%d sel=%d\n", n, f1, i1, sel);
	fillrect((n*20)%(IMG_W-80), 300, 80, 80, 0xff);
	usleep(1000*300);
	n++;
}