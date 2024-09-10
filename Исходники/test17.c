int Child2(char *arg) 
{

    if (!(strcmp(arg,"Child2"))){
        USLOSS_Console("Child2(): starting\n");
        Terminate(9);
    }
    else {
        if (!(strcmp(arg,"Child3"))){
            USLOSS_Console("Child3(): starting\n");
            Terminate(10);
        }
        else {
            USLOSS_Console("wrong argument passed ... test failed\n");
            exit(1);
        }
    }
    return 0;
} /* Child2 */