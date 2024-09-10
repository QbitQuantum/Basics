void Functions::tan(Aurora::NWScript::FunctionContext &ctx) {
	ctx.getReturn() = tanf(ctx.getParams()[0].getFloat());
}