// ------------------------------------------------------------------
// ciFieldLayout::ciFieldLayout
ciFieldLayout::ciFieldLayout(ciInstanceKlass* my_klass) {
  assert(my_klass->is_loaded(), "must be loaded");
  ASSERT_IN_VM;

  klassOop klass = my_klass->get_klassOop();

  Arena* arena = CURRENT_ENV->arena();
  GrowableArray<BasicType>* fieldtypes =
    new (arena) GrowableArray<BasicType>(arena, 8, 0, T_VOID);
  GrowableArray<int>* aflags =
    new (arena) GrowableArray<int>(arena, 8, 0, 0);
  GrowableArray<int>* fieldoffsets =
    new (arena) GrowableArray<int>(arena, 8, 0, 0);

  int pos = 0;

  fill_in_header_fields(fieldtypes, fieldoffsets, pos);
  _header_count = pos;
  fill_in_instance_fields(fieldtypes, fieldoffsets, aflags, pos, klass);

#if 0
  // [RGV] instance size is in word's but pos is number
  // of fields.
  int fill_to = my_klass->instance_size();
  if (fieldtypes->length() < fill_to)
    fields->at_put_grow(fill_to-1, T_VOID, T_VOID);
  if (aflags->length() < fill_to)
    aflags->at_put_grow(fill_to-1, 0, 0);
#endif

  _fieldtypes = fieldtypes;
  _access_flags = aflags;
  _fieldoffsets = fieldoffsets;
}