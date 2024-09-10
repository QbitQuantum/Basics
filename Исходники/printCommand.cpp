void PrintCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == ArgumentsNumber);

    Message msg;
    const auto cID = ctx.getCurrentInstance();
    const auto instance = ctx.getInstance(cID).lock();
    mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance));

    instance->evaluateExpression(args[Expression], msg);
    std::cout << args[Expression] << " = " << msg << std::endl;
}