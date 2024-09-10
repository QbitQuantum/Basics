bool clang_c_convertert::convert_string_literal(
  const clang::StringLiteral &string_literal,
  exprt &dest)
{
  typet type;
  if(get_type(string_literal.getType(), type))
    return true;

  string_constantt string(string_literal.getBytes().str(), type);
  dest.swap(string);

  return false;
}