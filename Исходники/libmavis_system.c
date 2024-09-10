static int mavis_parse_in(mavis_ctx * mcx, struct sym *sym)
{
    while (1) {
	switch (sym->code) {
	case S_script:
	    mavis_script_parse(mcx, sym);
	    continue;
	case S_chroot:
	    sym_get(sym);
	    parse(sym, S_equal);
	    mcx->ftp_chroot = parse_bool(sym);
	    continue;
	case S_passwd:
	    sym_get(sym);
	    parse(sym, S_file);
	    parse(sym, S_equal);
	    strset(&mcx->passwordfile, sym->buf);
	    sym_get(sym);
	    continue;
	case S_ftpusers:
	    sym_get(sym);
	    parse(sym, S_file);
	    parse(sym, S_equal);
	    strset(&mcx->ftpuserspath, sym->buf);
	    sym_get(sym);
	    continue;
	case S_shells:
	    sym_get(sym);
	    parse(sym, S_file);
	    parse(sym, S_equal);
	    strset(&mcx->shellpath, sym->buf);
	    sym_get(sym);
	    continue;
	case S_sslusers:
	    sym_get(sym);
	    parse(sym, S_file);
	    parse(sym, S_equal);
	    strset(&mcx->ssluserspath, sym->buf);
	    sym_get(sym);
	    continue;
	case S_check:
	    sym_get(sym);
	    switch (sym->code) {
	    case S_ftpusers:
		sym_get(sym);
		parse(sym, S_equal);
		mcx->honour_ftpusers = parse_bool(sym);
		break;
	    case S_shells:
		sym_get(sym);
		parse(sym, S_equal);
		mcx->require_valid_shell = parse_bool(sym);
		break;
	    case S_sslusers:
		sym_get(sym);
		parse(sym, S_equal);
		mcx->lookup_sslusers = parse_bool(sym);
		break;
	    default:
		parse_error_expect(sym, S_ftpusers, S_shells, S_sslusers, S_unknown);
	    }
	    continue;
	case S_eof:
	case S_closebra:
	    return MAVIS_CONF_OK;
	default:
	    parse_error_expect(sym, S_script, S_userid, S_groupid, S_path, S_mode, S_closebra, S_unknown);
	}
    }
}