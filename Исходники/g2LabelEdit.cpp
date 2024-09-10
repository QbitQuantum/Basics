void g2LabelEdit::PasteBuffer()
{
    // Win32 implementation
    #ifdef _WIN32
    
        // Attempt to open clipboard
        if(!OpenClipboard(GetForegroundWindow()))
            return;
        
        // Get the windows clipboard text buffer
        HGLOBAL ClipboardHandle = GetClipboardData(CF_TEXT);
        if(ClipboardHandle != NULL)
        {
            // Actually copy the text
            LPTSTR StringLock = (LPTSTR)GlobalLock(ClipboardHandle); 
            if (StringLock != NULL) 
            {
                // Copy as much as we can
                char TempClipBuffer[g2LabelEdit_TextBufferLength];
                strncpy(TempClipBuffer, StringLock, g2LabelEdit_TextBufferLength - strlen(TextBuffer) - strlen(StringLock) - 1);
                
                // Copy the current text buffer
                char TempTextBuffer[g2LabelEdit_TextBufferLength];
                strcpy(TempTextBuffer, TextBuffer);
                
                // Copy into the full buffer (only if text is small enough)
                if(strlen(TempTextBuffer) + strlen(TempClipBuffer) + 1 < g2LabelEdit_TextBufferLength)
                {
                    char NewTextBuffer[g2LabelEdit_TextBufferLength];
                    sprintf(NewTextBuffer, "%s%s", TempTextBuffer, TempClipBuffer);
                    SetText(NewTextBuffer);
                }
                
                // Release the lock
                GlobalUnlock(StringLock); 
            }
        }
        
        // Close clipboard
        CloseClipboard();
    
    // OSX implementation
    #elif __APPLE__
    
        // Allocate or get a reference to the application's active clipboard
        PasteboardRef ClipboardHandle;
        if(PasteboardCreate(kPasteboardClipboard, &ClipboardHandle) != noErr)
            return;
        
        // Explicitly update (possibly not needed...)
        PasteboardSynchronize(ClipboardHandle);
        
        // Get the item count
        ItemCount ClipboardItems;
        if(PasteboardGetItemCount(ClipboardHandle, &ClipboardItems) != noErr)
            return;
        
        // Keep searching until we find valid text
        for(ItemCount ItemIndex = 1; ItemIndex <= ClipboardItems; ItemIndex++)
        {
            // Get item's ID
            PasteboardItemID ItemID;
            if(PasteboardGetItemIdentifier(ClipboardHandle, ItemIndex, &ItemID) != noErr)
                continue;
            
            // Get this item's data types
            CFArrayRef ItemTypes;
            if(PasteboardCopyItemFlavors(ClipboardHandle, ItemID, &ItemTypes) != noErr)
                continue;
            
            // For each data type for this clipboard item
            CFIndex ItemCount = CFArrayGetCount(ItemTypes);
            for(CFIndex ItemTypeIndex = 0; ItemTypeIndex < ItemCount; ItemTypeIndex++)
            {
                // Get the data type
                CFStringRef ItemType = (CFStringRef)CFArrayGetValueAtIndex(ItemTypes, ItemTypeIndex);
                
                // If we have any text-type, then paste and stop
                if(UTTypeConformsTo(ItemType, CFSTR("public.utf8-plain-text")))
                {
                    // Copy from clipboard
                    CFDataRef ItemData;
                    if(PasteboardCopyItemFlavorData(ClipboardHandle, ItemID, ItemType, &ItemData) != noErr)
                        continue;
                    
                    // Paste into active buffer
                    CFIndex DateLength = CFDataGetLength(ItemData);
                    size_t StartIndex = strlen(TextBuffer);
                    
                    char NewTempBuffer[g2LabelEdit_TextBufferLength];
                    strcpy(NewTempBuffer, TextBuffer);
                    
                    for(CFIndex i = 0; (i < DateLength) && (StartIndex + i < g2LabelEdit_TextBufferLength); i++)
                    {
                        char byte = *(CFDataGetBytePtr(ItemData) + i);
                        NewTempBuffer[StartIndex + i] = byte;
                    }
                    
                    // Cap string and set to current buffer
                    NewTempBuffer[StartIndex + DateLength] = '\0';
                    SetText(NewTempBuffer);
                    SetCursorPos((int)strlen(NewTempBuffer));
                    
                    // Release
                    CFRelease(ItemData);
                    
                    // Pasted and done!
                    return;
                }
            }
        }
    
    // Linux clipboard implementation
    #elif __linux__
    
        // Paste into UI from linux buffer
        SetText(__LinuxClipboard);
        SetCursorPos((int)strlen(__LinuxClipboard));
    
    #endif
}