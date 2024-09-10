FXWindow*
MFXAddEditTypedTable::getControlForItem(FXint r, FXint c) {
    register FXTableItem* item = cells[r * ncols + c];
    if (item == NULL) {
        return 0;
//         cells[r * ncols + c] = item = createItem("", NULL, NULL);
//         if (isItemSelected(r, c)) {
//             item->setSelected(FALSE);
//         }
    }
    delete editor;
    editor = NULL;
    switch (getCellType(c)) {
        case CT_UNDEFINED:
        case CT_STRING: {
            register FXTextField* field;
            register FXuint justify = 0;
            field = new FXTextField(this, 1, NULL, 0, TEXTFIELD_ENTER_ONLY, 0, 0, 0, 0, getMarginLeft(), getMarginRight(), getMarginTop(), getMarginBottom());
            // !!! if(state&LEFT) justify|=JUSTIFY_LEFT;
            // !!! if(state&RIGHT) justify|=JUSTIFY_RIGHT;
            // !!! if(state&TOP) justify|=JUSTIFY_TOP;
            // !!! if(state&BOTTOM) justify|=JUSTIFY_BOTTOM;
            field->create();
            field->setJustify(justify);
            field->setFont(getFont());
            field->setBackColor(getBackColor());
            field->setTextColor(getTextColor());
            field->setSelBackColor(getSelBackColor());
            field->setSelTextColor(getSelTextColor());
            field->setText(item->getText());
            field->selectAll();
            return field;
        }
        case CT_REAL:
//        return myNumberEditor;
        case CT_INT: {
            register FXRealSpinDial* field;
            //register FXuint justify=0;
            field = new FXRealSpinDial(this, 1, NULL, 0, TEXTFIELD_ENTER_ONLY, 0, 0, 0, 0, getMarginLeft(), getMarginRight(), getMarginTop(), getMarginBottom());
            // !!! if(state&LEFT) justify|=JUSTIFY_LEFT;
            // !!! if(state&RIGHT) justify|=JUSTIFY_RIGHT;
            // !!! if(state&TOP) justify|=JUSTIFY_TOP;
            // !!! if(state&BOTTOM) justify|=JUSTIFY_BOTTOM;
            field->create();
//            field->setJustify(justify);
            field->setFont(getFont());
            field->setBackColor(getBackColor());
            field->setTextColor(getTextColor());
            field->setSelBackColor(getSelBackColor());
            field->setSelTextColor(getSelTextColor());
            NumberCellParams p = getNumberCellParams(c);
            if (p.format != "undefined") {
                field->setFormatString((char*) p.format.c_str());
                field->setIncrements(p.steps1, p.steps2, p.steps3);
                field->setRange(p.min, p.max);
            }
            try {
                if (getCellType(c) == CT_REAL) {
                    field->setValue(TplConvert::_2SUMOReal(item->getText().text()));
                } else {
                    field->setValue(TplConvert::_2int(item->getText().text()));
                }
            } catch (NumberFormatException&) {
                field->setValue(0);
            }
            field->selectAll();
            return field;
        }
        case CT_BOOL:
//        return myBoolEditor;
        case CT_ENUM:
//        return myEnumEditor;
        default:
            throw 1;
    }
}