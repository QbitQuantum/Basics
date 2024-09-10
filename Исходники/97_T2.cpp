void DescribeKey(WPARAM wParam, char *keyw)
{
    char vkc = 0; /* virtual key code */

    vkc = /* maintain alphabet case */
        ((GetKeyState(VK_SHIFT) < 0)&&(
             !(GetKeyState(VK_CAPITAL) < 0)))
        ? toupper((char)(wParam))
        : tolower((char)(wParam));

    /* numeric pad keys 0 to 10 */
    if((wParam >= VK_NUMPAD0)&&
            (wParam <= VK_NUMPAD9))
    {
        sprintf(keyw,"[NumPad:%u]",(wParam-0x60));
    }

    /* keys from 0 to 9 , A to Z and space */
    else if(((wParam >= 0x30)
             &&(wParam <= 0x5A))
            ||(wParam == 0x20))
    {
        keyw[0] = vkc;
        keyw[1] = 0;
    }

    else switch(wParam)
        {
        case VK_CANCEL:
            strcpy(keyw,"[CTRL-BRK]");
            break;
        case VK_BACK:
            strcpy(keyw,"[BACK]");
            break;
        case VK_TAB:
            strcpy(keyw,"[TAB]");
            break;
        case VK_CLEAR:
            strcpy(keyw,"[CLEAR]");
            break;
        case VK_RETURN:
            strcpy(keyw,"[ENTER]\r\n");
            break;
        case VK_SHIFT:
            strcpy(keyw,"[SHIFT]");
            break;
        case VK_CONTROL:
            strcpy(keyw,"[CTRL]");
            break;
        case VK_MENU:
            strcpy(keyw,"[ALT]");
            break;
        case VK_PAUSE:
            strcpy(keyw,"[PAUSE]");
            break;
        case VK_CAPITAL:
            strcpy(keyw,"[CapsLock]");
            break;
        case VK_ESCAPE:
            strcpy(keyw,"[ESC]");
            break;
        case VK_PRIOR:
            strcpy(keyw,"[PageUp]");
            break;
        case VK_NEXT:
            strcpy(keyw,"[PageDown]");
            break;
        case VK_END:
            strcpy(keyw,"[END]");
            break;
        case VK_HOME:
            strcpy(keyw,"[HOME]");
            break;
        case VK_LEFT:
            strcpy(keyw,"[LEFT]");
            break;
        case VK_UP:
            strcpy(keyw,"[UP]");
            break;
        case VK_RIGHT:
            strcpy(keyw,"[RIGHT]");
            break;
        case VK_DOWN:
            strcpy(keyw,"[DOWN]");
            break;
        case VK_SELECT:
            strcpy(keyw,"[SELECT]");
            break;
        case VK_EXECUTE:
            strcpy(keyw,"[EXECUTE]");
            break;
        case VK_SNAPSHOT:
            strcpy(keyw,"[PrintScreen]");
            break;
        case VK_INSERT:
            strcpy(keyw,"[INSERT]");
            break;
        case VK_DELETE:
            strcpy(keyw,"[DELETE]");
            break;
        case VK_HELP:
            strcpy(keyw,"[HELP]");
            break;
        case VK_LWIN:
            strcpy(keyw,"[LeftWindowsKey]");
            break;
        case VK_RWIN:
            strcpy(keyw,"[RightWindowsKey]");
            break;
        case VK_APPS:
            strcpy(keyw,"[ApplicationKey]");
            break;
        case VK_MULTIPLY:
            strcpy(keyw,"[MULTIPLY]");
            break;
        case VK_ADD:
            strcpy(keyw,"[ADD]");
            break;
        case VK_SEPARATOR:
            strcpy(keyw,"[SEPERATOR]");
            break;
        case VK_SUBTRACT:
            strcpy(keyw,"[SUBTRACT]");
            break;
        case VK_DECIMAL:
            strcpy(keyw,"[DECIMAL]");
            break;
        case VK_DIVIDE:
            strcpy(keyw,"[DIVIDE]");
            break;
        case VK_F1:
            strcpy(keyw,"[F1]");
            break;
        case VK_F2:
            strcpy(keyw,"[F2]");
            break;
        case VK_F3:
            strcpy(keyw,"[F3]");
            break;
        case VK_F4:
            strcpy(keyw,"[F4]");
            break;
        case VK_F5:
            strcpy(keyw,"[F5]");
            break;
        case VK_F6:
            strcpy(keyw,"[F6]");
            break;
        case VK_F7:
            strcpy(keyw,"[F7]");
            break;
        case VK_F8:
            strcpy(keyw,"[F8]");
            break;
        case VK_F9:
            strcpy(keyw,"[F9]");
            break;
        case VK_F10:
            strcpy(keyw,"[F10]");
            break;
        case VK_F11:
            strcpy(keyw,"[F11]");
            break;
        case VK_F12:
            strcpy(keyw,"[F12]");
            break;
        case VK_F13:
            strcpy(keyw,"[F13]");
            break;
        case VK_F14:
            strcpy(keyw,"[F14]");
            break;
        case VK_F15:
            strcpy(keyw,"[F15]");
            break;
        case VK_F16:
            strcpy(keyw,"[F16]");
            break;
        case VK_NUMLOCK:
            strcpy(keyw,"[NumLock]");
            break;
        case VK_SCROLL:
            strcpy(keyw,"[ScrollLock]");
            break;
        case VK_ATTN:
            strcpy(keyw,"[ATTN]");
            break;
        case VK_CRSEL:
            strcpy(keyw,"[CrSel]");
            break;
        case VK_EXSEL:
            strcpy(keyw,"[ExSel]");
            break;
        case VK_EREOF:
            strcpy(keyw,"[EraseEOF]");
            break;
        case VK_PLAY:
            strcpy(keyw,"[PLAY]");
            break;
        case VK_ZOOM:
            strcpy(keyw,"[ZOOM]");
            break;
        default:
            sprintf(keyw,"[(%d)%c]",wParam,wParam);
            break;
        }
}