void handle_line(char *line)
{
	float freq = 0.0;
	int octave = -1;
	char *check = NULL;
	check = get_arg_to("#reset",line);
	if (check)
	{
		step_prog = 0;
		free(check);
		return;
	}

	check = get_arg_to("#step ",line);
	if (check)
	{
		step_size = (float)strtof(check,0);
		free(check);
		return;
	}

	check = get_arg_to("#amp ",line);
	if (check)
	{
		amp = (float)strtof(check,0);
		free(check);
		return;
	}

	check = get_arg_to("#duty ",line);
	if (check)
	{
		duty = (float)strtof(check,0);
		free(check);
		return;
	}

	check = get_arg_to("#wave ",line);
	if (check)
	{
		wave_sel = (int)strtoul(check,NULL,0);
		free(check);
		return;
	}

	check = get_arg_to("#decay ",line);
	if (check)
	{
		decay_len = (float)strtof(check,0);
		free(check);
		return;
	}

	check = get_arg_to("#len ",line);
	if (check)
	{
		note_len = (float)strtof(check,0);
		free(check);
		return;
	}

	check = get_arg_to("#overclock ",line);
	if (check)
	{
		overclock = (float)strtof(check,0);
		free(check);
		return;
	}

	check = get_arg_to("#tmod ",line);
	if (check)
	{
		tmod_cnt++;
		tmod = (float)strtof(check,0);
		printf("\tfloat t%d = mod(t0,%f);\n",tmod_cnt,tmod);
		free(check);
		return;	
	}

	check = get_arg_to("#tune ",line);
	if (check)
	{
		tune = (float)strtof(check,0);
		free(check);
		return;
	}

	check = get_arg_to("#left ",line);
	if (check)
	{
		left_a = (float)strtof(check,0);	
		free(check);
		return;
	}

	check = get_arg_to("#right ",line);
	if (check)
	{
		right_a = (float)strtof(check,0);	
		free(check);
		return;
	}

	check = get_arg_to("#main",line);
	if (check)
	{	
		printf("vec2 mainSound(float t0)\n{\n");
		printf("\tt0 = t0 * %f;\n",overclock);
		printf("\tvec2 result = vec2(0.0,0.0);\n");
		free(check);
		return;
	}

	check = get_arg_to("#endmain",line);
	if (check)
	{
		printf("\n\treturn result;\n}\n\n");
		free(check);
		return;
	}

	check = get_arg_to("#func ",line);
	if (check)
	{
		first_if = 1;
		tmod_cnt = 0;
		printf("float %s(float t%d)\n{\n\tfloat result = 0.0;\n",check,tmod_cnt);
		free(check);
		return;
	}

	check = get_arg_to("#endfunc",line);
	if (check)
	{
		printf("\n\treturn result;\n}\n\n");
		free(check);
		return;
	}

	check = get_arg_to("#call ",line);
	if (check)
	{
		printf("\tresult += vec2(%f,%f) * (%s(t%d));\n",left_a,right_a,check,tmod_cnt);
		free(check);
		return;
	}

// Notes
	check = get_arg_to("C#",line);
	if (check)
	{
		freq = NOTE_CS;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("C",line);
	if (check)
	{
		freq = NOTE_C;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("D#",line);
	if (check)
	{
		freq = NOTE_DS;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("D",line);
	if (check)
	{
		freq = NOTE_D;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("E",line);
	if (check)
	{
		freq = NOTE_E;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("F#",line);
	if (check)
	{
		freq = NOTE_FS;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("F",line);
	if (check)
	{
		freq = NOTE_F;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("G#",line);
	if (check)
	{
		freq = NOTE_GS;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("G",line);
	if (check)
	{
		freq = NOTE_G;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("A#",line);
	if (check)
	{
		freq = NOTE_AS;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("A",line);
	if (check)
	{
		freq = NOTE_A;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("B",line);
	if (check)
	{
		freq = NOTE_B;
		octave = (int)strtoul(check,NULL,0);
		goto handle_line_finished;
	}
	check = get_arg_to("-",line);
	if (check)
	{
		freq = 0;
		octave = -1;
		goto handle_line_finished;
	}

// Unrecognized token, or a comment, etc
	free(check);
	return;

handle_line_finished:
	if (check)
	{
		free(check);
		print_line(freq, octave);
		step_prog += step_size;
	}
	return;
	
}