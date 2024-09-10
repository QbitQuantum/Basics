bool MessageCenter::unregisterHotkey()
{
    for (int i=0; i<hotKeyId.size(); i++) {
        ATOM id =  hotKeyId[i];
        UnregisterHotKey(self,id);
        GlobalDeleteAtom(id);
    }
    return true;
}