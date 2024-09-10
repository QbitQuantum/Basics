static int dir_ctrl(X509_LOOKUP *ctx, int cmd, const char *argp, long argl,
	     char **retp)
	{
	int ret=0;
	BY_DIR *ld;
	char *dir = NULL;

	ld=(BY_DIR *)ctx->method_data;

	switch (cmd)
		{
	case X509_L_ADD_DIR:
		if (argl == X509_FILETYPE_DEFAULT)
			{
			dir=(char *)Getenv(X509_get_default_cert_dir_env());
			if (dir)
				ret=add_cert_dir(ld,dir,X509_FILETYPE_PEM);
			else
				ret=add_cert_dir(ld,X509_get_default_cert_dir(),
					X509_FILETYPE_PEM);
			if (!ret)
				{
				X509err(X509_F_DIR_CTRL,X509_R_LOADING_CERT_DIR);
				}
			}
		else
			ret=add_cert_dir(ld,argp,(int)argl);
		break;
		}
	return(ret);
	}