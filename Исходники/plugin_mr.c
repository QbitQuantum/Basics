static void
mr_private_indexer_done(struct mr_private *mrpriv)
{
	if (mrpriv && mrpriv->sva) {
		valuearray_free(&mrpriv->sva);
	}
	if (mrpriv && mrpriv->bva) {
		ber_bvecfree(mrpriv->bva);
		mrpriv->bva = NULL;
	}
}