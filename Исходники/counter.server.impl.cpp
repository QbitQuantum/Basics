        // helper routines to accelerate learning
        int counter_service_impl::get_learn_state(decree start, const blob& learn_request, __out_param learn_state& state)
        {
            ::dsn::binary_writer writer;

            zauto_lock l(_lock);

            int magic = 0xdeadbeef;
            writer.write(magic);

            writer.write(_last_committed_decree.load());

            dassert(_last_committed_decree >= 0, "");

            int count = static_cast<int>(_counters.size());
            writer.write(count);

            for (auto it = _counters.begin(); it != _counters.end(); it++)
            {
                writer.write(it->first);
                writer.write(it->second);
            }

            auto bb = writer.get_buffer();
            auto buf = bb.buffer();

            state.meta.push_back(blob(buf, static_cast<int>(bb.data() - bb.buffer().get()), bb.length()));

            return ERR_SUCCESS;
        }