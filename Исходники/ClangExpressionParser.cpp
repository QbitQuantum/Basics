unsigned
ClangExpressionParser::Parse (Stream &stream)
{
    TextDiagnosticBuffer *diag_buf = static_cast<TextDiagnosticBuffer*>(m_compiler->getDiagnostics().getClient());

    diag_buf->FlushDiagnostics (m_compiler->getDiagnostics());

    const char *expr_text = m_expr.Text();

    clang::SourceManager &SourceMgr = m_compiler->getSourceManager();
    bool created_main_file = false;
    if (m_compiler->getCodeGenOpts().getDebugInfo() == CodeGenOptions::FullDebugInfo)
    {
        std::string temp_source_path;

        FileSpec tmpdir_file_spec;
        if (HostInfo::GetLLDBPath(lldb::ePathTypeLLDBTempSystemDir, tmpdir_file_spec))
        {
            tmpdir_file_spec.AppendPathComponent("expr.XXXXXX");
            temp_source_path = std::move(tmpdir_file_spec.GetPath());
        }
        else
        {
            temp_source_path = "/tmp/expr.XXXXXX";
        }

        if (mktemp(&temp_source_path[0]))
        {
            lldb_private::File file (temp_source_path.c_str(),
                                     File::eOpenOptionWrite | File::eOpenOptionCanCreateNewOnly,
                                     lldb::eFilePermissionsFileDefault);
            const size_t expr_text_len = strlen(expr_text);
            size_t bytes_written = expr_text_len;
            if (file.Write(expr_text, bytes_written).Success())
            {
                if (bytes_written == expr_text_len)
                {
                    file.Close();
                    SourceMgr.setMainFileID(SourceMgr.createFileID(
                        m_file_manager->getFile(temp_source_path),
                        SourceLocation(), SrcMgr::C_User));
                    created_main_file = true;
                }
            }
        }
    }

    if (!created_main_file)
    {
        std::unique_ptr<MemoryBuffer> memory_buffer = MemoryBuffer::getMemBufferCopy(expr_text, __FUNCTION__);
        SourceMgr.setMainFileID(SourceMgr.createFileID(std::move(memory_buffer)));
    }

    diag_buf->BeginSourceFile(m_compiler->getLangOpts(), &m_compiler->getPreprocessor());

    ASTConsumer *ast_transformer = m_expr.ASTTransformer(m_code_generator.get());

    if (ast_transformer)
        ParseAST(m_compiler->getPreprocessor(), ast_transformer, m_compiler->getASTContext());
    else
        ParseAST(m_compiler->getPreprocessor(), m_code_generator.get(), m_compiler->getASTContext());

    diag_buf->EndSourceFile();

    TextDiagnosticBuffer::const_iterator diag_iterator;

    int num_errors = 0;

    for (diag_iterator = diag_buf->warn_begin();
         diag_iterator != diag_buf->warn_end();
         ++diag_iterator)
        stream.Printf("warning: %s\n", (*diag_iterator).second.c_str());

    num_errors = 0;

    for (diag_iterator = diag_buf->err_begin();
         diag_iterator != diag_buf->err_end();
         ++diag_iterator)
    {
        num_errors++;
        stream.Printf("error: %s\n", (*diag_iterator).second.c_str());
    }

    for (diag_iterator = diag_buf->note_begin();
         diag_iterator != diag_buf->note_end();
         ++diag_iterator)
        stream.Printf("note: %s\n", (*diag_iterator).second.c_str());

    if (!num_errors)
    {
        if (m_expr.DeclMap() && !m_expr.DeclMap()->ResolveUnknownTypes())
        {
            stream.Printf("error: Couldn't infer the type of a variable\n");
            num_errors++;
        }
    }

    return num_errors;
}