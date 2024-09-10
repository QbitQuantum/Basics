void TerminationSignalHandler(int)
{
    ACE_OS::printf("Server goes down ...  \n");
//    ACSError::done();
    orb->shutdown (true);
}