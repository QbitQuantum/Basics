void CompressedColumnStoreTupleStorageSubBlock::shiftTuples(
    const tuple_id dest_position,
    const tuple_id src_tuple,
    const tuple_id num_tuples) {
  for (attribute_id attr_id = 0;
       attr_id < compression_info_.attribute_size_size();
       ++attr_id) {
    size_t attr_length = compression_info_.attribute_size(attr_id);
    if (attr_length > 0) {
      memmove(static_cast<char*>(column_stripes_[attr_id]) + dest_position * attr_length,
              static_cast<const char*>(column_stripes_[attr_id]) + src_tuple * attr_length,
              attr_length * num_tuples);
    }
  }
}