QString KeyBind::keyString(int key, int mod)
{
  QString modString = QString::null;
  QString keyString = QString::null;

  if (key >= Key_F1 && key <= Key_F12)
    {
      // Function keys
      keyString.sprintf("F%d", key - Key_F1 + 1);
    }
  else if (key >= Key_0 && key <= Key_9)
    {
      // Number keys
      keyString.sprintf("%d", key - Key_0);
    }
  else if (key >= Key_A && key <= Key_Z)
    {
      // A-Z
      keyString.sprintf("%c", 'A' + key - Key_A);
    }
  else
    {
      switch(key)
	{
	case Key_Exclam:
	  keyString.sprintf("!");
	  break;
	case Key_QuoteDbl:
	  keyString.sprintf("\"");
	  break;
	case Key_NumberSign:
	  keyString.sprintf("Unknown");
	  break;
	case Key_Dollar:
	  keyString.sprintf("$");
	  break;
	case Key_Percent:
	  keyString.sprintf("%%");
	  break;
	case Key_Ampersand:
	  keyString.sprintf("&");
	  break;
	case Key_Apostrophe:
	  keyString.sprintf("'");
	  break;
	case Key_ParenLeft:
	  keyString.sprintf("(");
	  break;
	case Key_ParenRight:
	  keyString.sprintf(")");
	  break;
	case Key_Asterisk:
	  keyString.sprintf("*");
	  break;
	case Key_Plus:
	  keyString.sprintf("+");
	  break;
	case Key_Comma:
	  keyString.sprintf(",");
	  break;
	case Key_Minus:
	  keyString.sprintf("-");
	  break;
	case Key_Period:
	  keyString.sprintf(".");
	  break;
	case Key_Slash:
	  keyString.sprintf("/");
	  break;
	case Key_Colon:
	  keyString.sprintf(":");
	  break;
        case Key_Semicolon:
	  keyString.sprintf(";");
	  break;
        case Key_Less:
	  keyString.sprintf("<");
	  break;
        case Key_Equal:
	  keyString.sprintf("/");
	  break;
        case Key_Greater:
	  keyString.sprintf(">");
	  break;
        case Key_Question:
	  keyString.sprintf("?");
	  break;
	case Key_BracketLeft:
	  keyString.sprintf("?");
	  break;
        case Key_Backslash:
	  keyString.sprintf("?");
	  break;
	case Key_BracketRight:
	  keyString.sprintf("?");
	  break;
	case Key_AsciiCircum:
	  keyString.sprintf("?");
	  break;
	case Key_Underscore:
	  keyString.sprintf("_");
	  break;
	case Key_QuoteLeft:
	  keyString.sprintf("`");
	  break;
	case Key_BraceLeft:
	  keyString.sprintf("{");
	  break;
	case Key_Bar:
	  keyString.sprintf("|");
	  break;
	case Key_BraceRight:
	  keyString.sprintf("}");
	  break;
	case Key_AsciiTilde:
	  keyString.sprintf("~");
	  break;
	case Key_At:
	  keyString.sprintf("@");
	  break;
	case Key_Space:
	  keyString.sprintf("Space");
	  break;
	case Key_Escape:
	  keyString.sprintf("Escape");
	  break;
	case Key_Return:
	  keyString.sprintf("Return");
	  break;
	case Key_Enter:
	  keyString.sprintf("Enter");
	  break;
	case Key_Insert:
	  keyString.sprintf("Insert");
	  break;
	case Key_Delete:
	  keyString.sprintf("Delete");
	  break;
	case Key_Pause:
	  keyString.sprintf("Pause");
	  break;
	case Key_Home:
	  keyString.sprintf("Home");
	  break;
	case Key_End:
	  keyString.sprintf("End");
          break;
	case Key_PageUp:
	  keyString.sprintf("PageUp");
	  break;
	case Key_PageDown:
	  keyString.sprintf("PageDown");
	  break;
	case Key_Left:
	  keyString.sprintf("Left");
          break;
	case Key_Right:
	  keyString.sprintf("Right");
          break;
	case Key_Up:
	  keyString.sprintf("Up");
          break;
	case Key_Down:
	  keyString.sprintf("Down");
          break;
	case Key_Shift:
	  keyString.sprintf("Shift +");
	  break;
	case Key_Alt:
	  keyString.sprintf("Alt +");
	  break;
	case Key_Control:
	  keyString.sprintf("Control +");
	  break;
	case 0:
	  keyString.sprintf("None");
	  break;
	case Key_unknown:
	  keyString.sprintf("Unknown");
	  break;
	default:
	  keyString.sprintf("Code %d", key);
	  break;
	}
    }

  if (mod & ShiftButton)
    {
      modString += QString("Shift + ");
    }
  
  if (mod & AltButton)
    {
      modString += QString("Alt + ");
    }

  if (mod & ControlButton)
    {
      modString += QString("Control + ");
    }

  if (key == 0)
    {
      return QString("None");
    }
  else
    {
      return QString(modString + keyString);
    }
}