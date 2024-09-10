    void BenchmarkSetUp() {
        hb = new HashBuild();
        hjp = new HashJoinProbe;
        hjp->setEvent("NO_PAPI");
        hb->setKey("join");
        hb->setEvent("NO_PAPI");
        sm = StorageManager::getInstance();

        t1 = sm->getTable("stock");
        t2 = sm->getTable("order_line");

        hb->addInput(t1);
        hb->addField(0);
        hjp->addInput(t2);
        hjp->addField(4);

    }