#include "resourcebundle/resourcebundle_class.h"
#include "resourcebundle/resourcebundle_iterator.h"

/*
 * Although libicu offers iterator functions, they are not used here: libicu does iterate
 * irrespective of array indices. Those cannot be recreated afterwards. Arrays as well as tables
 * can however be accessed by numerical index, with table keys readable ex post.
 */

/* {{{ resourcebundle_iterator_read */
static void resourcebundle_iterator_read( ResourceBundle_iterator *iterator TSRMLS_DC ) 
{
	UErrorCode icuerror = U_ZERO_ERROR;
	ResourceBundle_object *rb = iterator->subject;

	rb->child = ures_getByIndex( rb->me, iterator->i, rb->child, &icuerror );

	if (U_SUCCESS(icuerror)) {
		/* ATTN: key extraction must be the first thing to do... rb->child might be reset in read! */
		if (iterator->is_table) {
			iterator->currentkey = estrdup( ures_getKey( rb->child ) );
		}
		MAKE_STD_ZVAL( iterator->current );
		resourcebundle_extract_value( iterator->current, rb TSRMLS_CC );
	}
	else {
		// zend_throw_exception( spl_ce_OutOfRangeException, "Running past end of ResourceBundle", 0 TSRMLS_CC);
		iterator->current = NULL;
	}
}
/* }}} */