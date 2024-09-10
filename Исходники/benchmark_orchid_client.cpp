void counter(orchid::coroutine_handle co,
             orchid::chan<counter_t>& ch,
             orchid::scheduler_group& group,
             std::size_t size) {
    counter_t c;
    counter_t tmp;
    c.total_read = 0;
    c.total_write = 0;
    //printf("total_%d\n",size);
    while(size-- > 0) {
        ch.recv(tmp,co);
        c.total_write += tmp.total_write;
        c.total_read += tmp.total_read;
    }
    cout<<"total_read:"<<c.total_read<<endl;
    cout<<"total_write:"<<c.total_write<<endl;
    group.stop();

}