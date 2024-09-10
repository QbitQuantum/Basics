void manager_process(const MPI::Intracomm &comm_world, const int manager_rank, const int worker_size, std::string &maskName, std::string &imgDir, std::string &outDir, bool overwrite) {
	// first get the list of files to process
   	std::vector<std::string> filenames;
	std::vector<std::string> seg_output;
	std::vector<std::string> features_output;
	uint64_t t1, t0;

	t0 = cci::common::event::timestampInUS();
	getFiles(maskName, imgDir, outDir, filenames, seg_output, features_output, overwrite);

	t1 = cci::common::event::timestampInUS();
	printf("Manager ready at %d, file read took %lu us\n", manager_rank, t1 - t0);
	comm_world.Barrier();

	// now start the loop to listen for messages
	int curr = 0;
	int total = filenames.size();
	MPI::Status status;
	int worker_id;
	char ready;
	char *input;
	char *mask;
	char *output;
	int inputlen;
	int masklen;
	int outputlen;
	while (curr < total) {
		usleep(1000);

		if (comm_world.Iprobe(MPI_ANY_SOURCE, TAG_CONTROL, status)) {
/* where is it coming from */
			worker_id=status.Get_source();
			comm_world.Recv(&ready, 1, MPI::CHAR, worker_id, TAG_CONTROL);
//			printf("manager received request from worker %d\n",worker_id);
			if (worker_id == manager_rank) continue;

			if(ready == WORKER_READY) {
				// tell worker that manager is ready
				comm_world.Send(&MANAGER_READY, 1, MPI::CHAR, worker_id, TAG_CONTROL);
//				printf("manager signal transfer\n");
/* send real data */
				inputlen = filenames[curr].size() + 1;  // add one to create the zero-terminated string
				masklen = seg_output[curr].size() + 1;
				outputlen = features_output[curr].size() + 1;
				input = new char[inputlen];
				memset(input, 0, sizeof(char) * inputlen);
				strncpy(input, filenames[curr].c_str(), inputlen);
				mask = new char[masklen];
				memset(mask, 0, sizeof(char) * masklen);
				strncpy(mask, seg_output[curr].c_str(), masklen);
				output = new char[outputlen];
				memset(output, 0, sizeof(char) * outputlen);
				strncpy(output, features_output[curr].c_str(), outputlen);

				comm_world.Send(&inputlen, 1, MPI::INT, worker_id, TAG_METADATA);
				comm_world.Send(&masklen, 1, MPI::INT, worker_id, TAG_METADATA);
				comm_world.Send(&outputlen, 1, MPI::INT, worker_id, TAG_METADATA);

				// now send the actual string data
				comm_world.Send(input, inputlen, MPI::CHAR, worker_id, TAG_DATA);
				comm_world.Send(mask, masklen, MPI::CHAR, worker_id, TAG_DATA);
				comm_world.Send(output, outputlen, MPI::CHAR, worker_id, TAG_DATA);
				curr++;

				delete [] input;
				delete [] mask;
				delete [] output;

			}

			if (curr % 100 == 1) {
				printf("[ MANAGER STATUS ] %d tasks remaining.\n", total - curr);
			}

		}
	}
/* tell everyone to quit */
	int active_workers = worker_size;
	while (active_workers > 0) {
		usleep(1000);

		if (comm_world.Iprobe(MPI_ANY_SOURCE, TAG_CONTROL, status)) {
		/* where is it coming from */
			worker_id=status.Get_source();
			comm_world.Recv(&ready, 1, MPI::CHAR, worker_id, TAG_CONTROL);
//			printf("manager received request from worker %d\n",worker_id);
			if (worker_id == manager_rank) continue;

			if(ready == WORKER_READY) {
				comm_world.Send(&MANAGER_FINISHED, 1, MPI::CHAR, worker_id, TAG_CONTROL);
//				printf("manager signal finished\n");
				--active_workers;
			}
		}
	}
}