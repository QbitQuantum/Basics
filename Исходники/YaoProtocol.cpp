static int _main(int argc, char **argv) {
	vector<string> args(argc-1);
	for (int i=1; i<argc; ++i) {
		args[i-1] = argv[i];
	}

	args.at(0);
	//YaoProtocol yao;
	Socket *s;

	ifstream fmtin("/home/louis/sfe/priveq.fmt");
	FmtFile fmt = FmtFile::parseFmt(fmtin);
	cout << "Read fmt file" << endl;
	ifstream in("/home/louis/sfe/priveq.circ");
	Circuit_p cc = Circuit::parseCirc(in);

	if (args[0] == ("A")) {
		args.at(1);
		BigInt n = BigInt::parseString(args[1]);
		bit_vector input_bits = toBits(n, fmt.numInputs(0));

		cout << "connecting" << endl;
		s = new Socket("localhost", 5437);
		DataOutput *out = s->getOutput();
		DataInput *in = s->getInput();
		YaoSender cli;
		cli.setStreams(in, out);
		cli.go(cc, fmt, input_bits);
		delete out;
		delete in;
		delete s;
	} else if (args[0] == ("B")) {
		args.at(1);
		BigInt n = BigInt::parseString(args[1]);
		bit_vector input_bits = toBits(n, fmt.numInputs(1));

		args.at(1);
		YaoChooser srv;

		cout << "listening" << endl;
		ServerSocket *ss = new ServerSocket(5437);
		s = ss->accept();
		DataOutput *out = s->getOutput();
		DataInput *in = s->getInput();
		srv.setStreams(in, out);
		bit_vector circ_out = srv.go(cc, fmt, input_bits);
		for (uint i=0; i<circ_out.size(); ++i) {
			cout << "output " << i << ": " << circ_out[i] << endl;
		}
		delete s;
		delete ss;
		delete out;
		delete in;
	}
	return 0;
}