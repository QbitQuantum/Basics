	void compile(const std::string &entry, const std::string &target)
	{
		if (_src.empty()) return;
		if (entry != _entry || target != _target) _dirty = true;
		if (!_dirty) return;

		_bin = nullptr;
		_msg = nullptr;

		_hr = D3DCompile(&_src[0], _src.size(), nullptr, _defs, _inc, entry.c_str(), target.c_str(), _flags1, _flags2, &_bin, &_msg);
		_dirty = false;
	}