int
sqlite3_T_text16(sqlite3_context *aCtx,
                 const nsString &aValue)
{
  ::sqlite3_result_text16(aCtx,
                          aValue.get(),
                          aValue.Length() * 2, // Number of bytes.
                          SQLITE_TRANSIENT);
  return SQLITE_OK;
}