/* :Document-method: is_valid
 * call-seq:
 *      is_valid() --> valid_boolean
 * 
 * Checks if the PC/SC context is still valid.
 * A context may become invalid if the resource manager service has been shut down.
 * Wraps _SCardIsValidContext_ in PC/SC.
 * 
 * Returns a boolean value with the obvious meaning.
 */
static VALUE PCSC_Context_is_valid(VALUE self) {
	struct SCardContextEx *context;	
	Data_Get_Struct(self, struct SCardContextEx, context);
	if(context == NULL) return self;

#if defined(RB_SMARTCARD_OSX_TIGER_HACK) || defined(PCSC_SURROGATE_SCARD_IS_VALID_CONTEXT)	
	return Qtrue;
#else
	context->pcsc_error = SCardIsValidContext(context->pcsc_context);
	return (context->pcsc_error == SCARD_S_SUCCESS) ? Qtrue : Qfalse;
#endif
}