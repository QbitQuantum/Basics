static void
PrDoDirective (
    char                    *DirectiveToken,
    char                    **Next)
{
    char                    *Token = AslGbl_MainTokenBuffer;
    char                    *Token2 = NULL;
    char                    *End;
    UINT64                  Value;
    ACPI_SIZE               TokenOffset;
    int                     Directive;
    ACPI_STATUS             Status;


    if (!DirectiveToken)
    {
        goto SyntaxError;
    }

    Directive = PrMatchDirective (DirectiveToken);
    if (Directive == ASL_DIRECTIVE_NOT_FOUND)
    {
        PrError (ASL_ERROR, ASL_MSG_UNKNOWN_DIRECTIVE,
            THIS_TOKEN_OFFSET (DirectiveToken));

        DbgPrint (ASL_PARSE_OUTPUT, PR_PREFIX_ID
            "#%s: Unknown directive\n",
            AslGbl_CurrentLineNumber, DirectiveToken);
        return;
    }

    /*
     * Emit a line directive into the preprocessor file (.pre) after
     * every matched directive. This is passed through to the compiler
     * so that error/warning messages are kept in sync with the
     * original source file.
     */
    FlPrintFile (ASL_FILE_PREPROCESSOR, "#line %u \"%s\" // #%s\n",
        AslGbl_CurrentLineNumber, AslGbl_Files[ASL_FILE_INPUT].Filename,
        AslGbl_DirectiveInfo[Directive].Name);

    /*
     * If we are currently ignoring this block and we encounter a #else or
     * #elif, we must ignore their blocks also if the parent block is also
     * being ignored.
     */
    if (AslGbl_IgnoringThisCodeBlock)
    {
        switch (Directive)
        {
        case PR_DIRECTIVE_ELSE:
        case PR_DIRECTIVE_ELIF:

            if (AslGbl_DirectiveStack &&
                AslGbl_DirectiveStack->IgnoringThisCodeBlock)
            {
                PrDbgPrint ("Ignoring", AslGbl_DirectiveInfo[Directive].Name);
                return;
            }
            break;

        default:
            break;
        }
    }

    /*
     * Need to always check for #else, #elif, #endif regardless of
     * whether we are ignoring the current code block, since these
     * are conditional code block terminators.
     */
    switch (Directive)
    {
    case PR_DIRECTIVE_ELSE:

        AslGbl_IgnoringThisCodeBlock = !(AslGbl_IgnoringThisCodeBlock);
        PrDbgPrint ("Executing", "else block");
        return;

    case PR_DIRECTIVE_ELIF:

        AslGbl_IgnoringThisCodeBlock = !(AslGbl_IgnoringThisCodeBlock);
        Directive = PR_DIRECTIVE_IF;

        if (AslGbl_IgnoringThisCodeBlock == TRUE)
        {
            /* Not executing the ELSE part -- all done here */
            PrDbgPrint ("Ignoring", "elif block");
            return;
        }

        /*
         * After this, we will execute the IF part further below.
         * First, however, pop off the original #if directive.
         */
        if (ACPI_FAILURE (PrPopDirective ()))
        {
            PrError (ASL_ERROR, ASL_MSG_COMPILER_INTERNAL,
                THIS_TOKEN_OFFSET (DirectiveToken));
        }

        PrDbgPrint ("Executing", "elif block");
        break;

    case PR_DIRECTIVE_ENDIF:

        PrDbgPrint ("Executing", "endif");

        /* Pop the owning #if/#ifdef/#ifndef */

        if (ACPI_FAILURE (PrPopDirective ()))
        {
            PrError (ASL_ERROR, ASL_MSG_ENDIF_MISMATCH,
                THIS_TOKEN_OFFSET (DirectiveToken));
        }
        return;

    default:
        break;
    }

    /* Most directives have at least one argument */

    if (AslGbl_DirectiveInfo[Directive].ArgCount >= 1)
    {
        Token = PrGetNextToken (NULL, PR_TOKEN_SEPARATORS, Next);
        if (!Token)
        {
            goto SyntaxError;
        }
    }

    if (AslGbl_DirectiveInfo[Directive].ArgCount >= 2)
    {
        Token2 = PrGetNextToken (NULL, PR_TOKEN_SEPARATORS, Next);
        if (!Token2)
        {
            goto SyntaxError;
        }
    }

    /*
     * At this point, if we are ignoring the current code block,
     * do not process any more directives (i.e., ignore them also.)
     * For "if" style directives, open/push a new block anyway. We
     * must do this to keep track of #endif directives
     */
    if (AslGbl_IgnoringThisCodeBlock)
    {
        switch (Directive)
        {
        case PR_DIRECTIVE_IF:
        case PR_DIRECTIVE_IFDEF:
        case PR_DIRECTIVE_IFNDEF:

            PrPushDirective (Directive, Token);
            PrDbgPrint ("Ignoring", AslGbl_DirectiveInfo[Directive].Name);
            break;

        default:
            break;
        }

        return;
    }

    /*
     * Execute the directive
     */
    PrDbgPrint ("Begin execution", AslGbl_DirectiveInfo[Directive].Name);

    switch (Directive)
    {
    case PR_DIRECTIVE_IF:

        TokenOffset = Token - AslGbl_MainTokenBuffer;

        /* Need to expand #define macros in the expression string first */

        Status = PrResolveIntegerExpression (
            &AslGbl_CurrentLineBuffer[TokenOffset-1], &Value);
        if (ACPI_FAILURE (Status))
        {
            return;
        }

        PrPushDirective (Directive, Token);
        if (!Value)
        {
            AslGbl_IgnoringThisCodeBlock = TRUE;
        }

        DbgPrint (ASL_PARSE_OUTPUT, PR_PREFIX_ID
            "Resolved #if: %8.8X%8.8X %s\n",
            AslGbl_CurrentLineNumber, ACPI_FORMAT_UINT64 (Value),
            AslGbl_IgnoringThisCodeBlock ? "<Skipping Block>" : "<Executing Block>");
        break;

    case PR_DIRECTIVE_IFDEF:

        PrPushDirective (Directive, Token);
        if (!PrMatchDefine (Token))
        {
            AslGbl_IgnoringThisCodeBlock = TRUE;
        }

        PrDbgPrint ("Evaluated", "ifdef");
        break;

    case PR_DIRECTIVE_IFNDEF:

        PrPushDirective (Directive, Token);
        if (PrMatchDefine (Token))
        {
            AslGbl_IgnoringThisCodeBlock = TRUE;
        }

        PrDbgPrint ("Evaluated", "ifndef");
        break;

    case PR_DIRECTIVE_DEFINE:
        /*
         * By definition, if first char after the name is a paren,
         * this is a function macro.
         */
        TokenOffset = Token - AslGbl_MainTokenBuffer + strlen (Token);
        if (*(&AslGbl_CurrentLineBuffer[TokenOffset]) == '(')
        {
#ifndef MACROS_SUPPORTED
            AcpiOsPrintf (
                "%s ERROR - line %u: #define macros are not supported yet\n",
                AslGbl_CurrentLineBuffer, AslGbl_LogicalLineNumber);
            exit(1);
#else
            PrAddMacro (Token, Next);
#endif
        }
        else
        {
            /* Use the remainder of the line for the #define */

            Token2 = *Next;
            if (Token2)
            {
                while ((*Token2 == ' ') || (*Token2 == '\t'))
                {
                    Token2++;
                }

                End = Token2;
                while (*End != '\n')
                {
                    End++;
                }

                *End = 0;
            }
            else
            {
                Token2 = "";
            }
#if 0
            Token2 = PrGetNextToken (NULL, "\n", /*PR_TOKEN_SEPARATORS,*/ Next);
            if (!Token2)
            {
                Token2 = "";
            }
#endif
            DbgPrint (ASL_PARSE_OUTPUT, PR_PREFIX_ID
                "New #define: %s->%s\n",
                AslGbl_LogicalLineNumber, Token, Token2);

            PrAddDefine (Token, Token2, FALSE);
        }
        break;

    case PR_DIRECTIVE_ERROR:

        /* Note: No macro expansion */

        PrError (ASL_ERROR, ASL_MSG_ERROR_DIRECTIVE,
            THIS_TOKEN_OFFSET (Token));

        AslGbl_SourceLine = 0;
        AslGbl_NextError = AslGbl_ErrorLog;
        CmCleanupAndExit ();
        exit(1);

    case PR_DIRECTIVE_INCLUDE:

        Token = PrGetNextToken (NULL, " \"<>", Next);
        if (!Token)
        {
            goto SyntaxError;
        }

        DbgPrint (ASL_PARSE_OUTPUT, PR_PREFIX_ID
            "Start #include file \"%s\"\n", AslGbl_CurrentLineNumber,
            Token, AslGbl_CurrentLineNumber);

        PrDoIncludeFile (Token);
        break;

    case PR_DIRECTIVE_INCLUDEBUFFER:

        Token = PrGetNextToken (NULL, " \"<>", Next);
        if (!Token)
        {
            goto SyntaxError;
        }

        Token2 = PrGetNextToken (NULL, PR_TOKEN_SEPARATORS, Next);
        if (!Token2)
        {
            goto SyntaxError;
        }

        DbgPrint (ASL_PARSE_OUTPUT, PR_PREFIX_ID
            "Start #includebuffer input from file \"%s\", buffer name %s\n",
            AslGbl_CurrentLineNumber, Token, Token2);

        PrDoIncludeBuffer (Token, Token2);
        break;

    case PR_DIRECTIVE_LINE:

        TokenOffset = Token - AslGbl_MainTokenBuffer;

        Status = PrResolveIntegerExpression (
            &AslGbl_CurrentLineBuffer[TokenOffset-1], &Value);
        if (ACPI_FAILURE (Status))
        {
            return;
        }

        DbgPrint (ASL_PARSE_OUTPUT, PR_PREFIX_ID
            "User #line invocation %s\n", AslGbl_CurrentLineNumber,
            Token);

        AslGbl_CurrentLineNumber = (UINT32) Value;

        /* Emit #line into the preprocessor file */

        FlPrintFile (ASL_FILE_PREPROCESSOR, "#line %u \"%s\"\n",
            AslGbl_CurrentLineNumber, AslGbl_Files[ASL_FILE_INPUT].Filename);
        break;

    case PR_DIRECTIVE_PRAGMA:

        if (!strcmp (Token, "disable"))
        {
            Token = PrGetNextToken (NULL, PR_TOKEN_SEPARATORS, Next);
            if (!Token)
            {
                goto SyntaxError;
            }

            TokenOffset = Token - AslGbl_MainTokenBuffer;
            AslDisableException (&AslGbl_CurrentLineBuffer[TokenOffset]);
        }
        else if (!strcmp (Token, "message"))
        {
            Token = PrGetNextToken (NULL, PR_TOKEN_SEPARATORS, Next);
            if (!Token)
            {
                goto SyntaxError;
            }

            TokenOffset = Token - AslGbl_MainTokenBuffer;
            AcpiOsPrintf ("%s\n", &AslGbl_CurrentLineBuffer[TokenOffset]);
        }
        else
        {
            PrError (ASL_ERROR, ASL_MSG_UNKNOWN_PRAGMA,
                THIS_TOKEN_OFFSET (Token));
            return;
        }

        break;

    case PR_DIRECTIVE_UNDEF:

        DbgPrint (ASL_PARSE_OUTPUT, PR_PREFIX_ID
            "#undef: %s\n", AslGbl_CurrentLineNumber, Token);

        PrRemoveDefine (Token);
        break;

    case PR_DIRECTIVE_WARNING:

        PrError (ASL_WARNING, ASL_MSG_WARNING_DIRECTIVE,
            THIS_TOKEN_OFFSET (Token));

        AslGbl_SourceLine = 0;
        AslGbl_NextError = AslGbl_ErrorLog;
        break;

    default:

        /* Should never get here */
        DbgPrint (ASL_PARSE_OUTPUT, PR_PREFIX_ID
            "Unrecognized directive: %u\n",
            AslGbl_CurrentLineNumber, Directive);
        break;
    }

    return;

SyntaxError:

    PrError (ASL_ERROR, ASL_MSG_DIRECTIVE_SYNTAX,
        THIS_TOKEN_OFFSET (DirectiveToken));
    return;
}