static void istream_destructor(php_istream *stm)
{
	if (stm->res) {
		zend_resource *res = stm->res;
		stm->res = NULL;
		zend_list_delete(res);
		return;
	}

	if (stm->refcount > 0) {
		CoDisconnectObject((IUnknown*)stm, 0);
	}

	zend_list_delete(stm->stream->res);

	CoTaskMemFree(stm);
}