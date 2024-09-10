bool CourseTrainerApp::OnInit()
{
    #ifdef WINDOWS
        CreateMutexA(0, FALSE, "Local\\$myprogram$"); // try to create a named mutex
        if(GetLastError() == ERROR_ALREADY_EXISTS) // did the mutex already exist?
        {
            wxMessageDialog(NULL, "Another process already running.","Error").ShowModal();
            return false;
        }
    #else
        pid_t pid = getpid();
        std::stringstream command;
        command << "ps -eo pid,comm | grep CourseTrainer | grep -v " << pid;
        int isRuning = system(command.str().c_str());

        if (isRuning==0)
        {
            wxMessageDialog(NULL, "Another process already running.","Error").ShowModal();
            return false;
        }
    #endif // WINDOWS
    frame = new CourseTrainerFrame(0L, _("Course Calculatings"));
    WelcomeScreen* dialog=new WelcomeScreen(nullptr,wxID_ANY,"Identification",frame);
    dialog->Show();
    return true;
}