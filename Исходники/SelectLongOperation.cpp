bool SelectLongOperation::selectOption(const std::string& str) {
  std::vector<Option>::iterator it =
      find_if(options_.begin(), options_.end(), bind(&Option::str, _1) == str);

  if (it != options_.end() && it->shown) {
    selected(distance(options_.begin(), it));
    return true;
  }

  return false;
}