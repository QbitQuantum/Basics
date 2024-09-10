public boolean isValid(String s) {
    StringBuilder sb = new StringBuilder();
    boolean valid = true;
    for (int i = 0; valid && i < s.length(); i++) {
        int lastIdx = sb.length() - 1;
        char c = s.charAt(i);
        switch (c) {
        case '{':
        case '(':
        case '[':
        sb.append(c);
        break;
        case '}':
        case ')':
        case ']':
        char lchar = (c == ']' ? '[' : (c == ')' ? '(' : '{'));
        if (lastIdx >= 0 && sb.charAt(lastIdx) == lchar)
            sb.setLength(lastIdx);
        else
            valid = false;
        break;
        }
    }
    return valid && sb.length() == 0;
    }