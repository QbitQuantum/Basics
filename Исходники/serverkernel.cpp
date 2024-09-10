void ServerKernel::requestStopProcessByPID(KernelRequest *request){
    //Die gewählte PID einlesen
    uint pidToFind = request->propertyValue(KernelRequest::ProcessToStop).toUInt();

    QList<ProcessManager::Process *> processes = ProcessManager::instance()->processes();

    //Alle Prozesse durchgehen
    for(int i = 0; i < processes.length();++i){

        //Prozess gefunden?
        if(processes.at(i)->pid == pidToFind){
            //Prozess enden lassen
            processes.at(i)->thread->endProcess();
            //Prozess beenden
            processes.at(i)->thread->terminate();

            //Prozess später löschen
            //this->_objectsToDelete.append(processes.at(i)->thread);

            break;
        }
    }
}