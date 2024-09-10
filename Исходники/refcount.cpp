uint32_t get_next_shared_ptr_id() {
    shared_ptr_list_lock.lock();
    shared_ptr_is_alive.add(true);
    uint32_t ret = shared_ptr_is_alive.length() - 1;
    shared_ptr_list_lock.unlock();
    return ret;
}