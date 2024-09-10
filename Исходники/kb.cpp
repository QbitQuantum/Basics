Kb::~Kb(){
    activeDevices.remove(this);
    if(!isOpen()){
        terminate();
        wait(1000);
        return;
    }
    // Kill notification thread and remove node
    if(notifyNumber > 0)
        cmd.write(QString("idle\nnotifyoff %1\n").arg(notifyNumber).toLatin1());
    cmd.flush();
    terminate();
    wait(1000);
    // Reset to hardware profile
    if(_hwProfile){
        _currentProfile = _hwProfile;
        hwSave();
    }
    cmd.close();
}