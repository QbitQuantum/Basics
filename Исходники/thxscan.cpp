int thxscan(FILE *fp, label_ent *label_tab, char file_name[10])
{
	char *o_ptr;
	char out_str[255];
	//char fname[256];
	char out_num[8];
	size_t i, IIPlen, ret_code;
	char upstream_name[255];	
	char upstream_port_name[255];
	int upstream_elem_no;
	char procname[255];	


	proc_ent *proc_curr;
	//	proc_ent *proc_new;
	//	proc_ent *proc_find;
	cnxt_ent *cnxt_tab;
	cnxt_ent *cnxt_curr;
	cnxt_ent *cnxt_new;
	cnxt_ent *cnxt_hold;

//	label_ent *label_new;

	//int label_ct;
	bool eq_arrow;
	IIP *IIP_ptr;

	char buffer[100];

	while (true) {
		if (NULL == fgets(buffer, 100, fp))
			goto finish;
		if (0 == strcmp(buffer, "INPORT") || 0 == strcmp(buffer, "OUTPORT"))
			continue;

		ret_code = 0;

		curr_char = getc(fp);
		proc_tab = 0;
		cnxt_tab = 0;
		label_curr = label_tab;

		strcpy_s(label_curr->label, " ");
		strcpy_s(label_curr->file, file_name);
		label_curr->ent_type = 'L';

		IIPlen = -1;
		out_num[0] = '\0';
		cnxt_hold = 0;

		scan_blanks(fp);

	netloop:
		TCO(X0, '\'');
		goto Xs;       // quote found - scan off rest of IIP
	X0:
		if (scan_sym(fp, out_str) != 0) {  // this could be a network label or a process name...
			printf("Name error\n");
			ret_code = 4;
			goto exit;
		}

		TCO(X2, ':');
		strcpy_s(label_curr->label, out_str);  // it was a label		  
		printf("Scanning Network: %s\n", out_str);
		scan_blanks(fp);

	bigloop:

		cnxt_hold = 0;
		IIPlen = -1;
		TCO(X1, '\'');
	Xs:
		o_ptr = out_str;
		goto get_rest_of_IIP;

	X1:
		if (scan_sym(fp, out_str) != 0) {  // this must be a process name...
			printf("Name error\n");
			ret_code = 4;
			goto exit;
		}
	X2:
		strcpy_s(procname, out_str);
		printf("Procname: %s\n", procname);
		if (cnxt_hold != 0) {
			strcpy_s(cnxt_hold->downstream_name, procname);
			cnxt_hold = 0;
		}

		proc_curr = find_or_build_proc(procname);

		if (4 == scan_blanks(fp))
			goto bigloop;

		goto X3;

	get_rest_of_IIP:
		TCO(tbsl, EOF);
		printf("EOF encountered within quoted string\n");
		ret_code = 4;
		goto exit;
	tbsl:
		TCO(tbq, '\\');
		CC;
		goto get_rest_of_IIP;
	tbq:
		TCO(copy, '\'');
		goto NQ2;
	copy:
		CC;
		goto get_rest_of_IIP;
	NQ2:
		*o_ptr = '\0';
		IIPlen = static_cast<int>(o_ptr - out_str);
		IIP_ptr = (IIP *)malloc(IIPlen + 1);
		memcpy(IIP_ptr->datapart, out_str, IIPlen);
		IIP_ptr->datapart[IIPlen] = '\0';
		printf("IIP: %s\n", IIP_ptr->datapart);
		scan_blanks(fp);
		//IIPlen = -1;
		goto tArrow;


		// scan off process name with optional component name

	X3:
		TCO(NB1, '(');
		scan_blanks(fp);
		TCO(rest_of_comp, ')');
		goto NN2;
	rest_of_comp:

		TCO(NQ6, '"');           // this says that comp name may be surrounded by double quotes (not included in comp_name)
	NQ6:
		o_ptr = comp_name;      // if no data between brackets, comp_name will not be modified...

	TB1:
		TCO(NQ7, '"');
		scan_blanks(fp);

	NQ7:
		TCO(NB2, ')');
		goto NN2;
	NB2:
		CC;
		goto TB1;

	NN2:
		*o_ptr = '\0';

		if (strlen(comp_name) > 0) {
			strcpy_s(proc_curr->comp_name, comp_name);
			printf("Comp name: %s\n", comp_name);
		}

	NB1:
		// comp scanned off, if any
		strcpy_s(upstream_name, procname);	    // in case this proc is the upstream of another arrow

		if (4 == scan_blanks(fp))
			goto bigloop;

		TCO(NQ1, '?');
		proc_curr->trace = 1;
		if (4 == scan_blanks(fp))
			goto bigloop;
	NQ1:

		TCO(tsc, EOF);
		eof_found = TRUE;
		goto nxtnet;

	tsc:
		TCO(tcom, ';');
		scan_blanks(fp);
	nxtnet:
		// this is a fudge because multiple nets are not currently supported 
		IIPlen = -1;

		TCO(nextnet, EOF);
		goto exit;

	tcom:

		IIPlen = -1;
		TCO(not_com, ',');

		scan_blanks(fp);
		goto bigloop;

	not_com:

		o_ptr = out_str;
		TC(outport, '*');     /* automatic port */
		*o_ptr = '\0';

		goto GUy;

	outport:
		if (scan_sym(fp, out_str) != 0) {
			printf("Name error\n");
			ret_code = 4;
			goto exit;
		}
	GUy:
		scan_blanks(fp);

		strcpy_s(upstream_port_name, out_str);
		printf("Upstream port: %s\n", out_str);
		upstream_elem_no = 0;
		TCO(tArrow, '[');
		o_ptr = out_num;
	GNx:
		TN(NNx);
		goto GNx;
	NNx:
		TCO(elemerr, ']');
		*o_ptr = '\0';
		upstream_elem_no = atoi(out_num);

	tArrow:
		scan_blanks(fp);
		eq_arrow = FALSE;
		TCO(tEq, '-');
		goto tGr;
	tEq:
		TCO(nArrow, '=');
		eq_arrow = TRUE;
	tGr:
		TCO(nArrow, '>');
		printf("Arrow\n");
		cnxt_new = (cnxt_ent *)malloc(sizeof(cnxt_ent));
		cnxt_new->succ = 0;
		cnxt_new->dropOldest = false;
		if (cnxt_tab == 0) {
			cnxt_tab = cnxt_new;
			label_curr->cnxt_ptr = cnxt_tab;
			cnxt_curr = cnxt_tab;
		}
		else {
			cnxt_curr->succ = cnxt_new;
			cnxt_curr = cnxt_new;
		}

		cnxt_hold = cnxt_new;
		if (IIPlen != -1) {
			strcpy_s(cnxt_hold->upstream_name, "!");
			cnxt_hold->upstream_port_name[0] = '\0';
			cnxt_hold->gen.IIPptr = IIP_ptr;
		}
		else {
			strcpy_s(cnxt_hold->upstream_name, upstream_name);
			strcpy_s(cnxt_hold->upstream_port_name, upstream_port_name);

			cnxt_hold->upstream_elem_no = upstream_elem_no;
		}
		cnxt_hold->capacity = -1;
		scan_blanks(fp);
		TCO(ncap, '(');
		o_ptr = out_num;
	GNz:
		TN(NNz);
		goto GNz;
	NNz:
		TCO(caperr, ')');
		*o_ptr = '\0';
		cnxt_hold->capacity = atoi(out_num);
		scan_blanks(fp);
		goto ncap;
	caperr:
		printf("Capacity error\n");
		ret_code = 4;
		goto exit;
	ncap:
		cnxt_hold->downstream_elem_no = 0;

		/* Scan off downstream port name */
		o_ptr = out_str;
		TC(Y2a, '*');       /* automatic port */
		*o_ptr = '\0';
		strcpy_s(cnxt_hold->downstream_port_name, out_str);  /* ext. conn */
		goto is_outport;
	Y2a:
		if (scan_sym(fp, out_str) != 0) {
			printf("Downstream port name error for %s %s\n",
				cnxt_hold->upstream_name,
				cnxt_hold->upstream_port_name);
			ret_code = 4;
			goto exit;
		}
		strcpy_s(cnxt_hold->downstream_port_name, out_str);

	is_outport:

		printf("Downstream port: %s\n", cnxt_hold->downstream_port_name);

		scan_blanks(fp);
		TCO(X1, '[');
		o_ptr = out_num;
	GNy:
		TN(NNy);
		goto GNy;
	NNy:
		TCO(elemerr, ']');
		*o_ptr = '\0';
		cnxt_hold->downstream_elem_no = atoi(out_num);
		//cnxt_hold = 0;
		scan_blanks(fp);
		goto X1;

	nextnet:
		scan_blanks(fp);

		if (eof_found) {
			label_curr->succ = 0;   // temporary fix as we are only generating one network for now
			goto exit;
		}

		goto netloop;


	elemerr:
		printf("Port element error\n");
		ret_code = 4;
		goto exit;

	nArrow:
		printf("No arrow found\n");
		ret_code = 4;
	exit:
		printf("\nSummary:\n");
		proc_curr = proc_tab;
		while (proc_curr != 0) {
			printf(" Process: %s (%s)\n", proc_curr->proc_name,
				proc_curr->comp_name);
			proc_curr = proc_curr->succ;
		}

		cnxt_hold = cnxt_tab;
		while (cnxt_hold != 0) {
			char up[200];
			char down[200];
			char elem[20];
			if (cnxt_hold->upstream_name[0] != '!') {
				strcpy_s(up, cnxt_hold->upstream_port_name);
				if (up[0] != '*') {
					strcat_s(up, "[");
					_itoa_s(cnxt_hold->upstream_elem_no, elem, 10);
					strcat_s(up, elem);
					strcat_s(up, "]");
				}
				strcpy_s(down, cnxt_hold->downstream_port_name);
				if (down[0] != '*') {
					strcat_s(down, "[");
					_itoa_s(cnxt_hold->downstream_elem_no, elem, 10);
					strcat_s(down, elem);
					strcat_s(down, "]");
				}
				printf(" Connection: %s %s -> %s %s\n",
					cnxt_hold->upstream_name,
					up,
					down,
					cnxt_hold->downstream_name);
			}
			else {
				strcpy_s(down, cnxt_hold->downstream_port_name);
				if (down[0] != '*') {
					strcat_s(down, "[");
					_itoa_s(cnxt_hold->downstream_elem_no, elem, 10);
					strcat_s(down, elem);
					strcat_s(down, "]");
				}
				printf(" IIP: -> %s %s\n",
					down,
					cnxt_hold->downstream_name);
				IIP_ptr = cnxt_hold->gen.IIPptr;
				printf("    \'");
				auto j = strlen(IIP_ptr->datapart);
				for (i = 0; i < j; i++)
					printf("%c", IIP_ptr->datapart[i]);
				printf("\'\n");
			}
			cnxt_hold = cnxt_hold->succ;
		}
	 
	}
	finish:
	if (fclose(fp) != 0) {
		printf("Close error\n");
		if (ret_code == 0)
			ret_code = 2;
	}
	if (ret_code > 0) {
		// printf("Scan error\n");
		return(ret_code);
	}
	
	// printf("Scan finished\n");
	return (ret_code);
}