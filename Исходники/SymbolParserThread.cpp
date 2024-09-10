void SymbolParserThread::ParseFileSymbols(wxInputStream& input, std::vector<Symbol*>& symbols)
{

    if (!input.IsOk())
    {
        return;
    }

    wxString token;

    unsigned int lineNumber = 1;

    Symbol *return_symbol = nullptr;

    wxStack<Symbol *> symStack;
    symStack.push(nullptr);

    std::vector<Token> tokens;
    while (GetToken(input, token, lineNumber))
    {
      tokens.emplace_back(token, lineNumber);
    }

    for (unsigned current_token = 0; current_token < tokens.size(); ++current_token)
    {
      token = tokens[current_token].token;
      lineNumber = tokens[current_token].lineNumber;

      if (token == "function")
      {
        unsigned int defLineNumber = lineNumber;
        Symbol *function = nullptr;

        // Lua functions can have these forms:
        //    function (...)
        //    function Name (...)
        //    function Module.Function (...)
        //    function Class:Method (...)

        wxString t1;
        if (!GetNextToken(tokens, t1, lineNumber, current_token)) break;

        if (t1 == "(")
        {
          // The form function (...) which doesn't have a name. If we
          // were being really clever we could check to see what is being
          // done with this value, but we're not.
          continue;
        }

        wxString t2;

        if (!GetNextToken(tokens, t2, lineNumber, current_token)) break;

        if (t2 == "(")
        {
          function = new Symbol(symStack.top(), t1, defLineNumber);

          if (return_symbol)
          {
            function->typeSymbol = return_symbol;
            return_symbol = nullptr;
          }

          // The form function Name (...).
          symbols.push_back(function);
        }
        else
        {

          wxString t3;
          if (!GetNextToken(tokens, t3, lineNumber, current_token)) break;

          if (t2 == "." || t2 == ":")
          {
            Symbol *module = GetSymbol(t1, symbols);
            if (module == nullptr)
            {
              module = new Symbol(symStack.top(), t1, defLineNumber, SymbolType::Module);
              symbols.push_back(module);
            }

            function = new Symbol(module, t3, defLineNumber);
            if (return_symbol)
            {
              function->typeSymbol = return_symbol;
              return_symbol = nullptr;
            }

            symbols.push_back(function);
          }

        }


        if (function)
          symStack.push(function);

      }
      else if (token == "decodadef")
      {
        //A decodadef will be in the form:
        //decodadef name { Definitions }
        //decodadef name ret

        unsigned int defLineNumber = lineNumber;

        wxString moduleName;
        if (!GetNextToken(tokens, moduleName, lineNumber, current_token)) break;

        wxString t1 = PeekNextToken(tokens, current_token, lineNumber);
        if (t1 == "{")
        {
          if (!GetNextToken(tokens, t1, lineNumber, current_token)) break;
          //outputWin->OutputMessage("Processing " + moduleName);

          Symbol *module = GetSymbol(moduleName, symbols);
          if (module == nullptr)
          {
            module = new Symbol(symStack.top(), moduleName, lineNumber, SymbolType::Type);
            symbols.push_back(module);
          }

          DecodaDefRecursive(symbols, lineNumber, module, tokens, current_token);
        }
        else
        {
          DecodaDefFunction(symbols, lineNumber, nullptr, tokens, current_token, moduleName);
        }
      }
      else if (token == "end")
      {
        if (symStack.size() > 1)
          symStack.pop();
      }
      else if (token == "decodaprefix")
      {
        //A decodaprefix will be in the form:
        //decodaprefix Module name

        /*
        decodaprefix this __FILENAME__
        decodaprefix this { Weapon nil }

        */

        unsigned int defLineNumber = lineNumber;

        wxString moduleName;
        if (!GetNextToken(tokens, moduleName, lineNumber, current_token)) break;


        Symbol *module = GetSymbol(moduleName, symbols, SymbolType::Prefix);
        if (module == nullptr)
        {
          module = new Symbol(nullptr, moduleName, defLineNumber, SymbolType::Prefix);
          symbols.push_back(module);
        }

        wxString t1;
        if (!GetNextToken(tokens, t1, lineNumber, current_token)) break;

        //List of 
        if (t1 == "{")
        {
          DecodaPrefixRecursive(symbols, lineNumber, module, tokens, current_token);
        }
        else
        {
          Symbol *sym_prefix = new Symbol(module, t1, defLineNumber, SymbolType::Prefix);
          sym_prefix->requiredModule = moduleName;
          symbols.push_back(sym_prefix);
        }
      }
      else if (token == "decodareturn")
      {
        //A decodaprefix will be in the form:
        //decodareturn Module

        unsigned int defLineNumber = lineNumber;

        wxString moduleName;
        if (!GetNextToken(tokens, moduleName, lineNumber, current_token)) break;

        Symbol *module = GetSymbol(moduleName, symbols);
        if (module == nullptr)
        {
          module = new Symbol(symStack.top(), moduleName, lineNumber, SymbolType::Type);
          symbols.push_back(module);
        }

        return_symbol = module;
      }
      else if (token == "=")
      {
        unsigned int defLineNumber = lineNumber;

        //If we find an equal sign, we need to find the left and right hand side
        unsigned start = current_token;

        //First handle +=, -=, *=, /=
        wxString prev = PeekPrevToken(tokens, current_token, lineNumber);
        if (prev == "+" || prev == "-" || prev == "*" || prev == "/")
          GetPrevToken(tokens, prev, lineNumber, current_token);

        wxStack<wxString> lhs_stack;
        wxString lhs;
        if (!GetPrevToken(tokens, lhs, lineNumber, current_token)) break;
        
        lhs_stack.push(lhs);

        int currentLine = lineNumber;

        prev = PeekPrevToken(tokens, current_token, lineNumber);
        while ((prev == "." || prev == ":" || prev == ")" || prev == "]") && lineNumber == currentLine)
        {
          if (prev == "." || prev == ":")
          {
            GetPrevToken(tokens, prev, lineNumber, current_token);
            lhs_stack.push(prev);

            wxString part;
            if (!GetPrevToken(tokens, part, lineNumber, current_token)) return;
            if (part == ")" || part == "]")
            {
              current_token++;
              prev = part;
              continue;
            }

            lhs_stack.push(part);
          }
          else if (prev == ")" || prev == "]")
          {
            GetPrevToken(tokens, prev, lineNumber, current_token);
            lhs_stack.push(prev);

            wxString open;
            wxString close;

            if (prev == ")")
            {
              open = "(";
              close = ")";
            }
            else if (prev == "]")
            {
              open = "[";
              close = "]";
            }


            int parenStack = 0;
            wxString part;
            if (!GetPrevToken(tokens, part, lineNumber, current_token)) return;
            for (;;)
            {
              if (part == close)
                parenStack++;
              if (part == open)
              {
                if (parenStack == 0)
                  break;
                parenStack--;
              }

              lhs_stack.push(part);
              if (!GetPrevToken(tokens, part, lineNumber, current_token)) return;
            }
            lhs_stack.push(part);

            if (!GetPrevToken(tokens, part, lineNumber, current_token)) return;
            lhs_stack.push(part);
          }

          prev = PeekPrevToken(tokens, current_token, lineNumber);
        }

        //Parse rhs
        current_token = start;

        //First handle +=, -=, *=, /=
        wxString next = PeekNextToken(tokens, current_token, lineNumber);
        bool valid = true;
        for (int i = 0; i < next.size(); ++i)
        {
          if (IsSymbol(next[i]) || IsSpace(next[i]))
          {
            valid = false;
            break;
          }
        }

        wxString rhs;

        if (valid)
        {
          GetNextToken(tokens, next, lineNumber, current_token);
          rhs.Append(next);

          next = PeekNextToken(tokens, current_token, lineNumber);
          while ((next == "." || next == ":" || next == "(" || next == "[") && lineNumber == currentLine)
          {
            if (next == "." || next == ":")
            {
              GetNextToken(tokens, next, lineNumber, current_token);
              rhs.Append(next);

              wxString part;
              if (!GetNextToken(tokens, part, lineNumber, current_token)) return;
              rhs.Append(part);
            }
            else if (next == "(" || next == "[")
            {
              GetNextToken(tokens, next, lineNumber, current_token);
              rhs.Append(next);

              wxString open;
              wxString close;

              if (next == "(")
              {
                open = "(";
                close = ")";
              }
              else if (next == "[")
              {
                open = "[";
                close = "]";
              }


              int parenStack = 0;
              wxString part;
              if (!GetNextToken(tokens, part, lineNumber, current_token)) return;
              for (;;)
              {
                if (part == open)
                  parenStack++;
                if (part == close)
                {
                  if (parenStack == 0)
                    break;
                  parenStack--;
                }

                rhs.Append(part);
                if (!GetNextToken(tokens, part, lineNumber, current_token)) return;
              }
              rhs.Append(part);
            }

            next = PeekNextToken(tokens, current_token, lineNumber);
          }
        }

        //Build up the strings with the stacks
        if (lhs_stack.size() > 0 && rhs.size() > 0)
        {
          lhs.Empty();

          while (!lhs_stack.empty())
          {
            lhs.Append(lhs_stack.top());
            lhs_stack.pop();
          }

          Symbol *assignment = new Symbol(symStack.top(), lhs, defLineNumber, SymbolType::Assignment);
          assignment->rhs = rhs;
          symbols.push_back(assignment);
        }

        //Reset token
        current_token = start;
      }
    }
}