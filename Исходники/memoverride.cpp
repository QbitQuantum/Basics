ErrorHandlerRegistrar::ErrorHandlerRegistrar()
{
	_set_purecall_handler( VPureCall );
	_set_invalid_parameter_handler( VInvalidParameterHandler );
}