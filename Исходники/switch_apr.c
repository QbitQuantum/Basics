SWITCH_DECLARE(void) switch_uuid_get(switch_uuid_t *uuid)
{
	switch_mutex_lock(runtime.uuid_mutex);
#ifndef WIN32
	apr_uuid_get((apr_uuid_t *) uuid);
#else
	UuidCreate((UUID *) uuid);
#endif
	switch_mutex_unlock(runtime.uuid_mutex);
}