	Proc::~Proc() {
		if (inited_) {
			closeTrace();
		}

		assert(hasValidObjects());

		delete act_;
		delete prg_;
		delete data_;
		delete inp_;
		delete outp_;
	}