int main(int argc, char *argv[])
{
    srand(time(NULL));
    bool giveme = false;
    long zero = 0;
    char buf[100];
    bool gotflag = false;
    puts("Welcome to hell, we have real strong JumpFu here");
start:
    DBUG("start")
    puts("Where to?");
    fflush(0);
    zero = 0;
    fgets(buf, 117, stdin);
    buf[99] = 0;
    if (strncmp(buf+10, "WHO GOES THERE", strlen("WHO GOES THERE")) == 10)
        goto six;
    else
        goto two;
one:
    DBUG("one")
    puts("WELCOME BACK");
    goto start;
two:
    DBUG("two")
    puts("Who are you? Where are you even going?");
    fflush(0);
    if (buf[69]=='8')
        goto eleven;
    if (buf[69]=='9')
        goto five;
    goto one;
three:
    DBUG("three")
    puts("Here we go again...");
    fflush(0);
    goto eight;
four:
    DBUG("four")
    if (!zero)
        goto nine;
five:
    DBUG("five")
    giveme = true;
    if (!zero)
        goto eight;
six:
    DBUG("six")
    giveme = false;
seven: //lucky number seven
    DBUG("seven")
    if (giveme){
        gotflag = true;
        print_flag();
        goto end;
    }else{
        puts("NO!!! GO AWAY");
        fflush(0);
    }
eight:
    DBUG("eight")
    puts("Goodnight! See you later!");
    fflush(0);
    sleep(1);
    if (rand() % 2)
        goto one;
    else
        goto twelve;
nine:
    DBUG("nine")
    goto two;
ten:
    DBUG("ten")
    if (!zero)
        goto end;
    goto one;
eleven:
    DBUG("eleven")
    if (strncmp(&zero, "risky!", strlen("risky")))
        goto eight;
    goto six;
twelve:
    DBUG("twelve")
    if (zero)
        goto seven;
    else
        goto ten;
end:
    DBUG("end")
    if (!gotflag)
        puts("Looks like you are leavin here empty handed.");
    else
        puts("Nice work. You won.");
    fflush(0);
    return 0;
}