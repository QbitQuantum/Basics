int main(int argc, char *argv[]) {
    printf("This test creates two ports and writes from one to the other.\n");
    printf("Make sure no other YARP programs are running.\n");
    printf("(or else remove the yarpNetworkSetLocalMode line)\n");

    Network yarp;
    yarp.setLocalMode(1);

    Port p1, p2;
    bool ok = p1.open("/test1") && p2.open("/test2");
    if (!ok) {
        printf("failed to open ports\n");
        return 1;
    }

    ok = yarp.connect("/test1","/test2",NULL);
    if (!ok) {
        printf("failed to connect ports\n");
        return 1;
    }

    p1.enableBackgroundWrite(true);

    MyPortable i1, i2;
    i1.val = 15;

    printf("Writing (in background)...\n");
    p1.write(i1);

    printf("Reading...\n");

    p2.read(i2);

    printf("After read, received %d\n", i2.val);
    if (i2.val==15) {
        printf("Correct!\n");
    } else {
        printf("That's not right, something failed.\n");
        return 1;
    }

    p1.close();
    p2.close();

    return 0;
}