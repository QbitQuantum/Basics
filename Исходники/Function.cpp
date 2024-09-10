int qwe(std::string s1, std::string s2){
    int result=0;
    int k,n;

    if (s1.length() >= s2.length()){
        for (int i=0; i < s1.length(); i++){
            k=0;
            n=i;
            if (result > (s1.length()-i)) break;
            if ((s1.length()-i) >= s2.length()){
                for (int j=0; j < s2.length(); j++){
                    if (s1[n] == s2[j]) k++;
                    n++;
                }
            }else{
                for (int j=0; j<(s1.length()-i); j++){
                    if (s1[n] == s2[j]) k++;
                    n++;
                }
            }
            if (result < k) result = k;

        }
    }

    if (s2.length() > s1.length()){
        for (int i=0; i < s2.length(); i++){
            k=0;
            n=i;
            if (result > (s2.length()-i)) break;
            if ((s2.length()-i) >= s1.length()){
                for (int j=0; j < s1.length(); j++){
                    if (s2[n] == s1[j]) k++;
                    n++;
                }
            }else{
                for (int j=0; j<(s2.length()-i); j++){
                    if (s2[n] == s1[j]) k++;
                    n++;
                }
            }
            if (result < k) result = k;

        }
    }

    return result;
}