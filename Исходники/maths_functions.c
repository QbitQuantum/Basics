int main()
{
    float a, b, r;
    char op;
    do {
       printf("Extra line of code --- \n");
       printf("Number operator Number: ");

       scanf(" %f %c %f", &a, &op, &b);
       switch (op)
       {
           case '+' : r = add(a,b);
                      break;
           case '*' : r = product(a,b);
                      break;
           case '-' : r = subtract(a,b);
                      break;
           case '/' : r = divide(a,b);
                      break;
           case '%' : r = remainder(a,b);
                      break; 
           case 'q' : break;
           default  : op='?';
       }
       if (op=='?')
          printf("Unknown operator\n");
       else if (op=='q')
          printf("Bye\n");
       else
          printf("%f %c %f = %f\n", a, op, b, r);
    }
    while (op != 'q');
    
    return 0;
}