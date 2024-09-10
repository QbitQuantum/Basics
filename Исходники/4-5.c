int main(void)
{
        /* reverse Polish calculator */

        int type;
        double op2;
        char s[MAXOP];

        while ((type = getop(s)) != EOF) {
                switch (type) {
                case NUMBER:
                        push(atof(s) * sign);
                        sign = 1;    /* reset sign */
                        break;
                case SIN:
                        push(sin(pop()));
                        break;
                case COS:
                        push(cos(pop()));
                        break;
                case EXP:
                        push(exp(pop()));
                        break;
                case POW:
                        op2 = pop();
                        push(pow(pop(), op2));
                        break;
                case SQRT:
                        push(sqrt(pop()));
                        break;
                case '+':
                        push(pop() + pop());
                        break;
                case '*':
                        push(pop() * pop());
                        break;
                case '-':
                        op2 = pop();
                        push(pop() - op2);
                        break;
                case '/':
                        op2 = pop();
                        if (op2 != 0.0)
                                push(pop() / op2);
                        else
                                printf("error: zero devision\n");
                        break;
                case '%':
                        op2 = pop();
                        if (op2 != 0)
                                push(fmod(pop(), op2));
                        else
                                printf("error: zero devision\n");
                        break;
                case '\n':
                        if (popallowed)
                                printf("\t%.8g\n", pop());
                        else
                                popallowed = 1;
                        break;
                case '?':
                        printtop();
                        break;
                case '&':
                        dupetop();
                        break;
                case '~':
                        swaptop();
                        break;
                case '!':
                        clrstack();
                        break;
                default:
                        printf("error: unknown command\n");
                        break;
                }
        }
        return 0;
}