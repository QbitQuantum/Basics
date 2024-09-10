static zend_object *spoofchecker_clone_obj(zval *object) /* {{{ */
{
	zend_object *new_obj_val;
	Spoofchecker_object *sfo, *new_sfo;

    sfo = Z_INTL_SPOOFCHECKER_P(object);
    intl_error_reset(SPOOFCHECKER_ERROR_P(sfo));

	new_obj_val = Spoofchecker_ce_ptr->create_object(Z_OBJCE_P(object));
	new_sfo = php_intl_spoofchecker_fetch_object(new_obj_val);
	/* clone standard parts */
	zend_objects_clone_members(&new_sfo->zo, &sfo->zo);
	/* clone internal object */
	new_sfo->uspoof = uspoof_clone(sfo->uspoof, SPOOFCHECKER_ERROR_CODE_P(new_sfo));
	if(U_FAILURE(SPOOFCHECKER_ERROR_CODE(new_sfo))) {
		/* set up error in case error handler is interested */
		intl_error_set( NULL, SPOOFCHECKER_ERROR_CODE(new_sfo), "Failed to clone SpoofChecker object", 0 );
		Spoofchecker_objects_free(&new_sfo->zo); /* free new object */
		zend_error(E_ERROR, "Failed to clone SpoofChecker object");
	}
	return new_obj_val;
}