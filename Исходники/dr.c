static int
cmd_dr_run( chain_t *chain, char *params[] )
{
	int dir = 1;
	tap_register *r;

	if (cmd_params( params ) < 1 || cmd_params( params ) > 2)
		return -1;

	if (!cmd_test_cable( chain ))
		return 1;

	if (!chain->parts) {
		printf( _("Run \"detect\" first.\n") );
		return 1;
	}

	if (chain->active_part >= chain->parts->len) {
		printf( _("%s: no active part\n"), "dr" );
		return 1;
	}

	if (chain->parts->parts[chain->active_part]->active_instruction == NULL) {
		printf( _("%s: part without active instruction\n"), "dr" );
		return 1;
	}
	if (chain->parts->parts[chain->active_part]->active_instruction->data_register == NULL) {
		printf( _("%s: part without active data register\n"), "dr" );
		return 1;
	}

	if (params[1]) {
		if (strcasecmp( params[1], "in" ) == 0)
			dir = 0;
		else if (strcasecmp( params[1], "out" ) == 0)
			dir = 1;
		else {
			unsigned int bit;
			if (strspn(params[1], "01") != strlen(params[1])) {
				return -1;
			}
			
			r = chain->parts->parts[chain->active_part]->active_instruction->data_register->in;
			if (r->len != strlen(params[1])) {
				printf( _("%s: register length mismatch\n"), "dr" );
				return 1;
			}
			for (bit = 0; params[1][bit]; bit++) {
				r->data[r->len - 1 - bit] = (params[1][bit] == '1');
			}
			
			dir = 0;
		}
	}

	if (dir)
		r = chain->parts->parts[chain->active_part]->active_instruction->data_register->out;
	else
		r = chain->parts->parts[chain->active_part]->active_instruction->data_register->in;
	printf( _("%s\n"), register_get_string( r ) );

	return 1;
}