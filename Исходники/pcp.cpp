// ------------------------------------------
int PCPStream::readPacket(Stream & in, BroadcastState & bcs) {
    int error = PCP_ERROR_GENERAL;
    try {
        AtomStream atom(in);

        ChanPacket pack;
        MemoryStream mem(pack.data, sizeof(pack.data));
        AtomStream patom(mem);


        // send outward packets
        error = PCP_ERROR_WRITE;
        if (outData.numPending()) {
            outData.readPacket(pack);
            pack.writeRaw(in);
        }
        error = PCP_ERROR_GENERAL;

        if (outData.willSkip()) {
            error = PCP_ERROR_WRITE + PCP_ERROR_SKIP;
            throw StreamException("Send too slow");
        }


        error = PCP_ERROR_READ;
        // poll for new downward packet
        if (in.readReady()) {
            int numc, numd;
            ID4 id;

            id = atom.read(numc, numd);

            mem.rewind();
            pack.len = patom.writeAtoms(id, in, numc, numd);
            pack.type = ChanPacket::T_PCP;

            //inData.writePacket(pack);
            //}
            error = PCP_ERROR_GENERAL;

            // process downward packets
            //if (inData.numPending())
            //{
            //inData.readPacket(pack);

            mem.rewind();

            //int numc,numd;
            id = patom.read(numc, numd);

            error = PCPStream::procAtom(patom, id, numc, numd, bcs);

            if (error) {
                throw StreamException("PCP exception");
            }
        }

        error = 0;

    } catch (StreamException &e) {
        LOG_ERROR("PCP readPacket: %s (%d)", e.msg, error);
    }

    return error;
}