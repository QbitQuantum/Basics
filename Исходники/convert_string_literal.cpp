void convert_string_literal(const std::string &src, exprt &dest)
{
  std::string value;
  convert_string_literal(src, value);

  string_constantt result;
  result.set_value(value);

  dest.swap(result);
}