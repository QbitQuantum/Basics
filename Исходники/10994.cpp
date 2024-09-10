int main(){

    long long a,b;

    input.grabBuffer();

    while (true){

        a=input.rInt();
        b=input.rInt();

        if (a<0 && b<0)return 0;

        printf("%lld\n",sumOfAllDigitFromZeroToX(b)-sumOfAllDigitFromZeroToX(a-1));

    }

}