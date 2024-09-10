lts_file_t lts_get_template(lts_file_t file){
    file=SYSTEM(file);
    lts_file_t lts=(lts_file_t)HREmallocZero(hre_heap,system_size);
    lts->init_mode=file->init_mode;
    lts->edge_owner=file->edge_owner;
    lts->src_mode=file->src_mode;
    lts->dst_mode=file->dst_mode;
    return USER(lts);
}