/* {{{ zend_user_unserialize */
ZEND_API int zend_user_unserialize(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
	zval zdata;

	if (UNEXPECTED(object_init_ex(object, ce) != SUCCESS)) {
		return FAILURE;
	}

	ZVAL_STRINGL(&zdata, (char*)buf, buf_len);

	zend_call_method_with_1_params(object, ce, &ce->unserialize_func, "unserialize", NULL, &zdata);

	zval_ptr_dtor(&zdata);

	if (EG(exception)) {
		return FAILURE;
	} else {
		return SUCCESS;
	}
}