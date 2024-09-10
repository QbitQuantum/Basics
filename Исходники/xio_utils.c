/*---------------------------------------------------------------------------*/
size_t xio_write_tlv(uint32_t type, uint64_t len, uint8_t *buffer)
{
	struct xio_tlv *tlv = (struct xio_tlv *)buffer;

	tlv->magic	= htonl(XIO_MAGIC);
	tlv->type	= htonl(type);
	tlv->len	= htonll(len);

	return sizeof(struct xio_tlv) + len;
}