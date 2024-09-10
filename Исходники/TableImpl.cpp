TableValue TableValueImpl::CreateTableValue(const amqp_field_value_t &entry)
{
  switch (entry.kind)
  {
    case AMQP_FIELD_KIND_VOID:
      return TableValue();
    case AMQP_FIELD_KIND_BOOLEAN:
      return TableValue((bool)entry.value.boolean);
    case AMQP_FIELD_KIND_I8:
      return TableValue(entry.value.i8);
    case AMQP_FIELD_KIND_I16:
      return TableValue(entry.value.i16);
    case AMQP_FIELD_KIND_I32:
      return TableValue(entry.value.i32);
    case AMQP_FIELD_KIND_I64:
    case AMQP_FIELD_KIND_TIMESTAMP:
      return TableValue(entry.value.i64);
    case AMQP_FIELD_KIND_F32:
      return TableValue(entry.value.f32);
    case AMQP_FIELD_KIND_F64:
      return TableValue(entry.value.f64);
    case AMQP_FIELD_KIND_UTF8:
    case AMQP_FIELD_KIND_BYTES:
      return TableValue(std::string((char*)entry.value.bytes.bytes,
                                    entry.value.bytes.len));
    case AMQP_FIELD_KIND_ARRAY:
    {
      amqp_array_t array = entry.value.array;
      Detail::array_t new_array;

      for (int i = 0; i < array.num_entries; ++i)
      {
        new_array.push_back(CreateTableValue(array.entries[i]));
      }

      return TableValue(new_array);
    }
    case AMQP_FIELD_KIND_TABLE:
      return TableValue(CreateTable(entry.value.table));
    case AMQP_FIELD_KIND_DECIMAL:
    default:
      return TableValue();
  }
}