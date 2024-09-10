/************************************************************************
 *									*
 * mmap_validate_opts() - Validate Memory Mapped Test Options.		*
 *									*
 * Description:								*
 *	This function verifies the options specified for memory mapped	*
 * file testing are valid.						*
 *									*
 * Inputs:	dip = The device information pointer.			*
 *									*
 * Return Value:							*
 *		Returns SUCESS / FAILURE = Valid / Invalid Options.	*
 *									*
 ************************************************************************/
int
mmap_validate_opts (struct dinfo *dip)
{
    int status = SUCCESS;

    /*
     * For memory mapped I/O, ensure the user specified a limit, and
     * that the block size is a multiple of the page size (a MUST!).
     */
    if (mmap_flag) {
	if (data_limit == INFINITY) {
	    Fprintf ("You must specify a data limit for memory mapped I/O.\n");
	    status = FAILURE;
	} else if (block_size % page_size) {
	    Fprintf (
	"Please specify a block size modulo of the page size (%d).\n", page_size);
	    status = FAILURE;
	} else if (aio_flag) {
	    Fprintf ("Cannot enable async I/O with memory mapped I/O.\n");
	    status = FAILURE;
	} else {
	    status = validate_opts (dip);
	}
    }
    return (status);
}