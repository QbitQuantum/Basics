void init_global_addl_config_hook(void)
{
    LOGB("booting\n");
    
    cfg_load();

//#ifdef CONFIG_MENU
    md380_create_main_meny_entry();
//#endif    
}