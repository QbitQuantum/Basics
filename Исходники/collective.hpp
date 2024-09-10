static inline
void PrefixSumHypercube(
    Group& net, T& value, BinarySumOp sum_op = BinarySumOp()) {
    T total_sum = value;

    static const bool debug = false;

    for (size_t d = 1; d < net.num_hosts(); d <<= 1)
    {
        // communication peer for this round (hypercube dimension)
        size_t peer = net.my_host_rank() ^ d;

        // Send total sum of this hypercube to worker with id = id XOR d
        if (peer < net.num_hosts()) {
            net.SendTo(peer, total_sum);
            sLOG << "PREFIX_SUM: host" << net.my_host_rank()
                 << ": sending to peer" << peer;
        }

        // Receive total sum of smaller hypercube from worker with id = id XOR d
        T recv_data;
        if (peer < net.num_hosts()) {
            net.ReceiveFrom(peer, &recv_data);
            // The order of addition is important. The total sum of the smaller
            // hypercube always comes first.
            if (net.my_host_rank() & d)
                total_sum = sum_op(recv_data, total_sum);
            else
                total_sum = sum_op(total_sum, recv_data);
            // Variable 'value' represents the prefix sum of this worker
            if (net.my_host_rank() & d)
                // The order of addition is respected the same way as above.
                value = sum_op(recv_data, value);
            sLOG << "PREFIX_SUM: host" << net.my_host_rank()
                 << ": received from peer" << peer;
        }
    }

    sLOG << "PREFIX_SUM: host" << net.my_host_rank() << ": done";
}