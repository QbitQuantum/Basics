CAMLprim value caml_atan_float(value f)
{
  return caml_copy_double(atan(Double_val(f)));
}