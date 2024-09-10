CAMLprim value ml_text_strxfrm(value string)
{
  CAMLparam1(string);
  size_t length = strxfrm(NULL, String_val(string), 0);
  char buffer[length + 1];
  strxfrm(buffer, String_val(string), length + 1);
  CAMLreturn(caml_copy_string(buffer));
}