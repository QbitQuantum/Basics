bool CompressedPackedRowStoreTupleStorageSubBlock::bulkDeleteTuples(TupleIdSequence *tuples) {
  if (tuples->empty()) {
    // Nothing to do.
    return false;
  }

  const tuple_id front = tuples->front();
  const tuple_id back = tuples->back();
  const tuple_id num_tuples = tuples->numTuples();

  if ((back == *static_cast<const tuple_id*>(sub_block_memory_) - 1)
       && (back - front == num_tuples - 1)) {
    // Just truncate the back.
    *static_cast<tuple_id*>(sub_block_memory_) = front;
    if (null_bitmap_.get() != nullptr) {
      null_bitmap_->setBitRange(
          *static_cast<tuple_id*>(sub_block_memory_) * num_uncompressed_attributes_with_nulls_,
          num_tuples * num_uncompressed_attributes_with_nulls_,
          false);
    }
    return false;
  }

  // Pack the non-deleted tuples.
  tuple_id dest_tid = front;
  tuple_id src_tid = dest_tid;

  TupleIdSequence::const_iterator it = tuples->begin();
  for (tuple_id current_id = front;
       current_id < *static_cast<const tuple_id*>(sub_block_memory_);
       ++current_id, ++src_tid) {
    if (current_id == *it) {
      // Don't copy a deleted tuple.

      if (null_bitmap_.get() != nullptr) {
        // Erase the deleted tuple's entries in the null bitmap.
        null_bitmap_->shiftTailForward(dest_tid * num_uncompressed_attributes_with_nulls_,
                                       num_uncompressed_attributes_with_nulls_);
      }

      ++it;
      if (it == tuples->end()) {
        // No more to delete, so copy all the remaining tuples in one go.
        memmove(static_cast<char*>(tuple_storage_) + dest_tid * tuple_length_bytes_,
                static_cast<char*>(tuple_storage_) + (src_tid + 1) * tuple_length_bytes_,
                (*static_cast<const tuple_id*>(sub_block_memory_) - back - 1) * tuple_length_bytes_);
        break;
      }
    } else {
      // Copy the next tuple to the packed region.
      memmove(static_cast<char*>(tuple_storage_) + dest_tid * tuple_length_bytes_,
              static_cast<char*>(tuple_storage_) + src_tid * tuple_length_bytes_,
              tuple_length_bytes_);
      ++dest_tid;
    }
  }

  *static_cast<tuple_id*>(sub_block_memory_) -= num_tuples;

  return true;
}