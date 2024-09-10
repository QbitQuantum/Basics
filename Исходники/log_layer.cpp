	void LogLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom,
		const vector<Blob<Dtype>*>& top) {
			NeuronLayer<Dtype>::LayerSetUp(bottom, top);
			const Dtype base = this->layer_param_.log_param().base();
			if (base != Dtype(-1)) {
				CHECK_GT(base, 0) << "base must be strictly positive.";
			}
			// If base == -1, interpret the base as e and set log_base = 1 exactly.
			// Otherwise, calculate its log explicitly.
			const Dtype log_base = (base == Dtype(-1)) ? Dtype(1) : log(base);
			CHECK(!_isnanf(log_base))
				<< "NaN result: log(base) = log(" << base << ") = " << log_base;
			CHECK(_finitef(log_base))
				<< "Inf result: log(base) = log(" << base << ") = " << log_base;
			base_scale_ = Dtype(1) / log_base;
			CHECK(!_isnanf(base_scale_))
				<< "NaN result: 1/log(base) = 1/log(" << base << ") = " << base_scale_;
			CHECK(_finitef(base_scale_))
				<< "Inf result: 1/log(base) = 1/log(" << base << ") = " << base_scale_;
			input_scale_ = this->layer_param_.log_param().scale();
			input_shift_ = this->layer_param_.log_param().shift();
			backward_num_scale_ = input_scale_ / log_base;
	}