/* pc_resetsrc()
 * "position" may only hold a pointer that was previously obtained from
 * pc_getpossrc()
 */
void pc_resetsrc(void *handle,void *position)
{
	assert(handle!=NULL);
	fsetpos((FILE*)handle,(fpos_t *)position);
}