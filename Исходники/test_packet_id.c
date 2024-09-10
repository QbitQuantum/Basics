static int
test_packet_id_write_teardown(void **state) {
    free(*state);
    return 0;
}