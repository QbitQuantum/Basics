/* Shutdown TSRM (call once for the entire process) */
TSRM_API void tsrm_shutdown(void)
{
	int i;

	if (tsrm_tls_table) {
		for (i=0; i<tsrm_tls_table_size; i++) {
			tsrm_tls_entry *p = tsrm_tls_table[i], *next_p;

			while (p) {
				int j;

				next_p = p->next;
				for (j=0; j<p->count; j++) {
					if (p->storage[j]) {
						if (resource_types_table && !resource_types_table[j].done && resource_types_table[j].dtor) {
							resource_types_table[j].dtor(p->storage[j], &p->storage);
						}
						free(p->storage[j]);
					}
				}
				free(p->storage);
				free(p);
				p = next_p;
			}
		}
		free(tsrm_tls_table);
		tsrm_tls_table = NULL;
	}
	if (resource_types_table) {
		free(resource_types_table);
		resource_types_table=NULL;
	}
	tsrm_mutex_free(tsmm_mutex);
	tsmm_mutex = NULL;
	TSRM_ERROR((TSRM_ERROR_LEVEL_CORE, "Shutdown TSRM"));
	if (tsrm_error_file!=stderr) {
		fclose(tsrm_error_file);
	}
#if defined(GNUPTH)
	pth_kill();
#elif defined(PTHREADS)
	pthread_setspecific(tls_key, 0);
	pthread_key_delete(tls_key);
#elif defined(TSRM_WIN32)
	TlsFree(tls_key);
#endif
}