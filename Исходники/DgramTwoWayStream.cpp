void DgramTwoWayStream::write(const Bytes& b) {
    //YARP_DEBUG(Logger::get(),"DGRAM prep writing");
    //ACE_OS::printf("DGRAM write %d bytes\n",b.length());

    if (reader) {
        return;
    }
    if (writeBuffer.get()==NULL) {
        return;
    }

    Bytes local = b;
    while (local.length()>0) {
        //YARP_DEBUG(Logger::get(),"DGRAM prep writing");
        YARP_SSIZE_T rem = local.length();
        YARP_SSIZE_T space = writeBuffer.length()-writeAvail;
        bool shouldFlush = false;
        if (rem>=space) {
            rem = space;
            shouldFlush = true;
        }
        memcpy(writeBuffer.get()+writeAvail, local.get(), rem);
        writeAvail+=rem;
        local = Bytes(local.get()+rem,local.length()-rem);
        if (shouldFlush) {
            flush();
        }
    }
}