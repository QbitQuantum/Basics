 /**
  * @brief Checks if current character is alphanumeric (a-z|0-9).
  *
  * @return
  */
 bool IsAlphaNumberic() const {
     return IsAlpha() || IsRange('0', '9');
 }