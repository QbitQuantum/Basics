    size_t operator()(){
        struct _{ static void  retrieve_from_cache(self_type* _this, size_t thread_index){
            parameter_pack& p = _this->m_parameter_pack;
            access_sequence_type::iterator const begin_it =_this->m_access_sequence.begin()+ thread_index * _this->per_thread_sample_size;
            access_sequence_type::iterator const end_it = begin_it +  _this->per_thread_sample_size;

            _this->m_barrier.wait();
            tbb::tick_count start = tbb::tick_count::now();

            size_t local_loops_count =0;
            do {
                size_t part_of_the_sample_so_far = (local_loops_count * p.time_check_granularity_ops) % _this->per_thread_sample_size;
                access_sequence_type::iterator const iteration_begin_it = begin_it + part_of_the_sample_so_far;
                access_sequence_type::iterator const iteration_end_it = iteration_begin_it +
                        (std::min)(p.time_check_granularity_ops, _this->per_thread_sample_size - part_of_the_sample_so_far);

                for (access_sequence_type::iterator it = iteration_begin_it; it < iteration_end_it; ++it){
                    typename cache_type::handle h = _this->m_cache(*it);
                    micro_benchmarking::utils::busy_wait(p.time_of_item_use_usec);
                    micro_benchmarking::utils::disable_elimination(h.value());
                }
                ++local_loops_count;
            }while((tbb::tick_count::now()-start).seconds() < p.time_window_sec);
            _this->loops_count+=local_loops_count;
        }};
        m_barrier.initialize(m_parameter_pack.threads_number);

        NativeParallelFor(m_parameter_pack.threads_number,std::bind1st(std::ptr_fun(&_::retrieve_from_cache),this));

        return loops_count * m_parameter_pack.time_check_granularity_ops;
    }