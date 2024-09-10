void
test_skeleton_and_content(const communicator& comm, int root,
                          bool manual_broadcast)
{
    using boost::mpi::skeleton;
    using boost::mpi::content;
    using boost::mpi::get_content;
    using boost::make_counting_iterator;
    using boost::mpi::broadcast;

    int list_size = comm.size() + 7;
    if (comm.rank() == root) {
        // Fill in the seed data
        std::list<int> original_list;
        for (int i = 0; i < list_size; ++i)
            original_list.push_back(i);

        std::cout << "Broadcasting integer list skeleton from root " << root
                  << "...";
        if (manual_broadcast) {
            // Broadcast the skeleton (manually)
            for (int p = 0; p < comm.size(); ++p)
                if (p != root) comm.send(p, 0, skeleton(original_list));
        } else {
            broadcast(comm, skeleton(original_list), root);
        }
        std::cout << "OK." << std::endl;

        // Broadcast the content (manually)
        std::cout << "Broadcasting integer list content from root " << root
                  << "...";
        {
            content c = get_content(original_list);
            for (int p = 0; p < comm.size(); ++p)
                if (p != root) comm.send(p, 1, c);
        }
        std::cout << "OK." << std::endl;

        // Reverse the list, broadcast the content again
        std::reverse(original_list.begin(), original_list.end());
        std::cout << "Broadcasting reversed integer list content from root "
                  << root << "...";
        {
            content c = get_content(original_list);
            for (int p = 0; p < comm.size(); ++p)
                if (p != root) comm.send(p, 2, c);
        }
        std::cout << "OK." << std::endl;
    } else {
        // Allocate some useless data, to try to get the addresses of the
        // list<int>'s used later to be different across processes.
        std::list<int> junk_list(comm.rank() * 3 + 1, 17);

        // Receive the skeleton to build up the transferred list
        std::list<int> transferred_list;
        if (manual_broadcast) {
            comm.recv(root, 0, skeleton(transferred_list));
        } else {
            broadcast(comm, skeleton(transferred_list), root);
        }
        BOOST_CHECK((int)transferred_list.size() == list_size);

        // Receive the content and check it
        comm.recv(root, 1, get_content(transferred_list));
        BOOST_CHECK(std::equal(make_counting_iterator(0),
                               make_counting_iterator(list_size),
                               transferred_list.begin()));

        // Receive the reversed content and check it
        comm.recv(root, 2, get_content(transferred_list));
        BOOST_CHECK(std::equal(make_counting_iterator(0),
                               make_counting_iterator(list_size),
                               transferred_list.rbegin()));
    }

    (comm.barrier)();
}