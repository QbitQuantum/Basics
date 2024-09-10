rc_t MYSQLRecord::get_data(uint32_t idx, float_t* val) {

  CHECK_FIELD;
  (*val) = (float_t)ATOI(*(m_row + idx));
  return RC_S_OK;
}