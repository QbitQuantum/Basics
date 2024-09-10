static std::string
format_key_and_json_value(std::string const &key,
                          nlohmann::json const &value) {
  return (boost::format{"%1%:%2%"} % escape(key) % escape(format_json_value(value))).str();
}