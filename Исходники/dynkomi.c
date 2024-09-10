struct uct_dynkomi *
uct_dynkomi_init_adaptive(struct uct *u, char *arg, struct board *b)
{
	struct uct_dynkomi *d = calloc2(1, sizeof(*d));
	d->uct = u;
	d->permove = adaptive_permove;
	d->persim = adaptive_persim;
	d->done = generic_done;

	struct dynkomi_adaptive *a = calloc2(1, sizeof(*a));
	d->data = a;

	a->lead_moves = board_large(b) ? 20 : 4; // XXX
	a->max_losing_komi = 30;
	a->losing_komi_stop = 1.0f;
	a->no_komi_at_game_end = true;
	a->indicator = komi_by_value;

	a->adapter = adapter_sigmoid;
	a->adapt_rate = -18;
	a->adapt_phase = 0.65;
	a->adapt_moves = 200;
	a->adapt_dir = -0.5;

	a->zone_red = 0.45;
	a->zone_green = 0.50;
	a->score_step = 1;
	a->use_komi_ratchet = true;
	a->komi_ratchet_maxage = 0;
	a->komi_ratchet = 1000;

	if (arg) {
		char *optspec, *next = arg;
		while (*next) {
			optspec = next;
			next += strcspn(next, ":");
			if (*next) { *next++ = 0; } else { *next = 0; }

			char *optname = optspec;
			char *optval = strchr(optspec, '=');
			if (optval) *optval++ = 0;

			if (!strcasecmp(optname, "lead_moves") && optval) {
				/* Do not adjust komi adaptively for first
				 * N moves. */
				a->lead_moves = atoi(optval);
			} else if (!strcasecmp(optname, "max_losing_komi") && optval) {
				a->max_losing_komi = atof(optval);
			} else if (!strcasecmp(optname, "losing_komi_stop") && optval) {
				a->losing_komi_stop = atof(optval);
			} else if (!strcasecmp(optname, "no_komi_at_game_end")) {
				a->no_komi_at_game_end = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "indicator")) {
				/* Adaptatation indicator - how to decide
				 * the adaptation rate and direction. */
				if (!strcasecmp(optval, "value")) {
					/* Winrate w/ komi so far. */
					a->indicator = komi_by_value;
				} else if (!strcasecmp(optval, "score")) {
					/* Expected score w/ current komi. */
					a->indicator = komi_by_score;
				} else {
					fprintf(stderr, "UCT: Invalid indicator %s\n", optval);
					exit(1);
				}

				/* value indicator settings */
			} else if (!strcasecmp(optname, "zone_red") && optval) {
				a->zone_red = atof(optval);
			} else if (!strcasecmp(optname, "zone_green") && optval) {
				a->zone_green = atof(optval);
			} else if (!strcasecmp(optname, "score_step") && optval) {
				a->score_step = atoi(optval);
			} else if (!strcasecmp(optname, "score_step_byavg") && optval) {
				a->score_step_byavg = atof(optval);
			} else if (!strcasecmp(optname, "use_komi_ratchet")) {
				a->use_komi_ratchet = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "losing_komi_ratchet")) {
				a->losing_komi_ratchet = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "komi_ratchet_age") && optval) {
				a->komi_ratchet_maxage = atoi(optval);

				/* score indicator settings */
			} else if (!strcasecmp(optname, "adapter") && optval) {
				/* Adaptatation method. */
				if (!strcasecmp(optval, "sigmoid")) {
					a->adapter = adapter_sigmoid;
				} else if (!strcasecmp(optval, "linear")) {
					a->adapter = adapter_linear;
				} else {
					fprintf(stderr, "UCT: Invalid adapter %s\n", optval);
					exit(1);
				}
			} else if (!strcasecmp(optname, "adapt_base") && optval) {
				/* Adaptation base rate; see above. */
				a->adapt_base = atof(optval);
			} else if (!strcasecmp(optname, "adapt_rate") && optval) {
				/* Adaptation slope; see above. */
				a->adapt_rate = atof(optval);
			} else if (!strcasecmp(optname, "adapt_phase") && optval) {
				/* Adaptation phase shift; see above. */
				a->adapt_phase = atof(optval);
			} else if (!strcasecmp(optname, "adapt_moves") && optval) {
				/* Adaptation move amount; see above. */
				a->adapt_moves = atoi(optval);
			} else if (!strcasecmp(optname, "adapt_aport")) {
				a->adapt_aport = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "adapt_dir") && optval) {
				/* Adaptation direction vector; see above. */
				a->adapt_dir = atof(optval);

			} else {
				fprintf(stderr, "uct: Invalid dynkomi argument %s or missing value\n", optname);
				exit(1);
			}
		}
	}

	return d;
}