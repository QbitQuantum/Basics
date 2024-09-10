BOOL
EraseLine(
    IN HDC hDC,
    IN LPDRAW_ERASE_LINE DrawEraseLine
    )


/*++

Routine Description:

    EraseLine erasess the Erase line in the supplied DrawEraseLine structure.
    The EraseLine is set by the DrawLine routine.

Arguments:

    hDC             - Supplies a handle to the DC where the line should
                      be erased.
    DrawEraseLine   - Supplies a pointer to a DRAW_ERASE_LINE structure that
                      conatins the coordinates for the line to be erased.

Return Value:

    BOOL            - Returns TRUE if the line was succesfully erased.

--*/

{
    BOOL    Success;

    DbgHandleAssert( hDC );
    DbgPointerAssert( DrawEraseLine );

    Success = Polyline( hDC, ( CONST LPPOINT ) &DrawEraseLine->Erase, 2 );
    DbgAssert( Success );

    return Success;
}