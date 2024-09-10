bool startsiWith(const char* s, const char* prefix) {
 if (prefix==NULL || s==NULL) return false;
 int i=0;
 while (prefix[i]!='\0' && tolower(prefix[i])==tolower(s[i])) i++;
 return (prefix[i]=='\0');
 }