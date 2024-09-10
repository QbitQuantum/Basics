void create_leval_frame(Widget but, void *data)
{
    Quark *gr = (Quark *) data;

    if (!gr) {
        return;
    }
    
    set_wait_cursor();

    levalui.gr = gr;

    if (levalui.top == NULL) {
        int i;
        Widget fr, rc1;
        int nscols;
        char *rows[MAX_SET_COLS][1];
        char **cells[MAX_SET_COLS];
        char *rowlabels[MAX_SET_COLS];
        int column_widths[1] = {50};
        int column_maxlengths[1] = {256};
        Grace *grace = grace_from_quark(gr);

        levalui.top = CreateDialogForm(app_shell, "Load & evaluate");

        fr = CreateFrame(levalui.top, "Parameter mesh ($t)");
        AddDialogFormChild(levalui.top, fr);
        rc1 = CreateHContainer(fr);
        levalui.start = CreateTextItem(rc1, 10, "Start at:");
        levalui.stop = CreateTextItem(rc1, 10, "Stop at:");
        levalui.npts = CreateTextItem(rc1, 6, "Length:");

        levalui.set_type = CreateSetTypeChoice(levalui.top, "Set type:");
        AddDialogFormChild(levalui.top, levalui.set_type->menu);
        AddOptionChoiceCB(levalui.set_type, set_type_cb, (void *) &levalui);
        
        nscols = 2;
        for (i = 0; i < nscols; i++) {
            rowlabels[i] = copy_string(NULL, dataset_col_name(grace, i));
            rowlabels[i] = concat_strings(rowlabels[i], " = ");
            if (i == 0) {
                rows[i][0] = "$t";
            } else {
                rows[i][0] = "";
            }
            cells[i] = &rows[i][0];
        }

        levalui.mw = CreateTable("mw", levalui.top,
                                 nscols, 1,
                                 MAX_SET_COLS, 1);
        TableLevalInit(levalui.mw);
        TableSetColWidths(levalui.mw, column_widths);
        TableSetColMaxlengths(levalui.mw, column_maxlengths);
        TableSetRowLabels(levalui.mw, rowlabels);
        TableSetDefaultRowLabelWidth(levalui.mw, 6);
        TableSetDefaultRowLabelAlignment(levalui.mw, ALIGN_CENTER);
        TableSetCells(levalui.mw, cells);
        TableUpdateVisibleRowsCols(levalui.mw);

        AddTableLeaveCellCB(levalui.mw, leaveCB, &levalui);

        CreateAACDialog(levalui.top, levalui.mw, leval_aac_cb, &levalui);
    }
    
    RaiseWindow(GetParent(levalui.top));
    unset_wait_cursor();
}