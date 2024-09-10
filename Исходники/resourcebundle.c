#include "intl_data.h"
#include "resourcebundle/resourcebundle_class.h"

/* {{{ ResourceBundle_extract_value */
void resourcebundle_extract_value( zval *return_value, ResourceBundle_object *source TSRMLS_DC ) 
{
	UResType               restype;
	const UChar*           ufield;
	const uint8_t*         bfield;
	const int32_t*         vfield;
	int32_t                ilen;
	int                    i;
	long                   lfield;
	ResourceBundle_object* newrb;

	restype = ures_getType( source->child );
	switch (restype)
	{
		case URES_STRING:
			ufield = ures_getString( source->child, &ilen, &INTL_DATA_ERROR_CODE(source) );
			INTL_METHOD_CHECK_STATUS(source, "Failed to retrieve string value");
			INTL_METHOD_RETVAL_UTF8(source, (UChar *)ufield, ilen, 0);
			break;

		case URES_BINARY:
			bfield = ures_getBinary( source->child, &ilen, &INTL_DATA_ERROR_CODE(source) );
			INTL_METHOD_CHECK_STATUS(source, "Failed to retrieve binary value");
			ZVAL_STRINGL( return_value, (char *) bfield, ilen );
			break;

		case URES_INT: