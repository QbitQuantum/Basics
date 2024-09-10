void MachineOperation::operator () (osg::Object* object)
{
    Machine* machine = dynamic_cast<Machine*>(object);
    if (machine)
    {
        std::string application;
        if (_task->getProperty("application",application))
        {
            osg::Timer_t startTick = osg::Timer::instance()->tick();

            _task->setProperty("hostname",machine->getHostName());
            _task->setStatus(Task::RUNNING);
            _task->setWithCurrentDate("date");
            _task->write();
            
            // machine->log(osg::NOTICE,"machine=%s running task=%s",machine->getHostName().c_str(),_task->getFileName().c_str());

            machine->startedTask(_task.get());

            int result = machine->exec(application);
            
            machine->endedTask(_task.get());

            // read any updates to the task written to file by the application.
            _task->read();
            
            double duration;
            if (!_task->getProperty("duration",duration))
            {
                duration = osg::Timer::instance()->delta_s(startTick, osg::Timer::instance()->tick());
            }

            if (result==0)
            {
                // success
                _task->setStatus(Task::COMPLETED);
                _task->write();

                // need to update taskmanger with any new file lists
                if (machine->getMachinePool() && machine->getMachinePool()->getTaskManager())
                {
                    std::string fileListBaseName;
                    if (_task->getProperty("fileListBaseName",fileListBaseName))
                    {
                        machine->getMachinePool()->getTaskManager()->addRevisionFileList(fileListBaseName+".added");
                        machine->getMachinePool()->getTaskManager()->addRevisionFileList(fileListBaseName+".removed");
                        machine->getMachinePool()->getTaskManager()->addRevisionFileList(fileListBaseName+".modified");
                    }
                }
            }
            else
            {
                // failure
                _task->setStatus(Task::FAILED);
                _task->write();
                
                // tell the machine about this task failure.
                machine->taskFailed(_task.get(), result);
            }
            
            // machine->log(osg::NOTICE,"machine=%s completed task=%s in %f seconds, result=%d",machine->getHostName().c_str(),_task->getFileName().c_str(),duration,result);
        }

    }
}