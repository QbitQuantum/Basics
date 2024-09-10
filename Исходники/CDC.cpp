void CDC::converteStringParaMaiuscula(std::string &str) {
    for(unsigned int pos=0; pos<str.length(); pos++) {
        if(str[pos]>=97 && str[pos]<=122) str[pos]-=32;
    }
}