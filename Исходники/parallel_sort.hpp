  void sort() {
    sort_arg_t *thread_data;

    //          struct timeval t1, t2;
    //          gettimeofday(&t1, nullptr);

    if (thread_count == 1) {
      std::sort(data->begin(), data->end());
    }
    // divide input data on threads for sorting
    else {
      pthread_t *threads = new pthread_t[thread_count];
      thread_data = new sort_arg_t[thread_count];

      size_t begin = 0;
      size_t per_thread = data->size() / thread_count;
      size_t remainder = data->size() - per_thread * thread_count;

      for (int i = 0; i < thread_count; i++) {
        size_t size = per_thread + (i < remainder ? 1 : 0);
        thread_data[i].data = data;
        thread_data[i].begin = begin;
        thread_data[i].end = begin + size;
        begin += size;
      }

      for (int i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], nullptr, thunk<ParallelSort, &ParallelSort::sort_thread>, new std::pair<void *, void *>(this, &thread_data[i]));
      }

      for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], nullptr);
      }

      delete threads;
    }

    //          gettimeofday(&t2, nullptr);
    //          printf("%f,", t2.tv_sec + (double)t2.tv_usec / 1000000 - t1.tv_sec - (double)t1.tv_usec / 1000000);
    //          gettimeofday(&t1, nullptr);

    if (thread_count == 1) {

    }
    // uses a single 2-way merge to merge the two sorted parts
    else if (thread_count == 2) {
      merge_arg_t a, b;
      a.data = thread_data[0].data;
      a.begin = thread_data[0].begin;
      a.end = thread_data[0].end;
      a.delete_data_when_done = false;

      b.data = thread_data[1].data;
      b.begin = thread_data[1].begin;
      b.end = thread_data[1].end;
      b.delete_data_when_done = false;

      std::vector<T> *out = ParallelSort::merge_sorted(a, b);
      data->swap(*out);
      delete out;
    }

    // uses a single n-way merge to merge the sorted parts.
    // this is about 2x slower than the solution below
    //          else {
    //                  std::vector<T> *out = new std::vector<T>();
    //                  merge_data_t d;
    //
    //                  std::priority_queue<merge_data_t> heap;
    //
    //                  for (int i = 0; i < thread_count; i++) {
    //                          d.pos = thread_data[i].begin;
    //                          d.value = (*(thread_data[i].data))[d.pos];
    //                          d.slice = i;
    //                          heap.push(d);
    //                  }
    //
    //                  while (heap.size() > 0) {
    //                          d = heap.top();
    //                          heap.pop();
    //
    //                          out->push_back(d.value);
    //
    //                          d.pos++;
    //                          if (d.pos < thread_data[d.slice].end) {
    //                                  d.value = (*(thread_data[d.slice].data))[d.pos];
    //                                  heap.push(d);
    //                          }
    //                  }
    //                  data->swap(*out);
    //                  delete out;
    //          }

    // uses threaded 2-way merges to merge pairs of sorted parts until
    // only one big sorted part is left
    else {
      pthread_mutex_init(&parts_mutex, nullptr);
      pthread_mutex_init(&parts_exist_mutex, nullptr);

      size_t merge_thread_count = thread_count / 2;

      if (merge_thread_count < 2) {
        merge_thread_count = 2;
      }

      remaining_parts = 0;

      for (int i = 0; i < thread_count; i++) {
        merge_arg_t a;
        a.data = thread_data[i].data;
        a.begin = thread_data[i].begin;
        a.end = thread_data[i].end;
        a.delete_data_when_done = false;
        pending_parts.push(a);
        remaining_parts++;
      }

      pthread_mutex_lock(&parts_exist_mutex);

      pthread_t *threads = new pthread_t[merge_thread_count];

      for (int i = 0; i < merge_thread_count; i++) {
        pthread_create(&threads[i], nullptr, thunk<ParallelSort, &ParallelSort::merge_thread>, new std::pair<void *, void *>(this, NULL));
      }

      for (int i = 0; i < merge_thread_count; i++) {
        pthread_join(threads[i], nullptr);
      }

      delete threads;
      pthread_mutex_destroy(&parts_mutex);
      pthread_mutex_destroy(&parts_exist_mutex);

      merge_arg_t res = pending_parts.front();
      data->swap(*res.data);
      delete res.data;
    }

    //          gettimeofday(&t2, nullptr);
    //          printf("%f\n", t2.tv_sec + (double)t2.tv_usec / 1000000 - t1.tv_sec - (double)t1.tv_usec / 1000000);

    if (thread_count > 1) {
      delete thread_data;
    }
  }