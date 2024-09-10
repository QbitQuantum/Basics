void    pcf_read_parameters(void)
{
    char   *path;

    /*
     * A direct rip-off of mail_conf_read(). XXX Avoid code duplication by
     * better code decomposition.
     */
    pcf_set_config_dir();
    path = concatenate(var_config_dir, "/", MAIN_CONF_FILE, (char *) 0);
    if (dict_load_file_xt(CONFIG_DICT, path) == 0)
	msg_fatal("open %s: %m", path);
    myfree(path);
}