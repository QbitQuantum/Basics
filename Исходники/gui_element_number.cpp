    void CGuiNumber::SetNumber(int _Number)
    {
        /*
         _        _   _          _    _   __   _    _
        / \  /|    )  _)  |_|_  |_   |_    /  (_)  (_|
        \_/   |   /_  _)    |    _)  |_)  /   (_)    |

        */
        std::string Number = std::to_string(_Number);

        for (int IndexOfChar = Number.length(); IndexOfChar < m_MinLength; IndexOfChar++)
        {
            Number.insert(0, "0");
        }


        std::string FinalString;
        
        for (int IndexOfRow = 0; IndexOfRow < 3; IndexOfRow++)
        {
            for (char& Character : Number)
            {
                switch (Character)
                {
                    case '0':
                    {
                        switch (IndexOfRow)
                        {
                            case 0:
                                FinalString += " _  ";
                                break;
                            case 1:
                                FinalString += "/ \\ ";
                                break;
                            case 2:
                                FinalString += "\\_/ ";
                                break;
                            default:
                                break;
                        }

                        break;
                    }
                        
                    case '1':
                    {
                        switch (IndexOfRow)
                        {
                        case 0:
                            FinalString += "   ";
                            break;
                        case 1:
                            FinalString += "/| ";
                            break;
                        case 2:
                            FinalString += " | ";
                            break;
                        default:
                            break;
                        }

                        break;
                    }

                    case '2':
                    {
                        switch (IndexOfRow)
                        {
                        case 0:
                            FinalString += "_  ";
                            break;
                        case 1:
                            FinalString += " ) ";
                            break;
                        case 2:
                            FinalString += "/_ ";
                            break;
                        default:
                            break;
                        }

                        break;
                    }

                    case '3':
                    {
                        switch (IndexOfRow)
                        {
                        case 0:
                            FinalString += "_  ";
                            break;
                        case 1:
                            FinalString += "_) ";
                            break;
                        case 2:
                            FinalString += "_) ";
                            break;
                        default:
                            break;
                        }

                        break;
                    }

                    case '4':
                    {
                        switch (IndexOfRow)
                        {
                        case 0:
                            FinalString += "     ";
                            break;
                        case 1:
                            FinalString += "|_|_ ";
                            break;
                        case 2:
                            FinalString += "  |  ";
                            break;
                        default:
                            break;
                        }

                        break;
                    }

                    case '5':
                    {
                        switch (IndexOfRow)
                        {
                        case 0:
                            FinalString += " _  ";
                            break;
                        case 1:
                            FinalString += "|_  ";
                            break;
                        case 2:
                            FinalString += " _) ";
                            break;
                        default:
                            break;
                        }

                        break;
                    }

                    case '6':
                    {
                        switch (IndexOfRow)
                        {
                        case 0:
                            FinalString += " _  ";
                            break;
                        case 1:
                            FinalString += "|_  ";
                            break;
                        case 2:
                            FinalString += "|_) ";
                            break;
                        default:
                            break;
                        }

                        break;
                    }

                    case '7':
                    {
                        switch (IndexOfRow)
                        {
                        case 0:
                            FinalString += "__ ";
                            break;
                        case 1:
                            FinalString += " / ";
                            break;
                        case 2:
                            FinalString += "/  ";
                            break;
                        default:
                            break;
                        }

                        break;
                    }

                    case '8':
                    {
                        switch (IndexOfRow)
                        {
                        case 0:
                            FinalString += " _  ";
                            break;
                        case 1:
                            FinalString += "(_) ";
                            break;
                        case 2:
                            FinalString += "(_) ";
                            break;
                        default:
                            break;
                        }

                        break;
                    }

                    case '9':
                    {
                        switch (IndexOfRow)
                        {
                        case 0:
                            FinalString += " _  ";
                            break;
                        case 1:
                            FinalString += "(_| ";
                            break;
                        case 2:
                            FinalString += "  | ";
                            break;
                        default:
                            break;
                        }

                        break;
                    }

                    default:
                        break;
                }
            }
        }

        SetWidth(FinalString.length() / 3);
        SetHeight(3);

        SetLayout(FinalString);
    }