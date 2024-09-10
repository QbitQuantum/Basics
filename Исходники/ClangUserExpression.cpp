bool
ClangUserExpression::Parse (Stream &error_stream,
                            ExecutionContext &exe_ctx,
                            lldb_private::ExecutionPolicy execution_policy,
                            bool keep_result_in_memory,
                            bool generate_debug_info)
{
    Log *log(lldb_private::GetLogIfAllCategoriesSet (LIBLLDB_LOG_EXPRESSIONS));

    Error err;

    InstallContext(exe_ctx);
    
    if (Target *target = exe_ctx.GetTargetPtr())
    {
        if (PersistentExpressionState *persistent_state = target->GetPersistentExpressionStateForLanguage(lldb::eLanguageTypeC))
        {
            m_result_delegate.RegisterPersistentState(persistent_state);
        }
        else
        {
            error_stream.PutCString ("error: couldn't start parsing (no persistent data)");
            return false;
        }
    }
    else
    {
        error_stream.PutCString ("error: couldn't start parsing (no target)");
        return false;
    }

    ScanContext(exe_ctx, err);

    if (!err.Success())
    {
        error_stream.Printf("warning: %s\n", err.AsCString());
    }

    StreamString m_transformed_stream;

    ////////////////////////////////////
    // Generate the expression
    //

    ApplyObjcCastHack(m_expr_text);
    //ApplyUnicharHack(m_expr_text);

    std::string prefix = m_expr_prefix;
    
    if (ClangModulesDeclVendor *decl_vendor = m_target->GetClangModulesDeclVendor())
    {
        const ClangModulesDeclVendor::ModuleVector &hand_imported_modules = llvm::cast<ClangPersistentVariables>(m_target->GetPersistentExpressionStateForLanguage(lldb::eLanguageTypeC))->GetHandLoadedClangModules();
        ClangModulesDeclVendor::ModuleVector modules_for_macros;
        
        for (ClangModulesDeclVendor::ModuleID module : hand_imported_modules)
        {
            modules_for_macros.push_back(module);
        }

        if (m_target->GetEnableAutoImportClangModules())
        {
            if (StackFrame *frame = exe_ctx.GetFramePtr())
            {
                if (Block *block = frame->GetFrameBlock())
                {
                    SymbolContext sc;
                    
                    block->CalculateSymbolContext(&sc);
                    
                    if (sc.comp_unit)
                    {
                        StreamString error_stream;
                        
                        decl_vendor->AddModulesForCompileUnit(*sc.comp_unit, modules_for_macros, error_stream);
                    }
                }
            }
        }
    }
    
    std::unique_ptr<ExpressionSourceCode> source_code (ExpressionSourceCode::CreateWrapped(prefix.c_str(), m_expr_text.c_str()));
    
    lldb::LanguageType lang_type;

    if (m_in_cplusplus_method)
        lang_type = lldb::eLanguageTypeC_plus_plus;
    else if (m_in_objectivec_method)
        lang_type = lldb::eLanguageTypeObjC;
    else
        lang_type = lldb::eLanguageTypeC;

    if (!source_code->GetText(m_transformed_text, lang_type, m_const_object, m_in_static_method, exe_ctx))
    {
        error_stream.PutCString ("error: couldn't construct expression body");
        return false;
    }

    if (log)
        log->Printf("Parsing the following code:\n%s", m_transformed_text.c_str());

    ////////////////////////////////////
    // Set up the target and compiler
    //

    Target *target = exe_ctx.GetTargetPtr();

    if (!target)
    {
        error_stream.PutCString ("error: invalid target\n");
        return false;
    }

    //////////////////////////
    // Parse the expression
    //

    m_materializer_ap.reset(new Materializer());

    ResetDeclMap(exe_ctx, m_result_delegate, keep_result_in_memory);

    class OnExit
    {
    public:
        typedef std::function <void (void)> Callback;

        OnExit (Callback const &callback) :
            m_callback(callback)
        {
        }

        ~OnExit ()
        {
            m_callback();
        }
    private:
        Callback m_callback;
    };

    OnExit on_exit([this]() { ResetDeclMap(); });

    if (!DeclMap()->WillParse(exe_ctx, m_materializer_ap.get()))
    {
        error_stream.PutCString ("error: current process state is unsuitable for expression parsing\n");

        ResetDeclMap(); // We are being careful here in the case of breakpoint conditions.

        return false;
    }

    Process *process = exe_ctx.GetProcessPtr();
    ExecutionContextScope *exe_scope = process;

    if (!exe_scope)
        exe_scope = exe_ctx.GetTargetPtr();

    ClangExpressionParser parser(exe_scope, *this, generate_debug_info);

    unsigned num_errors = parser.Parse (error_stream);

    if (num_errors)
    {
        error_stream.Printf ("error: %d errors parsing expression\n", num_errors);

        ResetDeclMap(); // We are being careful here in the case of breakpoint conditions.

        return false;
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // Prepare the output of the parser for execution, evaluating it statically if possible
    //

    Error jit_error = parser.PrepareForExecution (m_jit_start_addr,
                                                  m_jit_end_addr,
                                                  m_execution_unit_sp,
                                                  exe_ctx,
                                                  m_can_interpret,
                                                  execution_policy);

    if (generate_debug_info)
    {
        lldb::ModuleSP jit_module_sp ( m_execution_unit_sp->GetJITModule());

        if (jit_module_sp)
        {
            ConstString const_func_name(FunctionName());
            FileSpec jit_file;
            jit_file.GetFilename() = const_func_name;
            jit_module_sp->SetFileSpecAndObjectName (jit_file, ConstString());
            m_jit_module_wp = jit_module_sp;
            target->GetImages().Append(jit_module_sp);
        }
//        lldb_private::ObjectFile *jit_obj_file = jit_module_sp->GetObjectFile();
//        StreamFile strm (stdout, false);
//        if (jit_obj_file)
//        {
//            jit_obj_file->GetSectionList();
//            jit_obj_file->GetSymtab();
//            jit_obj_file->Dump(&strm);
//        }
//        lldb_private::SymbolVendor *jit_sym_vendor = jit_module_sp->GetSymbolVendor();
//        if (jit_sym_vendor)
//        {
//            lldb_private::SymbolContextList sc_list;
//            jit_sym_vendor->FindFunctions(const_func_name, NULL, lldb::eFunctionNameTypeFull, true, false, sc_list);
//            sc_list.Dump(&strm, target);
//            jit_sym_vendor->Dump(&strm);
//        }
    }

    ResetDeclMap(); // Make this go away since we don't need any of its state after parsing.  This also gets rid of any ClangASTImporter::Minions.

    if (jit_error.Success())
    {
        if (process && m_jit_start_addr != LLDB_INVALID_ADDRESS)
            m_jit_process_wp = lldb::ProcessWP(process->shared_from_this());
        return true;
    }
    else
    {
        const char *error_cstr = jit_error.AsCString();
        if (error_cstr && error_cstr[0])
            error_stream.Printf ("error: %s\n", error_cstr);
        else
            error_stream.Printf ("error: expression can't be interpreted or run\n");
        return false;
    }
}