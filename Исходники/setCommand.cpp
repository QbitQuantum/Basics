void SetCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == 1u || args.size() == 2u);

    auto instanceId = ctx.getCurrentInstance();
    const auto instance = ctx.getInstance(instanceId).lock();
    mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance));

    if (args.size() == 1u)
    {
        const auto& assignation = args[0u];
        auto pos = assignation.find('=');
        if (pos == std::string::npos)
        {
            throw NSCommon::InvalidArgument(assignation);
        }
        instance->setVariable(assignation.substr(0u, pos), assignation.substr(pos + 1u));
    }
    else // args.size() == 2u
    {
        instance->setEnvironment(args[0u], args[1u]);
    }
}