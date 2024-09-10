static VALUE mapper_get_chunk (VALUE self, VALUE start, VALUE length)
{
	Mapper_t *m = NULL;
	Data_Get_Struct (self, Mapper_t, m);
	if (!m)
		rb_raise (rb_eException, "No Mapper Object");

	// TODO, what if some moron sends us a negative start value?
	unsigned long _start = NUM2ULONG (start);
	unsigned long _length = NUM2ULONG (length);
	if ((_start + _length) > m->GetFileSize())
		rb_raise (rb_eException, "Mapper Range Error");

	const char *chunk = m->GetChunk (_start);
	if (!chunk)
		rb_raise (rb_eException, "No Mapper Chunk");
	return rb_str_new (chunk, _length);
}