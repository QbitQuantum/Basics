/**
  sets a list of all Shell-Guid-based environment variables.

  @param Environment        Points to a NULL-terminated array of environment
                            variables with the format 'x=y', where x is the
                            environment variable name and y is the value.

  @retval EFI_SUCCESS       The command executed successfully.
  @retval EFI_INVALID_PARAMETER The parameter is invalid.
  @retval EFI_OUT_OF_RESOURCES Out of resources.

  @sa SetEnvironmentVariableList
**/
EFI_STATUS
EFIAPI
SetEnvironmentVariables(
    IN CONST CHAR16 **Environment
)
{
    CONST CHAR16  *CurrentString;
    UINTN         CurrentCount;
    ENV_VAR_LIST  *VarList;
    ENV_VAR_LIST  *Node;
    UINTN         NewSize;

    VarList = NULL;

    if (Environment == NULL) {
        return (EFI_INVALID_PARAMETER);
    }

    //
    // Build a list identical to the ones used for get/set list functions above
    //
    for ( CurrentCount = 0
                         ;
            ; CurrentCount++
        ) {
        CurrentString = Environment[CurrentCount];
        if (CurrentString == NULL) {
            break;
        }
        ASSERT(StrStr(CurrentString, L"=") != NULL);
        Node = AllocateZeroPool(sizeof(ENV_VAR_LIST));
        ASSERT(Node != NULL);
        Node->Key = AllocateZeroPool((StrStr(CurrentString, L"=") - CurrentString + 1) * sizeof(CHAR16));
        ASSERT(Node->Key != NULL);
        StrnCpy(Node->Key, CurrentString, StrStr(CurrentString, L"=") - CurrentString);
        NewSize = StrSize(CurrentString);
        NewSize -= StrLen(Node->Key) - 1;
        Node->Val = AllocateZeroPool(NewSize);
        ASSERT(Node->Val != NULL);
        StrCpy(Node->Val, CurrentString + StrLen(Node->Key) + 1);
        Node->Atts = EFI_VARIABLE_BOOTSERVICE_ACCESS;

        if (VarList == NULL) {
            VarList = AllocateZeroPool(sizeof(ENV_VAR_LIST));
            ASSERT(VarList != NULL);
            InitializeListHead(&VarList->Link);
        }
        InsertTailList(&VarList->Link, &Node->Link);

    } // for loop

    //
    // set this new list as the set of all environment variables.
    // this function also frees the memory and deletes all pre-existing
    // shell-guid based environment variables.
    //
    return (SetEnvironmentVariableList(&VarList->Link));
}