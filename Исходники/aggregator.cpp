    void Aggregator::StartThread()
    {
        int id = thread_counter_++;
        VectorClock flush_vector(num_trainers_);
        VectorClock clock_vector(num_trainers_);
        DeltaPool* delta_pool = delta_pools_[id];

        barrier_->Wait();
        
        integer_t table, row, col;
        void* delta;
        zmq::socket_t* socket = ZMQUtil::CreateSocket();

        while (delta_pool->Pop(table, row, col, delta))
        {
            switch (static_cast<DeltaType>(row))
            {
            case DeltaType::Flush:
                if (flush_vector.Update(col))
                {
                    Send(id, socket);
                    if (barrier_->Wait())
                    {
                        for (auto& table : tables_)
                        {
                            table->Clear();
                        }
                    }
                    barrier_->Wait();
                }
                break;
            case DeltaType::Clock:
                if (clock_vector.Update(col))
                {
                    if (barrier_->Wait())
                    {
                        Clock(socket);
                    }
                    barrier_->Wait();
                }
                break;
            default: // the general delta type, add update to aggregator table
                assert(row >= 0);
                tables_[table]->GetRow(row)->Add(col, delta);
            }
        }
        delete socket;
    }