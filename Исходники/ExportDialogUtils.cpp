    VOID GridLayout::PlaceWindow(HWND hwnd, INT rowStart, INT colStart, INT rowSpan, INT colSpan, INT border, DWORD alignment)
    {
        RECT rect;
        GetRect(&rect, rowStart, colStart, rowSpan, colSpan, border);
        INT cy = rect.bottom - rect.top;
        INT cx = rect.right - rect.left;

        // early out if the control is supposed to be resized to fit the rect
        if (alignment == ALIGN_FILLRECT)
        {
            MoveWindow(hwnd, rect.left, rect.top, cx, cy, true);
            return;
        }

        INT px = rect.left, py = rect.top;

        // get current size of window
        RECT currentRect;
        GetWindowRect(hwnd, &currentRect);
        INT sizeX = currentRect.right - currentRect.left;
        INT sizeY = currentRect.bottom - currentRect.top;

        INT newSizeX = sizeX;
        INT newSizeY = sizeY;

        // figure out horizontal placement
        if (alignment & ALIGN_HCENTER)
        {
            px = rect.left + (cx / 2) - (sizeX / 2);
        }
        else if (alignment & ALIGN_LEFT)
        {
            px = rect.left;
        }
        else if (alignment & ALIGN_RIGHT)
        {
            px = rect.right - sizeX;
        }
        else if (alignment & ALIGN_HJUSTIFY)
        {
            px = rect.left;
            newSizeX = cx;
        }

        // figure out vertical placement
        if (alignment & ALIGN_VCENTER)
        {
            py = rect.top + (cy / 2) - (sizeY / 2);
        }
        else if (alignment & ALIGN_TOP)
        {
            py = rect.top;
        }
        else if (alignment & ALIGN_BOTTOM)
        {
            py = rect.bottom - sizeY;
        }
        else if (alignment & ALIGN_VJUSTIFY)
        {
            py = rect.top;
            newSizeY = cy;
        }

        // move window INTo place
        if (newSizeX == sizeX && newSizeY == sizeY)
            SetWindowPos(hwnd, NULL, px, py, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
        else
            SetWindowPos(hwnd, NULL, px, py, newSizeX, newSizeY, SWP_NOZORDER);
    }