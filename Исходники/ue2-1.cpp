    void run() {
        while(1) {

            //incrementCounter.enter();
            if(strcmp(name,"1")) {
                firstCounter += 50;
            } else {
                secondCounter += 50;
            }
            globalCount += 50;
            //incrementCounter.leave();

            xprintf("Process %s called.\n Sum: %ld, globalCount: %ld, Diff: %ld\n",name,firstCounter + secondCounter,globalCount, firstCounter + secondCounter - globalCount);
            FFLUSH();
        }
    }