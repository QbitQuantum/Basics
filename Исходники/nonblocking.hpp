OutputIterator
wait_all(ForwardIterator first, ForwardIterator last, OutputIterator out)
{
  typedef typename std::iterator_traits<ForwardIterator>::difference_type
    difference_type;

  using std::distance;

  difference_type num_outstanding_requests = distance(first, last);

  std::vector<status> results(num_outstanding_requests);
  std::vector<bool> completed(num_outstanding_requests);

  while (num_outstanding_requests > 0) {
    bool all_trivial_requests = true;
    difference_type idx = 0;
    for (ForwardIterator current = first; current != last; ++current, ++idx) {
      if (!completed[idx]) {
        if (optional<status> stat = current->test()) {
          // This outstanding request has been completed. We're done.
          results[idx] = *stat;
          completed[idx] = true;
          --num_outstanding_requests;
          all_trivial_requests = false;
        } else {
          // Check if this request (and all others before it) are "trivial"
          // requests, e.g., they can be represented with a single
          // MPI_Request.
          all_trivial_requests =
            all_trivial_requests
            && !current->m_handler
            && current->m_requests[1] == MPI_REQUEST_NULL;
        }
      }
    }

    // If we have yet to fulfill any requests and all of the requests
    // are trivial (i.e., require only a single MPI_Request to be
    // fulfilled), call MPI_Waitall directly.
    if (all_trivial_requests
        && num_outstanding_requests == (difference_type)results.size()) {
      std::vector<MPI_Request> requests;
      requests.reserve(num_outstanding_requests);
      for (ForwardIterator current = first; current != last; ++current)
        requests.push_back(current->m_requests[0]);

      // Let MPI wait until all of these operations completes.
      std::vector<MPI_Status> stats(num_outstanding_requests);
      BOOST_MPI_CHECK_RESULT(MPI_Waitall,
                             (num_outstanding_requests, &requests[0],
                              &stats[0]));

      for (std::vector<MPI_Status>::iterator i = stats.begin();
           i != stats.end(); ++i, ++out) {
        status stat;
        stat.m_status = *i;
        *out = stat;
      }

      return out;
    }

    all_trivial_requests = false;
  }

  return std::copy(results.begin(), results.end(), out);
}