/*
 * This function injects a single character into the widget.
 */
static int _injectCDKUScale (CDKOBJS *object, chtype input)
{
    CDKUSCALE *widget = (CDKUSCALE *)object;
    int ppReturn = 1;
    unsigned ret = unknownUnsigned;
    bool complete = FALSE;

    /* Set the exit type. */
    setExitType(widget, 0);

    /* Draw the field. */
    drawCDKUScaleField (widget);

    /* Check if there is a pre-process function to be called. */
    if (PreProcessFuncOf(widget) != 0)
    {
        /* Call the pre-process function. */
        ppReturn = PreProcessFuncOf(widget) (vUSCALE, widget, PreProcessDataOf(widget), input);
    }

    /* Should we continue? */
    if (ppReturn != 0)
    {
        /* Check for a key binding. */
        if (checkCDKObjectBind(vUSCALE, widget, input) != 0)
        {
            checkEarlyExit(widget);
            complete = TRUE;
        }
        else
        {
            switch (input)
            {
            case KEY_LEFT :
                setEditPosition(widget, widget->fieldEdit + 1);
                break;

            case KEY_RIGHT :
                setEditPosition(widget, widget->fieldEdit - 1);
                break;

            case KEY_DOWN :
                Decrement(widget->current, widget->inc);
                break;

            case KEY_UP :
                Increment(widget->current, widget->inc);
                break;

            case KEY_PPAGE :
                Increment(widget->current, widget->fastinc);
                break;

            case KEY_NPAGE :
                Decrement(widget->current, widget->fastinc);
                break;

            case KEY_HOME :
                widget->current = widget->low;
                break;

            case KEY_END :
                widget->current = widget->high;
                break;

            case KEY_TAB :
            case KEY_ENTER :
                setExitType(widget, input);
                ret = (widget->current);
                complete = TRUE;
                break;

            case KEY_ESC :
                setExitType(widget, input);
                complete = TRUE;
                break;

            case CDK_REFRESH :
                eraseCDKScreen (ScreenOf(widget));
                refreshCDKScreen (ScreenOf(widget));
                break;

            default :
                if (widget->fieldEdit)
                {
                    if (!performEdit(widget, input))
                        BEEP();
                }
                else
                {
                    /*
                     * The cursor is not within the editable text.  Interpret
                     * input as commands.
                     */
                    switch (input)
                    {
                    case 'd':
                    case '-':
                        return _injectCDKUScale(object, KEY_DOWN);
                    case '+':
                        return _injectCDKUScale(object, KEY_UP);
                    case 'D':
                        return _injectCDKUScale(object, KEY_NPAGE);
                    case '0':
                        return _injectCDKUScale(object, KEY_HOME);
                    default:
                        BEEP();
                        break;
                    }
                }
                break;
            }
        }
        limitCurrentValue(widget);

        /* Should we call a post-process? */
        if (!complete && (PostProcessFuncOf(widget) != 0))
        {
            PostProcessFuncOf(widget) (vUSCALE, widget, PostProcessDataOf(widget), input);
        }
    }

    if (!complete) {
        drawCDKUScaleField (widget);
        setExitType(widget, 0);
    }

    ResultOf(widget).valueUnsigned = ret;
    return (ret != unknownUnsigned);
}