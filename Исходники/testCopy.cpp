void implFFT(std::string name, InputCopy<double>* i, OutputCopy<double>* o, Parameters<double> conf)
{
	auto input = new FileInput<double>("input_mono.wav", i, conf);
	auto output = new FileOutput<double>(o, conf);

	FFT_p<double> fft_m(new FFTWManager<double>(conf));
	fft_m->setChannels((unsigned int) input->channels());

	auto fft_i = new FFTInputProxy<double>(new RectWindow<double>,
										   input,
										   fft_m,
										   conf);

	auto fft_o = new FFTOutputProxy<double>(output, fft_m, conf);

	BenchmarkManager manager(Input_p(fft_i),
							 Output_p(fft_o),
							 Benchmark_p(new Dummy<double>(conf)));

	manager.execute();
	output->writeFile(("out_test_copy_fft_" + name + ".wav").c_str());
}