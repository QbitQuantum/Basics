void 	Rename(int argc, char *argv[], BBWinNet & bbobj)
{
	bbobj.SetHostName(argv[3]);
	cout << "hostname defined to: " << argv[3] << "\n";
	try {
		if (argc > 5) {
			cout << "Sending test rename ...\n";
			bbobj.Rename(argv[4], argv[5]);
		} else {
			cout << "Sending test rename ...\n";
			bbobj.Rename(argv[4]);
		}
	} catch (BBWinNetException ex) {
		cout << "Error : " << ex.getMessage() << "\n";
	}
}