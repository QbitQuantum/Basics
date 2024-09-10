int Loop::process(nframes_t nframes) {
  if (playing) {
    current_position += nframes;

    if (loop_length > 0 && current_position >= loop_length) {
      current_position -= loop_length;

      //assert(current_position < loop_length);

      // if (recording) {
      //   num_active_phrases++;
      //   phrases.push_back(Phrase());
      // }

      if (waiting_to_record) {
        recording = true;
        waiting_to_record = false;
        phrases.push_back(Phrase());
      }
    }
  }

  jack_default_audio_sample_t *jack_out =
    static_cast<jack_default_audio_sample_t*>(
      jack_port_get_buffer(output_port, nframes));

  jack_default_audio_sample_t *jack_in =
    static_cast<jack_default_audio_sample_t *>(
      jack_port_get_buffer(input_port, nframes));
  sample_vec in(jack_in, jack_in + nframes);

  if (recording && playing) {
    phrases.back().addAudio(in);
  }

  // combine the existing phrases with the out buffer
  sample_vec phrase_out(nframes);

  for (size_t i = 0; i < num_active_phrases; i++) {
    if (!phrases[i].getAudio(current_position, &phrase_out)) {
      ui << "phrase " << i << " failed\n";
      continue;
    }

    transform(in.begin(), in.end(), phrase_out.begin(),
              in.begin(), plus<sample_t>());
  }

  memcpy(jack_out, in.data(), sizeof(sample_t) * nframes);
  return 0;
}