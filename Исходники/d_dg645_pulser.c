MX_EXPORT mx_status_type
mxd_dg645_pulser_open( MX_RECORD *record )
{
	static const char fname[] = "mxd_dg645_pulser_open()";

	MX_PULSE_GENERATOR *pulser;
	MX_DG645_PULSER *dg645_pulser = NULL;
	MX_DG645 *dg645 = NULL;
	size_t i, length;
	int c;
	char *output_name;
	mx_status_type mx_status;

	if ( record == (MX_RECORD *) NULL ) {
		return mx_error( MXE_NULL_ARGUMENT, fname,
		"The MX_RECORD pointer passed was NULL." );
	}

	pulser = (MX_PULSE_GENERATOR *) record->record_class_struct;

	mx_status = mxd_dg645_pulser_get_pointers( pulser,
					&dg645_pulser, &dg645, fname );

	if ( mx_status.code != MXE_SUCCESS )
		return mx_status;

	output_name = dg645_pulser->output_name;

	length = strlen( output_name );

	if ( length != 2 ) {
		return mx_error( MXE_ILLEGAL_ARGUMENT, fname,
		"Invalid output name '%s'.  "
		"Output names for '%s' should be 2 characters long.",
			output_name, record->name );
	}

	/* Force the output_name field to upper case. */

	for ( i = 0; i < length; i++ ) {
		c = output_name[i];

		if ( islower(c) ) {
			output_name[i] = toupper(c);
		}
	}

	/* Figure out the output number for this channel as used by
	 * delay and output commands.
	 */

	if ( strcmp( "T0", output_name ) == 0 ) {
		dg645_pulser->output_number = 0;
	} else
	if ( strcmp( "AB", output_name ) == 0 ) {
		dg645_pulser->output_number = 1;
	} else
	if ( strcmp( "CD", output_name ) == 0 ) {
		dg645_pulser->output_number = 2;
	} else
	if ( strcmp( "EF", output_name ) == 0 ) {
		dg645_pulser->output_number = 3;
	} else
	if ( strcmp( "GH", output_name ) == 0 ) {
		dg645_pulser->output_number = 4;
	} else {
		return mx_error( MXE_ILLEGAL_ARGUMENT, fname,
		"Illegal output name '%s' requested for pulser '%s'.  "
		"The allowed names are 'T0', 'AB', 'CD', 'EF', and 'GH'.",
			output_name, record->name );
	}

	/* Call setup() to put the pulser into the state configured in
	 * the MX configuration file.
	 */

	mx_status = mx_pulse_generator_setup( record,
					pulser->pulse_period,
					pulser->pulse_width,
					pulser->num_pulses,
					pulser->pulse_delay,
					pulser->function_mode,
					pulser->trigger_mode );

	return mx_status;
}