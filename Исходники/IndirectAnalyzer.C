void IndirectControlFlowAnalyzer::ReadTable(AST::Ptr jumpTargetExpr,
                                            AbsRegion index,
					    StridedInterval &indexBound,
					    int memoryReadSize,
					    bool isZeroExtend,
					    bool scanTable,
					    set<Address> &constAddr,
					    std::vector<std::pair<Address, Dyninst::ParseAPI::EdgeTypeEnum> > &targetEdges) {
    CodeSource *cs = block->obj()->cs();
    set<Address> jumpTargets;
    int start = 0;
    if (indexBound.low > 0) start = indexBound.low = start;
    for (int v = start; v <= indexBound.high; v += indexBound.stride) {
        JumpTableReadVisitor jtrv(index, v, cs, block->region(), isZeroExtend, memoryReadSize);
	jumpTargetExpr->accept(&jtrv);
	if (jtrv.valid && cs->isCode(jtrv.targetAddress)) {
        if (cs->getArch() == Arch_x86_64 && FindJunkInstruction(jtrv.targetAddress)) {
            parsing_printf("WARNING: resolving jump tables leads to junk instruction from %lx\n", jtrv.targetAddress);
            break;
        }
	    jumpTargets.insert(jtrv.targetAddress);
	} else {
	    // We have a bad entry. We stop here, as we have wrong information
	    // In this case, we keep the good entries
	    parsing_printf("WARNING: resolving jump tables leads to a bad address %lx\n", jtrv.targetAddress);
	    break;
	}
	if (indexBound.stride == 0) break;
    }
    for (auto ait = constAddr.begin(); ait != constAddr.end(); ++ait) {
        if (block->region()->isCode(*ait)) {
	    jumpTargets.insert(*ait);
	}
    }
    for (auto tit = jumpTargets.begin(); tit != jumpTargets.end(); ++tit) {
        targetEdges.push_back(make_pair(*tit, INDIRECT));
    }
}