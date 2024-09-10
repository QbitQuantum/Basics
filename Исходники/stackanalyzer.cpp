void StackAnalyzer::analyze() {
	std::vector<void *> buffer{64};
	auto count = RtlCaptureStackBackTrace(base_skip_frames, buffer.size(), buffer.data(), NULL);
	if (count < buffer.size()) {
		buffer.resize(count);
	}
	this->stack_addrs = std::move(buffer);
}