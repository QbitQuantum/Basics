/**
 * Gets an attribute a message using the array syntax
 *
 *<code>
 * print_r(
 *     $messages[0]
 * );
 *</code>
 *
 * @param int index
 * @return \Phalcon\Validation\Message
 */
PHP_METHOD(Phalcon_Validation_Message_Group, offsetGet) {

	zval *index_param = NULL, *message = NULL, *_0;
	zend_long index;

	zephir_fetch_params(0, 1, 0, &index_param);

	if (UNEXPECTED(Z_TYPE_P(index_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'index' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	index = Z_LVAL_P(index_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_messages"), PH_NOISY_CC);
	if (zephir_array_isset_long_fetch(&message, _0, index, 1 TSRMLS_CC)) {
		RETURN_CTORW(message);
	}
	RETURN_BOOL(0);

}