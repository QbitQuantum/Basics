static void onKey(
    HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags )
{
    long start = getStart( hwnd );
    long end   = getEnd( hwnd );

    const BOOL controlKey = GetAsyncKeyState( VK_CONTROL ) < 0;

    if ( VK_ESCAPE == vk ) {
        if ( htNone != getHTCode( hwnd ) ) {
            setHTCode( hwnd, htNone );
            const LONG oldStart = getSaveStart( hwnd );
            const LONG oldEnd   = getSaveEnd  ( hwnd );
            setStart( hwnd, oldStart );
            setEnd  ( hwnd, oldEnd   );
            invalidateRect( hwnd );
            //onLButtonUp( hwnd, 0, 0, 0 ); // TODO retain capture anyway?
            // TODO notify parent
            return; //** FUNCTION EXIT POINT
        }
    }

    const UINT left_key  = isVertical( hwnd ) ? VK_UP   : VK_LEFT ;
    const UINT right_key = isVertical( hwnd ) ? VK_DOWN : VK_RIGHT;

    long granularity = getGranularity( hwnd );
    if ( granularity <= 0 ) {
        granularity = 1;
    }

    if ( left_key == vk ) {
        if ( controlKey ) {
            if ( getMinRange( hwnd ) < end - start ) {
                end -= granularity;
            }
        } else if ( getLower( hwnd ) < start ) {
            start -= granularity;
            end   -= granularity;
        }
    } else if ( right_key == vk ) {
        if ( end < getUpper( hwnd ) ) {
            end += granularity;
            if ( !controlKey ) {
                start += granularity;
            }
        }
    } else if ( VK_PRIOR == vk ) {
        scroll( hwnd, -1, 0 );
        return; //*** FUNCTION EXIT POINT
    } else if ( VK_NEXT == vk ) {
        scroll( hwnd, 1, 0 );
        return; //*** FUNCTION EXIT POINT
    } else if ( VK_HOME == vk ) {
        const long range = abs( getLower( hwnd ) - start );
        start -= range;
        end   -= range;
    } else if ( VK_END == vk ) {
        const long range = abs( getUpper( hwnd ) - end );
        start += range;
        end   += range;
    }

    start = adjust( hwnd, start );
    end   = adjust( hwnd, end   );
    if ( start != getStart( hwnd ) || end != getEnd( hwnd ) ) {
        setStart( hwnd, start );
        setEnd  ( hwnd, end );
        invalidateRect( hwnd );
        invalidateCursor();
        notifyParent( hwnd );
    }
}