struct oid_info *
allocate_oid_info(msgpack_object *o, struct cid_info *ci)
{
	struct oid_info *oi;
	char tmp_buf[2048];
	struct ber e;

	if (o->type != MSGPACK_OBJECT_RAW) return NULL;
	e = ber_init(tmp_buf, 2048);
	if (encode_string_oid(o->via.raw.ptr, o->via.raw.size, &e) < 0)	return NULL;

	oi = malloc(sizeof(*oi));
	if (!oi)
		croak(2, "allocate_oid_info: malloc(oid_info)");
	PS.active_oid_infos++;
	PS.total_oid_infos++;
	bzero(oi, sizeof(*oi));
	oi->cid = ci->cid;
	oi->fd  = ci->fd;
	oi->oid = ber_dup(&e);

	return oi;
}