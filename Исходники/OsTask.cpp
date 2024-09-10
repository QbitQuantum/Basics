// Constructor
OsTaskBase::OsTaskBase(const UtlString& name,
                       void* pArg,
                       const int priority,
                       const int options,
                       const int stackSize)
:  mDataGuard(OsMutex::Q_PRIORITY + OsMutex::INVERSION_SAFE),
   mState(UNINITIALIZED),
   mpArg(pArg),
   mUserData(0)
{
        // If name contains %d insert the task count/index
    assert(name.length() < 240);
    char nameBuffer[256];
    sprintf(nameBuffer, name.data(), taskCount++);
    mName.append(nameBuffer);

   if (mName != "")
      OsUtil::insertKeyValue(TASK_PREFIX, mName, (intptr_t) this);
}