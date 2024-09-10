/*
 * Note: info->size == 6 is special; this means a base size 4 bytes,
 * and secondiory (high) size of 2 bytes.  This is needed for the
 * special case of i_blocks_high and i_file_acl_high.
 */
static errcode_t parse_uint(struct field_set_info *info, char *field,
			    char *arg)
{
	unsigned long long n, num, mask, limit;
	int suffix = check_suffix(field);
	char *tmp;
	void *field1 = info->ptr, *field2 = info->ptr2;
	int size = (info->size == 6) ? 4 : info->size;
	union {
		__u64	*ptr64;
		__u32	*ptr32;
		__u16	*ptr16;
		__u8	*ptr8;
	} u;

	if (suffix == 1)
		field2 = 0;
	if (suffix == 2) {
		field1 = field2;
		field2 = 0;
	}

	u.ptr8 = (__u8 *) field1;
	if (info->flags & FLAG_ARRAY)
		u.ptr8 += array_idx * info->size;

	errno = 0;
	num = STRTOULL(arg, &tmp, 0);
	if (*tmp || errno) {
		fprintf(stderr, "Couldn't parse '%s' for field %s.\n",
			arg, info->name);
		return EINVAL;
	}
	mask = ~0ULL >> ((8 - size) * 8);
	limit = ~0ULL >> ((8 - info->size) * 8);
	if (field2 && info->size != 6)
		limit = ~0ULL >> ((8 - info->size*2) * 8);

	if (num > limit) {
		fprintf(stderr, "Value '%s' exceeds field %s maximum %llu.\n",
			arg, info->name, limit);
		return EINVAL;
	}
	n = num & mask;
	switch (size) {
	case 8:
		*u.ptr64 = n;
		break;
	case 4:
		*u.ptr32 = n;
		break;
	case 2:
		*u.ptr16 = n;
		break;
	case 1:
		*u.ptr8 = n;
		break;
	}
	if (!field2)
		return 0;
	n = num >> (size*8);
	u.ptr8 = (__u8 *) field2;
	if (info->size == 6)
		size = 2;
	switch (size) {
	case 8:
		*u.ptr64 = n;
		break;
	case 4:
		*u.ptr32 = n;
		break;
	case 2:
		*u.ptr16 = n;
		break;
	case 1:
		*u.ptr8 = n;
		break;
	}
	return 0;
}