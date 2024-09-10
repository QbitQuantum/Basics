/**************************************************************************************
 * Function Name: pinPage
 *
 * Description:
 *		Pin the page with the requested pageNum in the BUffer Pool
 *		If the page is not in the Buffer Pool, load it from the file to the Buffer Pool
 *
 * Parameters:
 *		BM_BufferPool * const bm: Buffer Pool Handler
 *		BM_PageHandle * const page: Buffer Page Handler
 *		PageNumber pageNum: the page number of the requested page
 *
 * Return:
 *		RC: return code
 *
 * Author:
 *		Jie Zhou <*****@*****.**>
 *
 * History:
 *		Date        Name								Content
 *		----------  ----------------------------------	----------------------------
 *		2015-03-17  Jie Zhou <*****@*****.**>		Initialization
 *		2015-03-20	Xin Su <*****@*****.**>			Modify the logic of pinning the requested page
 *														Add comments
 **************************************************************************************/
RC pinPage(BM_BufferPool * const bm, BM_PageHandle * const page,
		const PageNumber pageNum) {
	RC rc = -99; // init the return code

	if (bm->strategy == RS_FIFO) {
		rc = FIFO(bm, page, pageNum);

		// Because the searchPage() in the FIFO() returns a different return code (RC_PAGE_FOUND)
		// when it completes without errors from the return code (RC_OK) returned by appendPage() and replacePage(),
		// so it should be reset to RC_OK when searchPage() is executed and returned successfully
		if (rc == RC_PAGE_FOUND) {
			rc = RC_OK;
		}
	} else if (bm->strategy == RS_LRU) {
		rc = LRU(bm, page, pageNum);
	} else if (bm->strategy == RS_CLOCK) {
		rc = CLOCK(bm, page, pageNum);
	} else if (bm->strategy == RS_LFU) {
		// Replacement strategy is not implemented yet
		return RC_RS_NOT_IMPLEMENTED;
	} else if (bm->strategy == RS_LRU_K) {
		// Replacement strategy is not implemented yet
		return RC_RS_NOT_IMPLEMENTED;
	}

	return rc;
} // pinPage