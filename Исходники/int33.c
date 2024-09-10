/**********************************************************************
 *	    DOSVM_Int33Handler
 *
 * Handler for int 33h (MS MOUSE).
 */
void WINAPI DOSVM_Int33Handler( CONTEXT *context )
{
    switch (AX_reg(context))
    {
    case 0x0000:
        TRACE("Reset mouse driver and request status\n");
        INT33_ResetMouse( context );
        break;

    case 0x0001:
        TRACE("Show mouse cursor, old hide count: %d\n",
              mouse_info.hide_count);
        if (mouse_info.hide_count >= 1)
            mouse_info.hide_count--;
        if (!mouse_info.hide_count)
            VGA_ShowMouse( TRUE );
        break;

    case 0x0002:
        TRACE("Hide mouse cursor, old hide count: %d\n",
              mouse_info.hide_count);
        if(!mouse_info.hide_count)
            VGA_ShowMouse( FALSE );            
        mouse_info.hide_count++;
        break;

    case 0x0003:
        TRACE("Return mouse position and button status: (%d,%d) and %d\n",
              mouse_info.x, mouse_info.y, mouse_info.but);
        SET_BX( context, mouse_info.but );
        SET_CX( context, mouse_info.x );
        SET_DX( context, mouse_info.y );
        break;

    case 0x0004:
        FIXME("Position mouse cursor\n");
        break;

    case 0x0005:
        TRACE("Return Mouse button press Information for %s mouse button\n",
              BX_reg(context) ? "right" : "left");
        if (BX_reg(context)) 
        {
            SET_BX( context, mouse_info.rbcount );
            mouse_info.rbcount = 0;
            SET_CX( context, mouse_info.rlastx );
            SET_DX( context, mouse_info.rlasty );
        } 
        else 
        {
            SET_BX( context, mouse_info.lbcount );
            mouse_info.lbcount = 0;
            SET_CX( context, mouse_info.llastx );
            SET_DX( context, mouse_info.llasty );
        }
        SET_AX( context, mouse_info.but );
        break;

    case 0x0007:
        FIXME("Define horizontal mouse cursor range %d..%d\n",
              CX_reg(context), DX_reg(context));
        break;

    case 0x0008:
        FIXME("Define vertical mouse cursor range %d..%d\n",
              CX_reg(context), DX_reg(context));
        break;

    case 0x0009:
        FIXME("Define graphics mouse cursor\n");
        break;

    case 0x000A:
        FIXME("Define text mouse cursor\n");
        break;

    case 0x000B:
        TRACE("Read Mouse motion counters\n");
        {
            int dx = ((int)mouse_info.x - (int)mouse_info.oldx)
                * (mouse_info.HMPratio / 8);
            int dy = ((int)mouse_info.y - (int)mouse_info.oldy)
                * (mouse_info.VMPratio / 8);

            SET_CX( context, (WORD)dx );
            SET_DX( context, (WORD)dy );

            mouse_info.oldx = mouse_info.x;
            mouse_info.oldy = mouse_info.y;
        }
        break;

    case 0x000C:
        TRACE("Define mouse interrupt subroutine\n");
        mouse_info.callmask = CX_reg(context);
        mouse_info.callback = (FARPROC16)MAKESEGPTR(context->SegEs, 
                                                    DX_reg(context));
        break;

    case 0x000F:
        TRACE("Set mickey/pixel ratio\n");
        mouse_info.HMPratio = CX_reg(context);
        mouse_info.VMPratio = DX_reg(context);
        break;

    case 0x0010:
        FIXME("Define screen region for update\n");
        break;

    case 0x0021:
        TRACE("Software reset\n");
        INT33_ResetMouse( context );
        break;

    default:
        INT_BARF(context,0x33);
    }
}