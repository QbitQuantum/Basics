int main(int argc, char *argv[]) {

    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */

    int PIN = 0;
    unsigned long RCcode = atol(argv[1]);
    unsigned int RClength = atoi(argv[2]);

    if (wiringPiSetup () == -1) return 1;
    printf("Sending RCcode[%lu] RClength[%i]\n", RCcode, RClength);
    RCSwitch mySwitch = RCSwitch();
    mySwitch.enableTransmit(PIN);
    mySwitch.send(RCcode, RClength);

    return 0;
}