    /**
     * Implements plain-old positive integer multiplication.
     */
    string multiply(string num1, string num2) {
        // make sure num1 is longer
        if(num1.length() < num2.length())
            num1.swap(num2);

        list<int> value, temp_value;
        value.push_back(0); // initialize to 0
        for(int i=num2.length()-1;i >= 0;--i) {
            temp_value.clear();

            int d = num2[i] - '0', carry = 0, product;
            if(d == 0) continue;

            // "shifting" 
            for(int j=num2.length()-i-1;j > 0;--j) temp_value.push_back(0);

            for(int j=num1.length()-1;j >= 0;--j) {
                product = (num1[j]-'0') * d + carry;
                temp_value.push_back(product % 10);
                carry = product / 10;
            }

            if(carry) temp_value.push_back(carry);

            add_numbers(value, temp_value);
        }

        stringstream ss;
        for(auto it = value.rbegin();it != value.rend();++it)
            ss << *it;

        return ss.str();
    }