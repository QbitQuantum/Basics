void webjames_php_shutdown(void)
/*called when WebJames is about to quit*/
{
	sapi_module.shutdown(&sapi_module);
	sapi_shutdown();
}