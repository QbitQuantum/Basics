void DBObjTable::DeleteField(DBObjTableField *delField) {
    DBInt i, recID, fieldID;
    DBObjRecord *record;
    DBObjTableField *field;
    unsigned char *data;

    for (fieldID = 0; fieldID < FieldPTR->ItemNum(); ++fieldID) {
        field = FieldPTR->Item(fieldID);
        if (field->StartByte() > delField->StartByte())
            field->StartByte(field->StartByte() - delField->Length());
    }
    for (recID = 0; recID < ItemNum(); ++recID) {
        record = Item(recID);
        data = (unsigned char *) record->Data() + delField->StartByte();
        for (i = 0; i < RecordLengthVAR - delField->StartByte() - delField->Length(); ++i)
            data[i] = data[i + delField->Length()];
        record->Realloc(RecordLengthVAR - delField->Length());
    }
    FieldPTR->Remove(delField);
    RecordLengthVAR -= delField->Length();
    delete delField;
}