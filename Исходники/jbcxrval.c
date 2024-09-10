void
__except_validate_context_record (
    _In_ PCONTEXT ContextRecord
    )

/*++

Routine Description:

    This function validates a context record for exception handling support.

Arguments:

    ContextRecord - Supplies a pointer to the context record to validate.

Return Value:

    None.  If the context record was not valid, a fast fail event is raised if
    CFG was enforced.

--*/

{
    PVOID StackPointer;
    PNT_TIB Tib;

    //
    // If guard ICall checks are enforced, then validate the stack extents of
    // the context record and raise a fast fail exception if the extents are
    // invalid.  If checks are not enforced or the jump buffer was valid, then
    // return.
    //
    if (_guard_icall_checks_enforced()) {
        Tib = (PNT_TIB)NtCurrentTeb();

        //
        // HYB-TODO: Validate both chpe and guest context.
        //

        StackPointer = (PVOID)CONTEXT_TO_STACK_POINTER(ContextRecord);
        if ((StackPointer < Tib->StackLimit) ||
            (StackPointer > Tib->StackBase)) {

            __fastfail(FAST_FAIL_INVALID_SET_OF_CONTEXT);
        }
    }
}