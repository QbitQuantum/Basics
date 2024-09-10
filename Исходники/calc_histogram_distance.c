static void read_data(FILE * data_input)
{
	char line_buffer[4096], *tmp;
	int line;

	tmp = fgets(line_buffer, 4096, data_input);
	assert(tmp == line_buffer);

	if (sscanf
	    (line_buffer,
	     "%d %d %d %d " "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d "
	     "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &num_data,
	     &num_to_output, &num_words, &max_dist, score_factors + 0,
	     score_factors + 1, score_factors + 2, score_factors + 3,
	     score_factors + 4, score_factors + 5, score_factors + 6,
	     score_factors + 7, score_factors + 8, score_factors + 9,
	     score_factors + 10, score_factors + 11, score_factors + 12,
	     score_factors + 13, score_factors + 14, score_factors + 15,
	     score_factors + 16, score_factors + 17, score_factors + 18,
	     score_factors + 19, score_factors + 20, score_factors + 21,
	     score_factors + 22, score_factors + 23, score_factors + 24,
	     score_factors + 25, score_factors + 26, score_factors + 27,
	     score_factors + 28, score_factors + 29, score_factors + 30,
	     score_factors + 31) != 4 + 32) {
		usage("wrong number of parameters in first line");
	}
	assert(max_dist > 0);
	assert(num_words == 1 || num_words == 3);
	data = malloc(sizeof(__m128i) * num_data * num_words);
	available = malloc(sizeof(char) * num_data);

	to_output = malloc(sizeof(char) * num_data);
	memset(to_output, 0, sizeof(char) * num_data);

	counters = malloc(sizeof(counter_t) * num_data * NUM_SCORES);
	memset(counters, 0, sizeof(counter_t) * num_data * NUM_SCORES);

	assert(num_to_output <= num_data);
	assert(max_dist <= NUM_SCORES);
	for (int i = 0; i < NUM_SCORES; i++) {
		assert(score_factors[i] > 0);
		if (i > max_dist) {
			score_factors[i] = 0;
		} else {
			assert(score_factors[i] > 0);
		}
	}
	if (num_words == 1) {
		diff_percent = diff_percent_gray;
	} else {
		diff_percent = diff_percent_rgb;
	}

	for (line = 0; line < num_data; line++) {
		tmp = fgets(line_buffer, 4096, data_input);
		assert(tmp == line_buffer);
		if (strncmp(line_buffer, "na", 2) == 0) {
			available[line] = 0;
			if (num_words == 1)
				data[line] = _mm_set_epi64x(line, line);
			else {
				data[3 * line] = _mm_set_epi64x(line, line);
				data[3 * line + 1] = _mm_set_epi64x(line, line);
				data[3 * line + 2] = _mm_set_epi64x(line, line);
			}
		} else {
			available[line] = 1;
//                      printf("len=%ld s='%s'\n", strlen(line_buffer), line_buffer);
			if (num_words == 1) {
				assert(strlen(line_buffer) == 32 + 1);
				// remove newline
				line_buffer[strlen(line_buffer) - 1] = '\0';
				__m128i val = simple_strtoul(line_buffer);
				data[line] = val;
			} else {
				assert(strlen(line_buffer) ==
				       num_words * (32 + 1) - 1 + 1);
				// remove newline
				line_buffer[strlen(line_buffer) - 1] = '\0';
				assert(line_buffer[32] == ' ');
				assert(line_buffer[64 + 1] == ' ');
				__m128i val1 = simple_strtoul(line_buffer);
				__m128i val2 =
				    simple_strtoul(line_buffer + 32 + 1);
				__m128i val3 =
				    simple_strtoul(line_buffer + 64 + 2);
				data[3 * line] = val1;
				data[3 * line + 1] = val2;
				data[3 * line + 2] = val3;
			}
		}
//      printf("line=%d = '%s' = %lx avail=%d\n", line, line_buffer, (*data)[line], (*available)[line]);
	}
}