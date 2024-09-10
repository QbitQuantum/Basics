void NextCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(0u == args.size() || args.size() == unsigned(NumberOfArgs));

    const auto instanceNmbr = (args.size() == 0u) ? ctx.getCurrentInstance() : mili::from_string<NSCommon::InstanceId>(args[InstanceNumber]);
    const auto instance = ctx.getInstance(instanceNmbr).lock();
    mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance));

    auto nextTermination = instance->next();
    nextTermination.wait();
}