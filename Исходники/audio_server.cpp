void AudioServer::_mix_step() {

	for (int i = 0; i < buses.size(); i++) {
		Bus *bus = buses[i];
		bus->index_cache = i; //might be moved around by editor, so..
		for (int k = 0; k < bus->channels.size(); k++) {

			bus->channels[k].used = false;
		}
	}

	//make callbacks for mixing the audio
	for (Set<CallbackItem>::Element *E = callbacks.front(); E; E = E->next()) {

		E->get().callback(E->get().userdata);
	}

	for (int i = buses.size() - 1; i >= 0; i--) {
		//go bus by bus
		Bus *bus = buses[i];

		for (int k = 0; k < bus->channels.size(); k++) {

			if (bus->channels[k].active && !bus->channels[k].used) {
				//buffer was not used, but it's still active, so it must be cleaned
				AudioFrame *buf = bus->channels[k].buffer.ptr();

				for (uint32_t j = 0; j < buffer_size; j++) {

					buf[j] = AudioFrame(0, 0);
				}
			}
		}

		//process effects
		for (int j = 0; j < bus->effects.size(); j++) {

			if (!bus->effects[j].enabled)
				continue;

			for (int k = 0; k < bus->channels.size(); k++) {

				if (!bus->channels[k].active)
					continue;
				bus->channels[k].effect_instances[j]->process(bus->channels[k].buffer.ptr(), temp_buffer[k].ptr(), buffer_size);
			}

			//swap buffers, so internal buffer always has the right data
			for (int k = 0; k < bus->channels.size(); k++) {

				if (!buses[i]->channels[k].active)
					continue;
				SWAP(bus->channels[k].buffer, temp_buffer[k]);
			}
		}

		//process send

		Bus *send = NULL;

		if (i > 0) {
			//everything has a send save for master bus
			if (!bus_map.has(bus->send)) {
				send = buses[0];
			} else {
				send = bus_map[bus->send];
				if (send->index_cache >= bus->index_cache) { //invalid, send to master
					send = buses[0];
				}
			}
		}

		for (int k = 0; k < bus->channels.size(); k++) {

			if (!bus->channels[k].active)
				continue;

			AudioFrame *buf = bus->channels[k].buffer.ptr();

			AudioFrame peak = AudioFrame(0, 0);
			for (uint32_t j = 0; j < buffer_size; j++) {
				float l = ABS(buf[j].l);
				if (l > peak.l) {
					peak.l = l;
				}
				float r = ABS(buf[j].r);
				if (r > peak.r) {
					peak.r = r;
				}
			}

			bus->channels[k].peak_volume = AudioFrame(Math::linear2db(peak.l + 0.0000000001), Math::linear2db(peak.r + 0.0000000001));

			if (!bus->channels[k].used) {
				//see if any audio is contained, because channel was not used

				if (MAX(peak.r, peak.l) > Math::db2linear(channel_disable_treshold_db)) {
					bus->channels[k].last_mix_with_audio = mix_frames;
				} else if (mix_frames - bus->channels[k].last_mix_with_audio > channel_disable_frames) {
					bus->channels[k].active = false;
					continue; //went inactive, don't mix.
				}
			}

			if (send) {
				//if not master bus, send
				AudioFrame *target_buf = thread_get_channel_mix_buffer(send->index_cache, k);

				for (uint32_t j = 0; j < buffer_size; j++) {
					target_buf[j] += buf[j];
				}
			}
		}
	}

	mix_frames += buffer_size;
	to_mix = buffer_size;
}