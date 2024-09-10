bool
AppleObjCRuntime::GetObjectDescription (Stream &strm, Value &value, ExecutionContextScope *exe_scope)
{
    if (!m_read_objc_library)
        return false;
        
    ExecutionContext exe_ctx;
    exe_scope->CalculateExecutionContext(exe_ctx);
    Process *process = exe_ctx.GetProcessPtr();
    if (!process)
        return false;
    
    // We need other parts of the exe_ctx, but the processes have to match.
    assert (m_process == process);
    
    // Get the function address for the print function.
    const Address *function_address = GetPrintForDebuggerAddr();
    if (!function_address)
        return false;
    
    Target *target = exe_ctx.GetTargetPtr();
    if (value.GetClangType())
    {
        clang::QualType value_type = clang::QualType::getFromOpaquePtr (value.GetClangType());
        if (!value_type->isObjCObjectPointerType())
        {
            strm.Printf ("Value doesn't point to an ObjC object.\n");
            return false;
        }
    }
    else 
    {
        // If it is not a pointer, see if we can make it into a pointer.
        ClangASTContext *ast_context = target->GetScratchClangASTContext();
        void *opaque_type_ptr = ast_context->GetBuiltInType_objc_id();
        if (opaque_type_ptr == NULL)
            opaque_type_ptr = ast_context->GetVoidPtrType(false);
        value.SetContext(Value::eContextTypeClangType, opaque_type_ptr);    
    }

    ValueList arg_value_list;
    arg_value_list.PushValue(value);
    
    // This is the return value:
    ClangASTContext *ast_context = target->GetScratchClangASTContext();
    
    void *return_qualtype = ast_context->GetCStringType(true);
    Value ret;
    ret.SetContext(Value::eContextTypeClangType, return_qualtype);
    
    // Now we're ready to call the function:
    ClangFunction func (*exe_ctx.GetBestExecutionContextScope(),
                        ast_context, 
                        return_qualtype, 
                        *function_address, 
                        arg_value_list);

    StreamString error_stream;
    
    lldb::addr_t wrapper_struct_addr = LLDB_INVALID_ADDRESS;
    func.InsertFunction(exe_ctx, wrapper_struct_addr, error_stream);

    bool unwind_on_error = true;
    bool try_all_threads = true;
    bool stop_others = true;
    
    ExecutionResults results = func.ExecuteFunction (exe_ctx, 
                                                     &wrapper_struct_addr, 
                                                     error_stream, 
                                                     stop_others, 
                                                     1000000, 
                                                     try_all_threads, 
                                                     unwind_on_error, 
                                                     ret);
    if (results != eExecutionCompleted)
    {
        strm.Printf("Error evaluating Print Object function: %d.\n", results);
        return false;
    }
       
    addr_t result_ptr = ret.GetScalar().ULongLong(LLDB_INVALID_ADDRESS);
    
    char buf[512];
    size_t cstr_len = 0;    
    size_t full_buffer_len = sizeof (buf) - 1;
    size_t curr_len = full_buffer_len;
    while (curr_len == full_buffer_len)
    {
        Error error;
        curr_len = process->ReadCStringFromMemory(result_ptr + cstr_len, buf, sizeof(buf), error);
        strm.Write (buf, curr_len);
        cstr_len += curr_len;
    }
    return cstr_len > 0;
}