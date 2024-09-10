ZEND_API ZEND_COLD void _zend_bailout(char *filename, uint lineno) /* {{{ */
{

	if (!EG(bailout)) {
		zend_output_debug_string(1, "%s(%d) : Bailed out without a bailout address!", filename, lineno);
		exit(-1);
	}
	CG(unclean_shutdown) = 1;
	CG(active_class_entry) = NULL;
	CG(in_compilation) = 0;
	EG(current_execute_data) = NULL;
	LONGJMP(*EG(bailout), FAILURE);
}