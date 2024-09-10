/* {{{ IntlDateFormatter_object_clone */
zend_object *IntlDateFormatter_object_clone(zval *object)
{
	IntlDateFormatter_object *dfo, *new_dfo;
	zend_object *new_obj;

	DATE_FORMAT_METHOD_FETCH_OBJECT_NO_CHECK;

	new_obj = IntlDateFormatter_ce_ptr->create_object(Z_OBJCE_P(object));
	new_dfo = php_intl_dateformatter_fetch_object(new_obj);
	/* clone standard parts */
	zend_objects_clone_members(&new_dfo->zo, &dfo->zo);
	/* clone formatter object */
	if (dfo->datef_data.udatf != NULL) {
		DATE_FORMAT_OBJECT(new_dfo) = udat_clone(DATE_FORMAT_OBJECT(dfo),  &INTL_DATA_ERROR_CODE(dfo));
		if (U_FAILURE(INTL_DATA_ERROR_CODE(dfo))) {
			/* set up error in case error handler is interested */
			intl_errors_set(INTL_DATA_ERROR_P(dfo), INTL_DATA_ERROR_CODE(dfo),
					"Failed to clone IntlDateFormatter object", 0 );
			zend_throw_exception(NULL, "Failed to clone IntlDateFormatter object", 0);
		}
	} else {
		zend_throw_exception(NULL, "Cannot clone unconstructed IntlDateFormatter", 0);
	}
	return new_obj;
}