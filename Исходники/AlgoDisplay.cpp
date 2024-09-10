void AlgoDisplay::paint(Graphics &g) {

    g.setColour(DXLookNFeel::fillColour);
    g.fillRect(1, 3, 20, 15);
    String n = String(*algo +1);
    
    g.setColour(Colours::white);
    g.drawText(n, 1, 3, 20, 15, Justification::centred, true);

    switch(*algo) {
        case 0:
            displayOp(g, 6, 3, 0, 0, 1);
            displayOp(g, 5, 3, 1, 0, 0);
            displayOp(g, 4, 3, 2, 0, 0);
            displayOp(g, 3, 3, 3, 2, 0);
            displayOp(g, 2, 2, 2, 0, 0);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 1:
            displayOp(g, 6, 3, 0, 0, 0);
            displayOp(g, 5, 3, 1, 0, 0);
            displayOp(g, 4, 3, 2, 0, 0);
            displayOp(g, 3, 3, 3, 2, 0);
            displayOp(g, 2, 2, 2, 0, 1);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 2:
            displayOp(g, 6, 3, 1, 0, 1);
            displayOp(g, 5, 3, 2, 0, 0);
            displayOp(g, 4, 3, 3, 2, 0);
            displayOp(g, 3, 2, 1, 0, 0);
            displayOp(g, 2, 2, 2, 0, 0);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 3: //
            displayOp(g, 6, 3, 1, 0, 2);
            displayOp(g, 5, 3, 2, 0, 0);
            displayOp(g, 4, 3, 3, 2, 0);
            displayOp(g, 3, 2, 1, 0, 0);
            displayOp(g, 2, 2, 2, 0, 0);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 4:
            displayOp(g, 6, 4, 2, 0, 1);
            displayOp(g, 5, 4, 3, 2, 0);
            displayOp(g, 4, 3, 2, 0, 0);
            displayOp(g, 3, 3, 3, 1, 0);
            displayOp(g, 2, 2, 2, 0, 0);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 5: //
            displayOp(g, 6, 4, 2, 0, 3);
            displayOp(g, 5, 4, 3, 2, 0);
            displayOp(g, 4, 3, 2, 0, 0);
            displayOp(g, 3, 3, 3, 1, 0);
            displayOp(g, 2, 2, 2, 0, 0);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 6:
            displayOp(g, 6, 4, 1, 0, 1);
            displayOp(g, 5, 4, 2, 7, 0);
            displayOp(g, 4, 3, 2, 0, 0);
            displayOp(g, 3, 3, 3, 2, 0);
            displayOp(g, 2, 2, 2, 0, 0);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 7:
            displayOp(g, 6, 4, 1, 0, 0);
            displayOp(g, 5, 4, 2, 7, 0);
            displayOp(g, 4, 3, 2, 0, 4);
            displayOp(g, 3, 3, 3, 2, 0);
            displayOp(g, 2, 2, 2, 0, 0);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 8:
            displayOp(g, 6, 4, 1, 0, 0);
            displayOp(g, 5, 4, 2, 7, 0);
            displayOp(g, 4, 3, 2, 0, 0);
            displayOp(g, 3, 3, 3, 2, 0);
            displayOp(g, 2, 2, 2, 0, 1);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 9:
            displayOp(g, 6, 2, 2, 0, 0);
            displayOp(g, 5, 1, 2, 1, 0);
            displayOp(g, 4, 2, 3, 1, 0);
            displayOp(g, 3, 3, 1, 0, 1);
            displayOp(g, 2, 3, 2, 0, 0);
            displayOp(g, 1, 3, 3, 2, 0);
            break;
        case 10:
            displayOp(g, 6, 2, 2, 0, 1);
            displayOp(g, 5, 1, 2, 1, 0);
            displayOp(g, 4, 2, 3, 1, 0);
            displayOp(g, 3, 3, 1, 0, 0);
            displayOp(g, 2, 3, 2, 0, 0);
            displayOp(g, 1, 3, 3, 2, 0);
            break;
        case 11:
            displayOp(g, 6, 3, 2, 7, 0);
            displayOp(g, 5, 2, 2, 0, 0);
            displayOp(g, 4, 1, 2, 1, 0);
            displayOp(g, 3, 2, 3, 6, 0);
            displayOp(g, 2, 4, 2, 0, 1);
            displayOp(g, 1, 4, 3, 2, 0);
            break;
        case 12:
            displayOp(g, 6, 3, 2, 7, 1);
            displayOp(g, 5, 2, 2, 0, 0);
            displayOp(g, 4, 1, 2, 1, 0);
            displayOp(g, 3, 2, 3, 6, 0);
            displayOp(g, 2, 4, 2, 0, 0);
            displayOp(g, 1, 4, 3, 2, 0);
            break;
        case 13:
            displayOp(g, 6, 3, 1, 0, 1);
            displayOp(g, 5, 2, 1, 1, 0);
            displayOp(g, 4, 3, 2, 0, 0);
            displayOp(g, 3, 3, 3, 2, 0);
            displayOp(g, 2, 2, 2, 0, 0);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 14:
            displayOp(g, 6, 3, 1, 0, 0);
            displayOp(g, 5, 2, 1, 1, 0);
            displayOp(g, 4, 3, 2, 0, 0);
            displayOp(g, 3, 3, 3, 2, 0);
            displayOp(g, 2, 2, 2, 0, 4);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 15:
            displayOp(g, 6, 4, 1, 0, 1);
            displayOp(g, 5, 4, 2, 7, 0);
            displayOp(g, 4, 3, 1, 0, 0);
            displayOp(g, 3, 3, 2, 0, 0);
            displayOp(g, 2, 2, 2, 1, 0);
            displayOp(g, 1, 3, 3, 0, 0);
            break;
        case 16:
            displayOp(g, 6, 4, 1, 0, 0);
            displayOp(g, 5, 4, 2, 7, 0);
            displayOp(g, 4, 3, 1, 0, 0);
            displayOp(g, 3, 3, 2, 0, 0);
            displayOp(g, 2, 2, 2, 1, 4);
            displayOp(g, 1, 3, 3, 0, 0);
            break;
        case 17:
            displayOp(g, 6, 4, 0, 0, 0);
            displayOp(g, 5, 4, 1, 0, 0);
            displayOp(g, 4, 4, 2, 7, 0);
            displayOp(g, 3, 3, 2, 0, 4);
            displayOp(g, 2, 2, 2, 1, 0);
            displayOp(g, 1, 3, 3, 0, 0);
            break;
        case 18:
            displayOp(g, 6, 3, 2, 0, 1);
            displayOp(g, 5, 4, 3, 2, 0);
            displayOp(g, 4, 3, 3, 1, 0);
            displayOp(g, 3, 2, 1, 0, 0);
            displayOp(g, 2, 2, 2, 0, 0);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 19:
            displayOp(g, 6, 4, 2, 0, 0);
            displayOp(g, 5, 3, 2, 1, 0);
            displayOp(g, 4, 4, 3, 2, 0);
            displayOp(g, 3, 1, 2, 0, 1);
            displayOp(g, 2, 2, 3, 6, 0);
            displayOp(g, 1, 1, 3, 1, 0);
            break;
        case 20:
            displayOp(g, 6, 3, 2, 0, 0);
            displayOp(g, 5, 4, 3, 2, 0);
            displayOp(g, 4, 3, 3, 1, 0);
            displayOp(g, 3, 1, 2, 0, 1);
            displayOp(g, 2, 2, 3, 1, 0);
            displayOp(g, 1, 1, 3, 1, 0);
            break;
        case 21:
            displayOp(g, 6, 3, 2, 0, 1);
            displayOp(g, 5, 4, 3, 2, 0);
            displayOp(g, 4, 3, 3, 1, 0);
            displayOp(g, 3, 2, 3, 1, 0);
            displayOp(g, 2, 1, 2, 0, 0);
            displayOp(g, 1, 1, 3, 1, 0);
            break;
        case 22: // CC
            displayOp(g, 6, 3, 2, 0, 1);
            displayOp(g, 5, 4, 3, 2, 0);
            displayOp(g, 4, 3, 3, 1, 0);
            displayOp(g, 3, 2, 2, 0, 0);
            displayOp(g, 2, 2, 3, 1, 0);
            displayOp(g, 1, 1, 3, 1, 0);
            break;
        case 23: // CC
            displayOp(g, 6, 3, 2, 0, 1);
            displayOp(g, 5, 4, 3, 2, 0);
            displayOp(g, 4, 3, 3, 1, 0);
            displayOp(g, 3, 2, 3, 1, 0);
            displayOp(g, 2, 1, 3, 1, 0);
            displayOp(g, 1, 0, 3, 1, 0);
            break;
        case 24: // CC
            displayOp(g, 6, 3, 2, 0, 1);
            displayOp(g, 5, 4, 3, 2, 0);
            displayOp(g, 4, 3, 3, 1, 0);
            displayOp(g, 3, 2, 3, 1, 0);
            displayOp(g, 2, 1, 3, 1, 0);
            displayOp(g, 1, 0, 3, 1, 0);
            break;
        case 25:
            displayOp(g, 6, 4, 2, 0, 1);
            displayOp(g, 5, 3, 2, 1, 0);
            displayOp(g, 4, 4, 3, 2, 0);
            displayOp(g, 3, 2, 2, 0, 0);
            displayOp(g, 2, 2, 3, 6, 0);
            displayOp(g, 1, 1, 3, 1, 0);
            break;
        case 26:
            displayOp(g, 6, 4, 2, 0, 0);
            displayOp(g, 5, 3, 2, 1, 0);
            displayOp(g, 4, 4, 3, 2, 0);
            displayOp(g, 3, 2, 2, 0, 1);
            displayOp(g, 2, 2, 3, 6, 0);
            displayOp(g, 1, 1, 3, 1, 0);
            break;
        case 27:
            displayOp(g, 6, 4, 3, 2, 0);
            displayOp(g, 5, 3, 1, 0, 1);
            displayOp(g, 4, 3, 2, 0, 0);
            displayOp(g, 3, 3, 3, 1, 0);
            displayOp(g, 2, 2, 2, 0, 0);
            displayOp(g, 1, 2, 3, 1, 0);
            break;
        case 28:
            displayOp(g, 6, 4, 2, 0, 1);
            displayOp(g, 5, 4, 3, 2, 0);
            displayOp(g, 4, 3, 2, 0, 0);
            displayOp(g, 3, 3, 3, 1, 0);
            displayOp(g, 2, 2, 3, 1, 0);
            displayOp(g, 1, 1, 3, 1, 0);
            break;
        case 29:
            displayOp(g, 6, 4, 3, 2, 0);
            displayOp(g, 5, 3, 1, 0, 1);
            displayOp(g, 4, 3, 2, 0, 0);
            displayOp(g, 3, 3, 3, 1, 0);
            displayOp(g, 2, 2, 3, 1, 0);
            displayOp(g, 1, 1, 3, 1, 0);
            break;
        case 30:
            displayOp(g, 6, 4, 2, 0, 1);
            displayOp(g, 5, 4, 3, 2, 0);
            displayOp(g, 4, 3, 3, 1, 0);
            displayOp(g, 3, 2, 3, 1, 0);
            displayOp(g, 2, 1, 3, 1, 0);
            displayOp(g, 1, 0, 3, 1, 0);     
            break;
        case 31:
            displayOp(g, 6, 5, 3, 2, 1);
            displayOp(g, 5, 4, 3, 1, 0);
            displayOp(g, 4, 3, 3, 1, 0);
            displayOp(g, 3, 2, 3, 1, 0);
            displayOp(g, 2, 1, 3, 1, 0);
            displayOp(g, 1, 0, 3, 1, 0);       
            break;
        default:
            break;
    }
}