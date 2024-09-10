static duk_ret_t Line_Distance_Line_float(duk_context* ctx)
{
    Line* thisObj = GetThisValueObject<Line>(ctx, Line_ID);
    Line& other = *GetCheckedValueObject<Line>(ctx, 0, Line_ID);
    float d = (float)duk_require_number(ctx, 1);
    float ret = thisObj->Distance(other, d);
    duk_push_number(ctx, ret);
    return 1;
}