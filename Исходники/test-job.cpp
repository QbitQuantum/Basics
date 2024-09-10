bool Test::JobMachineName::run()
{
    const std::string machine_name("test-machine1");
    Job j1(1, machine_name);

    if (j1.get_machine() == machine_name)
        return true;
    else
        return false;
}