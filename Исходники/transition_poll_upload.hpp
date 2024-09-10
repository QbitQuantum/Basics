void StartPoll(const std::string & upload_key, FSM & fsm)
{
    if (upload_key.empty())
    {
        assert(!"Reached poll upload without upload key");
        fsm.ProcessEvent(
                event::Error{make_error_code(uploader::errc::LogicError),
                             "Filsize unavailable."});
        return;
    }

    auto fsmp = fsm.AsFrontShared();

    fsm.GetSessionMaintainer()->Call(
            mf::api::upload::poll_upload::Request(upload_key),
            [fsmp, upload_key](
                    const mf::api::upload::poll_upload::Response & response)
            {
                HandlePollResponse(upload_key, *fsmp, response);
            });
}