static StructuredData::ObjectSP ParseJSONValue(JSONParser &json_parser) {
  std::string value;
  const JSONParser::Token token = json_parser.GetToken(value);
  switch (token) {
  case JSONParser::Token::ObjectStart:
    return ParseJSONObject(json_parser);

  case JSONParser::Token::ArrayStart:
    return ParseJSONArray(json_parser);

  case JSONParser::Token::Integer: {
    uint64_t uval;
    if (llvm::to_integer(value, uval, 0))
      return std::make_shared<StructuredData::Integer>(uval);
  } break;

  case JSONParser::Token::Float: {
    double val;
    if (llvm::to_float(value, val))
      return std::make_shared<StructuredData::Float>(val);
  } break;

  case JSONParser::Token::String:
    return std::make_shared<StructuredData::String>(value);

  case JSONParser::Token::True:
  case JSONParser::Token::False:
    return std::make_shared<StructuredData::Boolean>(token ==
                                                     JSONParser::Token::True);

  case JSONParser::Token::Null:
    return std::make_shared<StructuredData::Null>();

  default:
    break;
  }
  return StructuredData::ObjectSP();
}