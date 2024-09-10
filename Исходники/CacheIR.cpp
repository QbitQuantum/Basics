bool
GetPropIRGenerator::tryAttachStringChar(ValOperandId valId, ValOperandId indexId)
{
    MOZ_ASSERT(idVal_.isInt32());

    if (!val_.isString())
        return false;

    JSString* str = val_.toString();
    int32_t index = idVal_.toInt32();
    if (size_t(index) >= str->length() ||
        !str->isLinear() ||
        str->asLinear().latin1OrTwoByteChar(index) >= StaticStrings::UNIT_STATIC_LIMIT)
    {
        return false;
    }

    StringOperandId strId = writer.guardIsString(valId);
    Int32OperandId int32IndexId = writer.guardIsInt32(indexId);
    writer.loadStringCharResult(strId, int32IndexId);
    writer.returnFromIC();
    return true;
}