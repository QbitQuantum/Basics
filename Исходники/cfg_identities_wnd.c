void
get_ctrl_row_metrics(struct ctrl_row_dimensions * dim, HWND hw_lbl, HWND hw_ctl) {

    assert(hw_lbl);
    assert(hw_ctl);

    GetWindowRect(hw_lbl, &dim->label);
    GetWindowRect(hw_ctl, &dim->control);

    UnionRect(&dim->enclosure, &dim->label, &dim->control);
    OffsetRect(&dim->label,
               -dim->enclosure.left,
               -dim->enclosure.top);
    OffsetRect(&dim->control,
               -dim->enclosure.left,
               -dim->enclosure.top);
    OffsetRect(&dim->enclosure,
               -dim->enclosure.left,
               -dim->enclosure.top);
}