Path::completion Path::complete(String & s) const {
	Path copy(*this);
	copy.rep += '*';
	List<Path> all;
	copy.expand_wildcards(all);

	completion ret = Path::no_completion;
	if (all.length() == 1) {
		// s = all.get()->rep;
		s = all.get().rep;
		ret = Path::unique_completion;
	}
	else if (all.length() > 1) {
		s = common_prefix(all);
		ret = Path::several_completions;
	}	
	return ret;
}