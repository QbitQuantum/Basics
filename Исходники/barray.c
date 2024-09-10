/**
 * Pack a unsigned 64 bits integer into this byte array. If the byte array
 * capacity isn't enough, the buffer is increased with the exact size needed.
 * Consider resizing the byte array if performance becomes an issue.
 *
 * @see byte_array_resize()
 */
void _byte_array_pack64(struct byte_array *ba, uint64_t v)
{
	ensure_size(ba, sizeof(v));
	union {
		uint64_t i;
		char c[8];
	} nv = { htonll(v) };
	memcpy(ba->ptr + ba->len, nv.c, sizeof(v));
	ba->len += sizeof(v);
}