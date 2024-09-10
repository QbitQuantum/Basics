    string addBinary(string a, string b) {
        int sign = 0, cur_val = 0;
        string result = "";
        if (a.length() > b.length()) {
            a.swap(b);
        }
        int indexa = a.length() - 1;
        int indexb = b.length() - 1;
        for (; indexa >= 0; --indexa, --indexb) {
            cur_val = a.at(indexa) + b.at(indexb) - '0' - '0' + sign;
            sign = cur_val >> 1;
            result = string(1, (cur_val & 0x1) + '0') + result;
        }
        for (; indexb >= 0; --indexb) {
            cur_val = b.at(indexb) - '0' + sign;
            sign = cur_val >> 1;
            result = string(1, (cur_val & 0x1) + '0') + result;
        }
        if (sign > 0) {
            result = string(1, '1') + result;
        }

        return ((result.length() > 0) ? result : "0");
    }