/**
 * Process the de-activation of a sale on one product in the inventory.
 *
 * @return SUCCESS on success, else -1
 */
static int do_nosale(void) {
	Product *p = NULL;
	char bc[BARCODE_SZ] = {0};
	unsigned int sale_percent = 0;

	// recv barcode
	RECV(STDIN, bc, BARCODE_SZ);

	// find product in inventory with matching bar code
	p = get_product_by_barcode(bc);

	// if not found, return -1
	if (NULL == p) return -1;

	// update product's sale fn ptr
	p->sfn = onsale_fn[0];

	return SUCCESS;
}