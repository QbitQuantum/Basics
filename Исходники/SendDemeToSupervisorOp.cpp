/*!
 *  \brief Initialize the operator
 *  \param ioSystem Current system
 */
void HPC::SendDemeToSupervisorOp::init(System& ioSystem)
{
    Beagle_StackTraceBeginM();
    mComm = castHandleT<HPC::MPICommunication>(ioSystem.getComponent("MPICommunication"));
    Beagle_StackTraceEndM("HPC::SendDemeToSupervisorOp::init(System&)");
}