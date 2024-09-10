    mask_type init_numa_node_affinity_mask(
        std::size_t num_thread
      , bool numa_sensitive
        )
    { // {{{
        std::size_t num_of_cores = hardware_concurrency();
        UCHAR affinity = UCHAR(num_thread % num_of_cores);

        ULONG numa_nodes = 1;
        if (GetNumaHighestNodeNumber(&numa_nodes))
            ++numa_nodes;

        ULONGLONG mask = 0;
        if (numa_sensitive) {
            UCHAR numa_node = affinity % numa_nodes;
            if (!GetNumaNodeProcessorMask(numa_node, &mask))
            {
                HPX_THROW_EXCEPTION(kernel_error
                  , "hpx::threads::windows_topology::init_numa_node_affinity_mask"
                  , boost::str(boost::format(
                        "failed to initialize NUMA node affinity mask for "
                        "thread %1%")
                        % num_thread));
            }
            return static_cast<mask_type>(mask);
        }

        UCHAR numa_node = UCHAR(get_numa_node_number(num_thread));
        if (!GetNumaNodeProcessorMask(numa_node, &mask))
        {
            HPX_THROW_EXCEPTION(kernel_error
              , "hpx::threads::windows_topology::init_numa_node_affinity_mask"
              , boost::str(boost::format(
                    "failed to initialize NUMA node affinity mask for "
                    "thread %1%")
                    % num_thread));
        }

        return static_cast<mask_type>(mask);
    } // }}}