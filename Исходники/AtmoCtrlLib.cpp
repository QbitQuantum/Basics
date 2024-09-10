DLL int AtmoInitialize() {
    OleInitialize(NULL);
    if(getAtmoRemoteControl() == NULL) {
       OleUninitialize();
       return -1;
    } else {
       return 1;
    }
}