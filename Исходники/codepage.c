static BOOL php_win32_cp_cli_io_setup(void)
{/*{{{*/
	BOOL ret = TRUE;

	if (PG(input_encoding) && PG(input_encoding)[0]) {
		cur_in_cp = php_win32_cp_get_by_enc(PG(input_encoding));
		if (!cur_in_cp) {
			cur_in_cp = cur_cp;
		}
	} else {
		cur_in_cp = cur_cp;
	}

	if (PG(output_encoding) && PG(output_encoding)[0]) {
		cur_out_cp = php_win32_cp_get_by_enc(PG(output_encoding));
		if (!cur_out_cp) {
			cur_out_cp = cur_cp;
		}
	} else {
		cur_out_cp = cur_cp;
	}

	if(php_get_module_initialized()) {
		ret = SetConsoleCP(cur_in_cp->id) && SetConsoleOutputCP(cur_out_cp->id);
	}

	return ret;
}/*}}}*/