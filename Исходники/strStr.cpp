int main(){
    char a[]="abdfa";
    char b[]="df";

    char* p = strStr(a,b);
    printf("ans: %s\n",p);

    return 0;
}