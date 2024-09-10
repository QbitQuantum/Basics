void ArgumentRecovery::fixCallSites(Function& base, Function& newTarget, const CallInformation& ci)
{
	auto targetInfo = TargetInfo::getTargetInfo(*base.getParent());
	
	// loop over callers and transform call sites.
	while (!base.use_empty())
	{
		CallInst* call = cast<CallInst>(base.user_back());
		Function* caller = call->getParent()->getParent();
		auto registers = getRegisterPtr(*caller);
		auto newCall = createCallSite(*targetInfo, ci, newTarget, *registers, *call);
		
		// replace call
		newCall->takeName(call);
		call->eraseFromParent();
		
		md::incrementFunctionVersion(*caller);
	}
}