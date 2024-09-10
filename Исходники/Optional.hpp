 /**
  * @brief   Gets the constant value.
  * @copydetails value
  */
 const T& value() const
 {
     if (!m_hasValue) fatalExit("tried to retrieve value of Optional without value");
     return *ptr();
 }