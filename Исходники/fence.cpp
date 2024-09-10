void test(int mode)
{
	printf("mode:%6s ", mode2str(mode));
	memset(data, 0, sizeof(data));
	double time = 0;
	{
		Xbyak::util::Clock clk;
		clk.begin();
		std::thread t1(write1[mode]);
		std::thread t2(write2[mode]);
		t1.join();
		t2.join();
		clk.end();
		time = (double)clk.getClock();
	}

	int num[4] = { };
	for (int i = 0; i < N; i++) {
		const Data& d = data[i];
		if (d.sa == 0 || d.sb == 0) {
			printf("ERR %d %d\n", d.sa, d.sb);
			exit(1);
		}
		if (d.r1 == 0 && d.r2 == 0) {
			num[0]++;
		} else
		if (d.r1 == 1 && d.r2 == 0) {
			num[1]++;
		} else
		if (d.r1 == 0 && d.r2 == 1) {
			num[2]++;
		} else
		{
			num[3]++;
		}
	}
	int sum = 0;
	printf("num=");
	for (int i = 0; i < 4; i++) {
		printf("%8d ", num[i]);
		sum += num[i];
	}
	if (sum != N) {
		fprintf(stderr, "ERR sum=%d\n", sum);
		exit(1);
	}
	printf("clk=%7.3fMclk\n", time * 1e-6);
}