void test_select_random_access(const Select& select, bit_vector::size_type args, bit_vector::size_type times)
{
    typedef bit_vector::size_type size_type;
    const int s = 20;
    const uint64_t mask = (1<<s)-1;
    int_vector<64> rands(1<<s ,0);
    util::set_random_bits(rands, 17);
    util::all_elements_mod(rands, args);
    for (size_type i=0; i<rands.size(); ++i)
        rands[i] = rands[i]+1;
    size_type cnt=0;
    write_R_output("select","random access","begin",times,cnt);
    for (size_type i=0; i<times; ++i) {
        cnt += select.select(rands[ i&mask ]);
    }
    write_R_output("select","random access","end",times,cnt);
}