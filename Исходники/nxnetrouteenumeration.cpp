 /**
    Validate the non required parameters
    @detailed This used in the NxNetRoute Provider code to ensure that the user
              has supplied only valid digits for the fields that require only digits.
    @param[in] param A wstring which may contain alphanumeric characters
    @return bool Returns true if the parameter string consists only of numeric digits
 */
  bool NxNetRouteEnumeration::ValidateNonRequiredParameters(std::wstring &param)
  {
      if (param.empty())
      {
          param = L"0";
      }
      else
      {
          for(uint i = 0; i < param.length(); i++)
          {
              if(!isdigit(param[i]))
              {
                  return false;
              }
          }
      }
      return true;
  }