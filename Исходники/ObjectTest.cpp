	void SetUp(){
		donut = Handler<Donut>(new Donut(log_trace));
		donut->bootstrap();
		clock = donut->clock();
		heap = donut->heap();
	}