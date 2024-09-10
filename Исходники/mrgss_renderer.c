void mrgss_renderer_update_sprites_order(mrb_state *mrb, mrb_value drawables, mrgss_renderer *renderer){
    if (renderer->needsSorting) {
        struct RArray *children = DATA_PTR(drawables);
        qsort_s(children, RARRAY_LEN(drawables), sizeof(mrb_value), mrgss_renderer_vertex_compare, mrb);
    }
}