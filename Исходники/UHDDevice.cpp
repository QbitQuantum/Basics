int uhd_device::writeSamples(short *buf, int len, bool *underrun,
			unsigned long long timestamp,bool isControl)
{
	uhd::tx_metadata_t metadata;
	metadata.has_time_spec = true;
	metadata.start_of_burst = false;
	metadata.end_of_burst = false;
	metadata.time_spec = convert_time(timestamp, tx_rate);

	*underrun = false;

	// No control packets
	if (isControl) {
		LOG(ERR) << "Control packets not supported";
		return 0;
	}

	// Drop a fixed number of packets (magic value)
	if (!aligned) {
		drop_cnt++;

		if (drop_cnt == 1) {
			LOG(DEBUG) << "Aligning transmitter: stop burst";
			*underrun = true;
			metadata.end_of_burst = true;
		} else if (drop_cnt < 30) {
			LOG(DEBUG) << "Aligning transmitter: packet advance";
			return len;
		} else {
			LOG(DEBUG) << "Aligning transmitter: start burst";
			metadata.start_of_burst = true;
			aligned = true;
			drop_cnt = 0;
		}
	}

	size_t num_smpls = tx_stream->send(buf, len, metadata);

	if (num_smpls != (unsigned) len) {
		LOG(ALERT) << "UHD: Device send timed out";
		LOG(ALERT) << "UHD: Version " << uhd::get_version_string();
		LOG(ALERT) << "UHD: Unrecoverable error, exiting...";
		exit(-1);
	}

	return num_smpls;
}