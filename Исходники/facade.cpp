    void Run() {
	Scanner scanner;
	scanner.Scan();
	Parser parser;
	parser.Parse();
	GenMidCode midcode;
	midcode.GenCode();
	GenMachineCode machneCode;
	machneCode.GenCode();
    }