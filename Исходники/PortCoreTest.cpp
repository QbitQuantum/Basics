    void testBackground() {
        report(0,"background transmission check...");

        expectation = "";
        receives = 0;

        Contact write = NetworkBase::registerContact(Contact("/write", "tcp", "127.0.0.1", safePort()));
        Contact read = NetworkBase::registerContact(Contact("/read", "tcp", "127.0.0.1", safePort()+1));
        Contact fake("tcp", "127.0.0.1", safePort()+2);

        checkEqual(NetworkBase::queryName("/write").isValid(),true,"name server sanity");
        checkEqual(NetworkBase::queryName("/read").isValid(),true,"name server sanity");

        PortCore sender;

        sender.setWaitBeforeSend(false);
        sender.setWaitAfterSend(false);

        PortCore receiver;
        receiver.setReadHandler(*this);
        sender.listen(write);
        receiver.listen(read);
        sender.start();
        receiver.start();
        //Time::delay(1);
        Bottle bot;
        bot.addInt32(0);
        bot.addString("Hello world");
        report(0,"sending bottle, should received nothing");
        expectation = "";
        sender.send(bot);
        Time::delay(0.3);
        checkEqual(receives,0,"nothing received");
        NetworkBase::connect("/write", "/read");
        Time::delay(0.3);
        report(0,"sending bottle, should receive it this time");
        expectation = bot.toString();
        sender.send(bot);
        for (int i=0; i<1000; i++) {
            if (receives==1) break;
            Time::delay(0.3);
        }
        checkEqual(receives,1,"something received");
        sender.close();
        receiver.close();
    }