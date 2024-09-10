bool trpgModelTable::Read(trpgReadBuffer &buf)
{
    int32 numModel;
    trpgToken tok;
    int32 len;
    bool status;

    try {
        buf.Get(numModel);
        for (int i=0;i<numModel;i++) {
            trpgModel model;
            buf.GetToken(tok,len);
            bool readHandle;
            if (tok == TRPGMODELREF)
                readHandle = false;
            else if (tok == TRPGMODELREF2)
                readHandle = true;
            else
                throw 1;
            buf.PushLimit(len);
            status = model.Read(buf,readHandle);
            buf.PopLimit();
            if (!status)  throw 1;
            AddModel(model);
        }
    }
    catch (...) {
        return false;
    }

    return isValid();
}