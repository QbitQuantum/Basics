  SymbolTable::Kind SymbolTable::detect_kind(const char* str, size_t size) {
    const char one = str[0];

    // A constant begins with an uppercase letter.
    if(one >= 'A' && one <= 'Z') {
      // Make sure that the rest of it is only alphanumerics
      for(size_t i = 1; i < size; i++) {
        if((isalnum(str[i]) || str[i] == '_') == false)
          return SymbolTable::Normal;
      }
      return SymbolTable::Constant;
    }

    if(one == '@') {
      // A class variable begins with @@
      if(size > 1 && str[1] == '@') {
        return SymbolTable::CVar;
      }

      // An instance variable can't start with a digit and can't be just @.
      if((size == 1) || (size > 1 && ISDIGIT(str[1]))) {
        return SymbolTable::Normal;
      }

      // An instance variable begins with @
      return SymbolTable::IVar;
    }

    // A system variable begins with __
    if(size > 2 && one == '_' && str[1] == '_') {
      return SymbolTable::System;
    }

    // Everything else is normal
    return SymbolTable::Normal;
  }