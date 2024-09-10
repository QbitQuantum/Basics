    string add(string num1, string num2) {  // 对两个string相加
        reverse(num1.begin(),num1.end());
        reverse(num2.begin(),num2.end());
        
        if(num1.size() < num2.size()) num1.swap(num2);
        int cflag = 0;

        int i = 0;
        for(; i < num2.size(); ++i) {
            int temp = (num2[i] - '0')+(num1[i]-'0')+cflag;
            cflag = temp/10;
            num1[i] = temp%10 + '0';
        }
        
        while(cflag&&i<num1.size()) {
            int temp = num1[i]-'0'+cflag;
            cflag = temp/10;
            num1[i++] = temp%10 + '0';
        }
        
        if(cflag) num1.push_back(cflag+'0');
        
        reverse(num1.begin(),num1.end());
        
        return num1;
    }