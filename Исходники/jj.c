main(int argc, char *argv[]) {
    register int x,m=0;
    char *cl;
    char w[256];
    char tfile[L_tmpnam];
    int subs,slims,sides,drinks,allow;
    char name[32];
    char phone[10];
    char address[64];
    FILE *tfp,*order;

    printf("Content-type: text/html%c%c",LF,LF);

    cl=getenv("QUERY_STRING");
    if((!cl) || (!cl[0]))
        dump_form();

    tmpnam(tfile);
    if(!(tfp=fopen(tfile,"w"))) {
        printf("<TITLE>Server Error</TITLE>%c",LF);
        printf("<H1>Server Error</H1>%c",LF);
        printf("Server unable to get a temporary file. Please try again later.<P>%c",LF);
        exit(1);
    }

    subs=0;slims=0;sides=0;drinks=0;allow=0;
    name[0]='\0';
    phone[0]='\0';
    address[0]='\0';

    for(x=0;cl[0] != '\0'; x++) {
        m=x;
        getword(w,cl,'=');
        plustospace(w);
        unescape_url(w);
        if(!strcmp(w,"pwd")) {
            getword(w,cl,'&');
            plustospace(w);
            unescape_url(w);
            allow=(strcmp(w,PASSWORD) ? 0 : 1);
        }
        if(!strcmp(w,"sub")) {
            getword(w,cl,'&');
            plustospace(w);
            unescape_url(w);
            subs |= (1 << atoi(w));
        }
        else if(!strcmp(w,"slj")) {
            getword(w,cl,'&');
            plustospace(w);
            unescape_url(w);
            slims |= (1 << atoi(w));
        }
        else if(!strcmp(w,"sde")) {
            getword(w,cl,'&');
            plustospace(w);
            unescape_url(w);
            sides |= (1 << atoi(w));
        }
        else if(!strcmp(w,"pop")) {
            getword(w,cl,'&');
            plustospace(w);
            unescape_url(w);
            drinks |= (1 << atoi(w));
        }
        else if(!strcmp(w,"name")) {
            getword(w,cl,'&');
            plustospace(w);
            unescape_url(w);
            strcpy(name,w);
        }
        else if(!strcmp(w,"phone")) {
            getword(w,cl,'&');
            plustospace(w);
            unescape_url(w);
            strcpy(phone,w);
        }
        else if(!strcmp(w,"adr")) {
            getword(w,cl,'&');
            plustospace(w);
            unescape_url(w);
            strcpy(address,w);
        }
    }

    if(!name[0]) print_error("you didn't give your name");
    if(!address[0]) print_error("you didn't give your address");
    if(!phone[0]) print_error("you didn't give your phone number");
    if((!subs) && (!slims) && (!sides) && (!drinks)) print_error("you didn't order anything");

    if(allow) {
        char t[256];
        sprintf(t,"/bin/mail %s",JJ_FAX);
        if(!(order=popen(t,"w")))
            print_error("the server was unable to open a pipe to mail");
        printf("<TITLE>Order Sent</TITLE>%c",LF);
        printf("<H1>Order Sent</H1>%c",LF);
        printf("Your order has been sent to the UIUC e-mail to FAX gateway.<P>%c",LF);
    } else {
        printf("<TITLE>Your Order</TITLE>%c",LF);
        printf("<H1>Your Order</H1>%c",LF);
        printf("This is how your order would have looked if it had been sent.<P><PLAINTEXT>%c",LF);
        order=stdout;
    }

    fprintf(order,"My name is %s, and I would like to have the following%c",
            name,LF);
    fprintf(order,"order delivered to %s:%c%c",address,LF,LF);
    for(x=0;x<12;x++)
        if(subs & (1 << x))
            fprintf(order,"\t(1) %s%c",sublist[x],LF);
    for(x=0;x<6;x++)
        if(slims & (1 << x))
            fprintf(order,"\t(1) %s Slim Jim%c",slimlist[x],LF);
    for(x=0;x<2;x++)
        if(sides & (1 << x))
            fprintf(order,"\t(1) %s%c",sidelist[x],LF);
    for(x=0;x<4;x++)
        if(drinks & (1 << x))
            fprintf(order,"\t(1) %s%c",poplist[x],LF);
    fprintf(order,"%cPlease feel free to call me at %s if there is any%c",LF,
            phone,LF);
    fprintf(order,"problem. Thank you.%c%c.%c",LF,LF,LF);
    fclose(order);
    exit(0);
}