ConstantToken* PreprocessorLexer::scanNumber(const std::string& input, size_t& end) const
{
    std::string numberString("");
    ConstantToken::Base base = ConstantToken::BASE_10;
    ConstantToken::ConstantType type = ConstantToken::TYPE_INT;
    bool hasExponent = false;
    bool (*pred)(const char ref) = &isDigit;

    size_t pos = 0;
    for (bool atEnd = false; ((! atEnd) && (pos < input.length())); ++pos) {
        const char top = input[pos];
        const char next = ((pos < (input.length() - 1)) ? input[pos + 1] : '\0');

        if ((pred != 0) && ((*pred)(top) == true)) {
            numberString += top;
            if ((pos == 0) && (top == '0')) {
                if ((next == 'x') || (next == 'X')) {
                    numberString += next;
                    ++pos;
                    pred = &isHexDigit;
                    base = ConstantToken::BASE_16;
                } else if (next == '.')
                    type = ConstantToken::TYPE_FLOAT;
                else {
                    pred = &isOctalDigit;
                    base = ConstantToken::BASE_8;
                }
            }

            switch (next) {
                case 'u':
                case 'U':
                    atEnd = true;
                    if (type == ConstantToken::TYPE_INT) {
                        numberString += next;
                        ++pos;
                        type = ConstantToken::TYPE_UINT;
                    }
                    break;

                case 'f':
                case 'F':
                    atEnd = true;
                    if (type == ConstantToken::TYPE_FLOAT) {
                        numberString += next;
                        ++pos;
                    }
                    break;

                case '.':
                    if (base == ConstantToken::BASE_10) {
                        type = ConstantToken::TYPE_FLOAT;
                        numberString += next;
                        ++pos;
                    }
                    break;

                case 'e':
                case 'E':
                    if (type == ConstantToken::TYPE_FLOAT) {
                        hasExponent = true;
                        numberString += next;
                        ++pos;
                    }
                    break;

                default:
                    break;
            }
        }  else if ((top == 'f') && (type == ConstantToken::TYPE_FLOAT)) {
            numberString += top;
        } else if ((top == '.') && (base == ConstantToken::BASE_10)) {
            // Accept the dot '.' only, if it is not the first character or
            // if a digit is following to avoid invalid ".f" strings.
            //
            if ((pos > 0) || (isDigit(next) == true)) {
                type = ConstantToken::TYPE_FLOAT;
                numberString += top;
            }
        } else if (((top == '+') || (top == '-')) && (hasExponent == true)) {
            numberString += top;
        } else
            break;
    }   // for (pos

    end = (pos > 0) ? --pos : 0;
    if (numberString.empty() == true)
        return 0;

    return new ConstantToken(PreprocessorTerminals::ID_CONSTANT, numberString, type, base);
}