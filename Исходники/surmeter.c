static void
sur_run(LV2_Handle instance, uint32_t n_samples)
{
	LV2meter* self = (LV2meter*)instance;
	uint32_t cors = self->chn > 3 ? 4 : 3;

	for (uint32_t c = 0; c < cors; ++c) {
		uint32_t in_a = rintf (*self->surc_a[c]);
		uint32_t in_b = rintf (*self->surc_b[c]);
		if (in_a >= self->chn) in_a = self->chn - 1;
		if (in_b >= self->chn) in_b = self->chn - 1;
		self->cor4[c]->process (self->input[in_a], self->input[in_b], n_samples);
		*self->surc_c[c] = self->cor4[c]->read();
	}

	for (uint32_t c = 0; c < self->chn; ++c) {
		float m, p;

		float* const input  = self->input[c];
		float* const output = self->output[c];

		self->mtr[c]->process(input, n_samples);

		static_cast<Kmeterdsp*>(self->mtr[c])->read(m, p);

		*self->level[c] = m;
		*self->peak[c]  = p;

		if (input != output) {
			memcpy(output, input, sizeof(float) * n_samples);
		}
	}
}