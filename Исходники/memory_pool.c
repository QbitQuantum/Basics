/* allocates n strings in the string_buffer */
m_string* string_alloc(int n)
{
  return (m_string*) omc_alloc_interface.malloc(n*sizeof(m_string));
}