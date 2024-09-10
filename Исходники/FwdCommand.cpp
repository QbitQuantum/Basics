void FwdCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    const auto instance = ctx.getInstance(mili::from_string<NSCommon::InstanceId>(args[InstanceNumber])).lock();
    mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance));

    std::string msg;
    for (unsigned int i = GDBMessage; i < args.size(); ++i)
    {
        msg += " " + args[i];
    }

    instance->sendMessageToGDB(msg);
}