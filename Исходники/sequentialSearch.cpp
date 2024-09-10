	void analyze(Array arr)
	{
		Timer t;
		cout << "\nANALYSIS \nN\tTIME\n";
		for (int i = 0; i <= 5000; i += 500)
		{
			arr.randomGenerator(i, 5000);
			t.start();
			this->sequentialSearch(arr.a, i, arr.a[i - 1]);
			//key as arr.a[i - 1] ensures worst case
			t.stop();
			cout << i << "\t" << t.time() << endl;
			t.reset();
		}
	}