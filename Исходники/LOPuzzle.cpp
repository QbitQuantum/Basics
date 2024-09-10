void LOPuzzle::checkTheConnection(char number)
{
    const float gresh = 0.1;
        
    char * cParts;
    char cPartsCount = getConnectedParts(number, cParts);
    
    //left side
    if (number%puzzleHorizontalSize!=0 && connection[number][0]<0)
    {
        char part = number-1;
        if (puzzleParts[part].active && puzzleParts[number].rotation == puzzleParts[part].rotation)
        {
            float dx = (puzzleParts[number].position.x - puzzleParts[part].position.x);
            float dy = (puzzleParts[number].position.y - puzzleParts[part].position.y);
        
            bool q = false;
            switch (puzzleParts[number].rotation) {
                case 0:
                    q = (fabsf(dx-puzzlePartSizeX)<gresh*puzzlePartSizeX && fabsf(dy)<gresh*puzzlePartSizeY);
                    if (q) moveParts(SunnyVector2D(-(dx-puzzlePartSizeX),-dy), cParts, cPartsCount);
                    break;
                case 1:
                    q = (fabsf(-dy-puzzlePartSizeX)<gresh*puzzlePartSizeX && fabsf(dx)<gresh*puzzlePartSizeY);
                    if (q) moveParts(SunnyVector2D(-dx,(-dy-puzzlePartSizeX)), cParts, cPartsCount);
                    break;
                case 2:
                    q = (fabsf(-dx-puzzlePartSizeX)<gresh*puzzlePartSizeX && fabsf(dy)<gresh*puzzlePartSizeY);
                    if (q) moveParts(SunnyVector2D((-dx-puzzlePartSizeX),-dy), cParts, cPartsCount);
                    break;
                case 3:
                    q = (fabsf(dy-puzzlePartSizeX)<gresh*puzzlePartSizeX && fabsf(dx)<gresh*puzzlePartSizeY);
                    if (q) moveParts(SunnyVector2D(-dx,-(dy-puzzlePartSizeX)), cParts, cPartsCount);
                    break;
                default:
                    break;
            }
            
            if (q)
            {
                connection[number][0] = part;
                connection[part][2] = number;
                playConnectSound = true;
            }
        }
    }
    
    //top side
    if (number>=puzzleHorizontalSize && connection[number][1]<0)
    {
        char part = number-puzzleHorizontalSize;
        if (puzzleParts[part].active && puzzleParts[number].rotation == puzzleParts[part].rotation)
        {
            float dx = (puzzleParts[number].position.x - puzzleParts[part].position.x);
            float dy = (puzzleParts[number].position.y - puzzleParts[part].position.y);
            
            bool q = false;
            switch (puzzleParts[number].rotation) {
                case 0:
                    q = (fabsf(-dy-puzzlePartSizeY)<gresh*puzzlePartSizeY && fabsf(dx)<gresh*puzzlePartSizeX);
                    if (q) moveParts(SunnyVector2D(-dx,(-dy-puzzlePartSizeY)), cParts, cPartsCount);
                    break;
                case 1:
                    q = (fabsf(-dx-puzzlePartSizeY)<gresh*puzzlePartSizeY && fabsf(dy)<gresh*puzzlePartSizeX);
                    if (q) moveParts(SunnyVector2D((-dx-puzzlePartSizeY),-dy), cParts, cPartsCount);
                    break;
                case 2:
                    q = (fabsf(dy-puzzlePartSizeY)<gresh*puzzlePartSizeY && fabsf(dx)<gresh*puzzlePartSizeX);
                    if (q) moveParts(SunnyVector2D(-dx,-(dy-puzzlePartSizeY)), cParts, cPartsCount);
                    break;
                case 3:
                    q = (fabsf(dx-puzzlePartSizeY)<gresh*puzzlePartSizeY && fabsf(dy)<gresh*puzzlePartSizeX);
                    if (q) moveParts(SunnyVector2D(-(dx-puzzlePartSizeY),-dy), cParts, cPartsCount);
                    break;
                default:
                    break;
            }
            
            if (q)
            {
                connection[number][1] = part;
                connection[part][3] = number;
                playConnectSound = true;
            }
        }
    }
    
    //right side
    if (number%puzzleHorizontalSize!=puzzleHorizontalSize-1 && connection[number][2]<0)
    {
        char part = number+1;
        if (puzzleParts[part].active && puzzleParts[number].rotation == puzzleParts[part].rotation)
        {
            float dx = (puzzleParts[number].position.x - puzzleParts[part].position.x);
            float dy = (puzzleParts[number].position.y - puzzleParts[part].position.y);
            
            bool q = false;
            switch (puzzleParts[number].rotation) {
                case 0:
                    q = (fabsf(-dx-puzzlePartSizeX)<gresh*puzzlePartSizeX && fabsf(dy)<gresh*puzzlePartSizeY);
                    if (q) moveParts(SunnyVector2D((-dx-puzzlePartSizeX),-dy), cParts, cPartsCount);
                    break;
                case 1:
                    q = (fabsf(dy-puzzlePartSizeX)<gresh*puzzlePartSizeX && fabsf(dx)<gresh*puzzlePartSizeY);
                    if (q) moveParts(SunnyVector2D(-dx,-(dy-puzzlePartSizeX)), cParts, cPartsCount);
                    break;
                case 2:
                    q = (fabsf(dx-puzzlePartSizeX)<gresh*puzzlePartSizeX && fabsf(dy)<gresh*puzzlePartSizeY);
                    if (q) moveParts(SunnyVector2D(-(dx-puzzlePartSizeX),-dy), cParts, cPartsCount);
                    break;
                case 3:
                    q = (fabsf(-dy-puzzlePartSizeX)<gresh*puzzlePartSizeX && fabsf(dx)<gresh*puzzlePartSizeY);
                    if (q) moveParts(SunnyVector2D(-dx,(-dy-puzzlePartSizeX)), cParts, cPartsCount);
                    break;
                default:
                    break;
            }
            
            if (q)
            {
                connection[number][2] = part;
                connection[part][0] = number;
                playConnectSound = true;
            }
        }
    }
    
    //bottom side
    if (number/puzzleHorizontalSize+1 < puzzleVerticalSize && connection[number][3]<0)
    {
        char part = number+puzzleHorizontalSize;
        if (puzzleParts[part].active && puzzleParts[number].rotation == puzzleParts[part].rotation)
        {
            float dx = (puzzleParts[number].position.x - puzzleParts[part].position.x);
            float dy = (puzzleParts[number].position.y - puzzleParts[part].position.y);
            
            bool q = false;
            switch (puzzleParts[number].rotation) {
                case 0:
                    q = (fabsf(dy-puzzlePartSizeY)<gresh*puzzlePartSizeY && fabsf(dx)<gresh*puzzlePartSizeX);
                    if (q) moveParts(SunnyVector2D(-dx,-(dy-puzzlePartSizeY)), cParts, cPartsCount);
                    break;
                case 1:
                    q = (fabsf(dx-puzzlePartSizeY)<gresh*puzzlePartSizeY && fabsf(dy)<gresh*puzzlePartSizeX);
                    if (q) moveParts(SunnyVector2D(-(dx-puzzlePartSizeY),-dy), cParts, cPartsCount);
                    break;
                case 2:
                    q = (fabsf(-dy-puzzlePartSizeY)<gresh*puzzlePartSizeY && fabsf(dx)<gresh*puzzlePartSizeX);
                    if (q) moveParts(SunnyVector2D(-dx,(-dy-puzzlePartSizeY)), cParts, cPartsCount);
                    break;
                case 3:
                    q = (fabsf(-dx-puzzlePartSizeY)<gresh*puzzlePartSizeY && fabsf(dy)<gresh*puzzlePartSizeX);
                    if (q) moveParts(SunnyVector2D((-dx-puzzlePartSizeY),-dy), cParts, cPartsCount);
                    break;
                default:
                    break;
            }
            
            if (q)
            {
                connection[number][3] = part;
                connection[part][1] = number;
                playConnectSound = true;
            }
        }
    }
    
    free(cParts);
}