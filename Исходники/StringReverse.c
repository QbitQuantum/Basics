int main(void){
    int Option = 1;
    char Str[15];
    while(Option){
        printf("Enter a choice: \n1.) String length\n2.) String reverse\n0.) Exit\n");
        scanf("%d", &Option);

        switch(Option){
            case 1:
                printf("Enter a string: ");
                scanf("%s", Str);
                int Len = StrLen(Str);
                printf("Ans: String length is %d\n\n", Len);
                break;
            case 2:
                printf("Enter a string: ");
                scanf("%s", Str);
                StrRev(Str);
                printf("Ans: Reversed string - %s\n\n", Str);
                break;
            case 0:
               break;
            default:
                printf("Enter a valid choice\n\n");
        }
    }
}