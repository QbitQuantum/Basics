void DocumentDecoder::translate() {
	namespace mpi = boost::mpi;

	mpi::request reqs[2];
	reqs[1] = communicator_.irecv(0, TAG_STOP_TRANSLATING);
	NumberedInputDocument input;
	for(;;) {
		reqs[0] = communicator_.irecv(0, TAG_TRANSLATE, input);
		std::pair<mpi::status, mpi::request *> wstat = mpi::wait_any(reqs, reqs + 2);
		if(wstat.first.tag() == TAG_STOP_TRANSLATING) {
			LOG(logger_, debug, "T: Received STOP_TRANSLATING.");
			reqs[0].cancel();
			communicator_.send(0, TAG_STOP_COLLECTING);
			return;
		} else {
			NumberedOutputDocument output;
			LOG(logger_, debug, "T: Received document " << input.first << " for translation.");
			output.first = input.first;
			output.second = runDecoder(input);
			LOG(logger_, debug, "T: Sending translation of document " << input.first << " to collector.");
			communicator_.send(0, TAG_COLLECT, output);
		}
	}
}