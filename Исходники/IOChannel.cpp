bool
IOChannel::GetCommandFromQueue (std::string &cmd)
{
    if (m_command_queue.empty())
        return false;
    cmd.swap(m_command_queue.front());
    m_command_queue.pop ();
    return true;
}