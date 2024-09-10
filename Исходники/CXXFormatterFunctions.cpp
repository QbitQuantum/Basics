bool
lldb_private::formatters::ExtractSummaryFromObjCExpression (ValueObject &valobj,
                                                            const char* target_type,
                                                            const char* selector,
                                                            Stream &stream)
{
    if (!target_type || !*target_type)
        return false;
    if (!selector || !*selector)
        return false;
    StreamString expr;
    expr.Printf("(%s)[(id)0x%" PRIx64 " %s]",target_type,valobj.GetPointerValue(),selector);
    ExecutionContext exe_ctx (valobj.GetExecutionContextRef());
    lldb::ValueObjectSP result_sp;
    Target* target = exe_ctx.GetTargetPtr();
    StackFrame* stack_frame = GetViableFrame(exe_ctx);
    if (!target || !stack_frame)
        return false;
    
    EvaluateExpressionOptions options;
    options.SetCoerceToId(false);
    options.SetUnwindOnError(true);
    options.SetKeepInMemory(true);
    options.SetUseDynamic(lldb::eDynamicCanRunTarget);
    
    target->EvaluateExpression(expr.GetData(),
                               stack_frame,
                               result_sp,
                               options);
    if (!result_sp)
        return false;
    stream.Printf("%s",result_sp->GetSummaryAsCString());
    return true;
}