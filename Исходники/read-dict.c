/**
 * Returns TRUE if this token is a special token and it is equal to c
 */
static int is_equal(Dictionary dict, wint_t c)
{
	return (dict->is_special &&
	        wctob(c) == dict->token[0] &&
	        dict->token[1] == '\0');
}