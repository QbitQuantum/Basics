/**
  Get selection for OneOf and OrderedList (Left/Right will be ignored).

  @param  MenuOption        Pointer to the current input menu.

  @retval EFI_SUCCESS       If Option input is processed successfully
  @retval EFI_DEVICE_ERROR  If operation fails

**/
EFI_STATUS
GetSelectionInputPopUp (
  IN  UI_MENU_OPTION              *MenuOption
  )
{
  EFI_STATUS              Status;
  EFI_INPUT_KEY           Key;
  UINTN                   Index;
  CHAR16                  *StringPtr;
  CHAR16                  *TempStringPtr;
  UINTN                   Index2;
  UINTN                   TopOptionIndex;
  UINTN                   HighlightOptionIndex;
  UINTN                   Start;
  UINTN                   End;
  UINTN                   Top;
  UINTN                   Bottom;
  UINTN                   PopUpMenuLines;
  UINTN                   MenuLinesInView;
  UINTN                   PopUpWidth;
  CHAR16                  Character;
  INT32                   SavedAttribute;
  BOOLEAN                 ShowDownArrow;
  BOOLEAN                 ShowUpArrow;
  UINTN                   DimensionsWidth;
  LIST_ENTRY              *Link;
  BOOLEAN                 OrderedList;
  UINT8                   *ValueArray;
  UINT8                   *ReturnValue;
  UINT8                   ValueType;
  EFI_HII_VALUE           HiiValue;
  DISPLAY_QUESTION_OPTION         *OneOfOption;
  DISPLAY_QUESTION_OPTION         *CurrentOption;
  FORM_DISPLAY_ENGINE_STATEMENT  *Question;
  INTN                    Result;
  EFI_IFR_ORDERED_LIST    *OrderList;

  DimensionsWidth   = gStatementDimensions.RightColumn - gStatementDimensions.LeftColumn;

  ValueArray        = NULL;
  ValueType         = 0;
  CurrentOption     = NULL;
  ShowDownArrow     = FALSE;
  ShowUpArrow       = FALSE;

  StringPtr = AllocateZeroPool ((gOptionBlockWidth + 1) * 2);
  ASSERT (StringPtr);

  ZeroMem (&HiiValue, sizeof (EFI_HII_VALUE));

  Question = MenuOption->ThisTag;
  if (Question->OpCode->OpCode == EFI_IFR_ORDERED_LIST_OP) {
    Link = GetFirstNode (&Question->OptionListHead);
    OneOfOption = DISPLAY_QUESTION_OPTION_FROM_LINK (Link);
    ValueArray = Question->CurrentValue.Buffer;
    ValueType =  OneOfOption->OptionOpCode->Type;
    OrderedList = TRUE;
    OrderList = (EFI_IFR_ORDERED_LIST *) Question->OpCode;
  } else {
    OrderedList = FALSE;
    OrderList = NULL;
  }

  //
  // Calculate Option count
  //
  PopUpMenuLines = 0;
  if (OrderedList) {
    AdjustOptionOrder(Question, &PopUpMenuLines);
  } else {
    Link = GetFirstNode (&Question->OptionListHead);
    while (!IsNull (&Question->OptionListHead, Link)) {
      OneOfOption = DISPLAY_QUESTION_OPTION_FROM_LINK (Link);
      PopUpMenuLines++;
      Link = GetNextNode (&Question->OptionListHead, Link);
    }
  }

  //
  // Get the number of one of options present and its size
  //
  PopUpWidth = 0;
  HighlightOptionIndex = 0;
  Link = GetFirstNode (&Question->OptionListHead);
  for (Index = 0; Index < PopUpMenuLines; Index++) {
    OneOfOption = DISPLAY_QUESTION_OPTION_FROM_LINK (Link);

    StringPtr = GetToken (OneOfOption->OptionOpCode->Option, gFormData->HiiHandle);
    if (StrLen (StringPtr) > PopUpWidth) {
      PopUpWidth = StrLen (StringPtr);
    }
    FreePool (StringPtr);
    HiiValue.Type = OneOfOption->OptionOpCode->Type;
    SetValuesByType (&HiiValue.Value, &OneOfOption->OptionOpCode->Value, HiiValue.Type);
    if (!OrderedList && (CompareHiiValue (&Question->CurrentValue, &HiiValue, &Result, NULL) == EFI_SUCCESS) && (Result == 0)) {
      //
      // Find current selected Option for OneOf
      //
      HighlightOptionIndex = Index;
    }

    Link = GetNextNode (&Question->OptionListHead, Link);
  }

  //
  // Perform popup menu initialization.
  //
  PopUpWidth = PopUpWidth + POPUP_PAD_SPACE_COUNT;

  SavedAttribute = gST->ConOut->Mode->Attribute;
  gST->ConOut->SetAttribute (gST->ConOut, GetPopupColor ());

  if ((PopUpWidth + POPUP_FRAME_WIDTH) > DimensionsWidth) {
    PopUpWidth = DimensionsWidth - POPUP_FRAME_WIDTH;
  }

  Start  = (DimensionsWidth - PopUpWidth - POPUP_FRAME_WIDTH) / 2 + gStatementDimensions.LeftColumn;
  End    = Start + PopUpWidth + POPUP_FRAME_WIDTH;
  Top    = gStatementDimensions.TopRow;
  Bottom = gStatementDimensions.BottomRow - 1;

  MenuLinesInView = Bottom - Top - 1;
  if (MenuLinesInView >= PopUpMenuLines) {
    Top     = Top + (MenuLinesInView - PopUpMenuLines) / 2;
    Bottom  = Top + PopUpMenuLines + 1;
  } else {
    ShowDownArrow = TRUE;
  }

  if (HighlightOptionIndex > (MenuLinesInView - 1)) {
    TopOptionIndex = HighlightOptionIndex - MenuLinesInView + 1;
  } else {
    TopOptionIndex = 0;
  }

  do {
    //
    // Clear that portion of the screen
    //
    ClearLines (Start, End, Top, Bottom, GetPopupColor ());

    //
    // Draw "One of" pop-up menu
    //
    Character = BOXDRAW_DOWN_RIGHT;
    PrintCharAt (Start, Top, Character);
    for (Index = Start; Index + 2 < End; Index++) {
      if ((ShowUpArrow) && ((Index + 1) == (Start + End) / 2)) {
        Character = GEOMETRICSHAPE_UP_TRIANGLE;
      } else {
        Character = BOXDRAW_HORIZONTAL;
      }

      PrintCharAt ((UINTN)-1, (UINTN)-1, Character);
    }

    Character = BOXDRAW_DOWN_LEFT;
    PrintCharAt ((UINTN)-1, (UINTN)-1, Character);
    Character = BOXDRAW_VERTICAL;
    for (Index = Top + 1; Index < Bottom; Index++) {
      PrintCharAt (Start, Index, Character);
      PrintCharAt (End - 1, Index, Character);
    }

    //
    // Move to top Option
    //
    Link = GetFirstNode (&Question->OptionListHead);
    for (Index = 0; Index < TopOptionIndex; Index++) {
      Link = GetNextNode (&Question->OptionListHead, Link);
    }

    //
    // Display the One of options
    //
    Index2 = Top + 1;
    for (Index = TopOptionIndex; (Index < PopUpMenuLines) && (Index2 < Bottom); Index++) {
      OneOfOption = DISPLAY_QUESTION_OPTION_FROM_LINK (Link);
      Link = GetNextNode (&Question->OptionListHead, Link);

      StringPtr = GetToken (OneOfOption->OptionOpCode->Option, gFormData->HiiHandle);
      ASSERT (StringPtr != NULL);
      //
      // If the string occupies multiple lines, truncate it to fit in one line,
      // and append a "..." for indication.
      //
      if (StrLen (StringPtr) > (PopUpWidth - 1)) {
        TempStringPtr = AllocateZeroPool (sizeof (CHAR16) * (PopUpWidth - 1));
        ASSERT ( TempStringPtr != NULL );
        CopyMem (TempStringPtr, StringPtr, (sizeof (CHAR16) * (PopUpWidth - 5)));
        FreePool (StringPtr);
        StringPtr = TempStringPtr;
        StrCat (StringPtr, L"...");
      }

      if (Index == HighlightOptionIndex) {
          //
          // Highlight the selected one
          //
          CurrentOption = OneOfOption;

          gST->ConOut->SetAttribute (gST->ConOut, GetPickListColor ());
          PrintStringAt (Start + 2, Index2, StringPtr);
          gST->ConOut->SetAttribute (gST->ConOut, GetPopupColor ());
        } else {
          gST->ConOut->SetAttribute (gST->ConOut, GetPopupColor ());
          PrintStringAt (Start + 2, Index2, StringPtr);
        }

      Index2++;
      FreePool (StringPtr);
    }

    Character = BOXDRAW_UP_RIGHT;
    PrintCharAt (Start, Bottom, Character);
    for (Index = Start; Index + 2 < End; Index++) {
      if ((ShowDownArrow) && ((Index + 1) == (Start + End) / 2)) {
        Character = GEOMETRICSHAPE_DOWN_TRIANGLE;
      } else {
        Character = BOXDRAW_HORIZONTAL;
      }

      PrintCharAt ((UINTN)-1, (UINTN)-1, Character);
    }

    Character = BOXDRAW_UP_LEFT;
    PrintCharAt ((UINTN)-1, (UINTN)-1, Character);

    //
    // Get User selection
    //
    Key.UnicodeChar = CHAR_NULL;
    if ((gDirection == SCAN_UP) || (gDirection == SCAN_DOWN)) {
      Key.ScanCode  = gDirection;
      gDirection    = 0;
      goto TheKey;
    }

    Status = WaitForKeyStroke (&Key);

TheKey:
    switch (Key.UnicodeChar) {
    case '+':
      if (OrderedList) {
        if ((TopOptionIndex > 0) && (TopOptionIndex == HighlightOptionIndex)) {
          //
          // Highlight reaches the top of the popup window, scroll one menu item.
          //
          TopOptionIndex--;
          ShowDownArrow = TRUE;
        }

        if (TopOptionIndex == 0) {
          ShowUpArrow = FALSE;
        }

        if (HighlightOptionIndex > 0) {
          HighlightOptionIndex--;

          ASSERT (CurrentOption != NULL);
          SwapListEntries (CurrentOption->Link.BackLink, &CurrentOption->Link);
        }
      }
      break;

    case '-':
      //
      // If an ordered list op-code, we will allow for a popup of +/- keys
      // to create an ordered list of items
      //
      if (OrderedList) {
        if (((TopOptionIndex + MenuLinesInView) < PopUpMenuLines) &&
            (HighlightOptionIndex == (TopOptionIndex + MenuLinesInView - 1))) {
          //
          // Highlight reaches the bottom of the popup window, scroll one menu item.
          //
          TopOptionIndex++;
          ShowUpArrow = TRUE;
        }

        if ((TopOptionIndex + MenuLinesInView) == PopUpMenuLines) {
          ShowDownArrow = FALSE;
        }

        if (HighlightOptionIndex < (PopUpMenuLines - 1)) {
          HighlightOptionIndex++;

          ASSERT (CurrentOption != NULL);
          SwapListEntries (&CurrentOption->Link, CurrentOption->Link.ForwardLink);
        }
      }
      break;

    case CHAR_NULL:
      switch (Key.ScanCode) {
      case SCAN_UP:
      case SCAN_DOWN:
        if (Key.ScanCode == SCAN_UP) {
          if ((TopOptionIndex > 0) && (TopOptionIndex == HighlightOptionIndex)) {
            //
            // Highlight reaches the top of the popup window, scroll one menu item.
            //
            TopOptionIndex--;
            ShowDownArrow = TRUE;
          }

          if (TopOptionIndex == 0) {
            ShowUpArrow = FALSE;
          }

          if (HighlightOptionIndex > 0) {
            HighlightOptionIndex--;
          }
        } else {
          if (((TopOptionIndex + MenuLinesInView) < PopUpMenuLines) &&
              (HighlightOptionIndex == (TopOptionIndex + MenuLinesInView - 1))) {
            //
            // Highlight reaches the bottom of the popup window, scroll one menu item.
            //
            TopOptionIndex++;
            ShowUpArrow = TRUE;
          }

          if ((TopOptionIndex + MenuLinesInView) == PopUpMenuLines) {
            ShowDownArrow = FALSE;
          }

          if (HighlightOptionIndex < (PopUpMenuLines - 1)) {
            HighlightOptionIndex++;
          }
        }
        break;

      case SCAN_ESC:
        gST->ConOut->SetAttribute (gST->ConOut, SavedAttribute);

        //
        // Restore link list order for orderedlist
        //
        if (OrderedList) {
          HiiValue.Type = ValueType;
          HiiValue.Value.u64 = 0;
          for (Index = 0; Index < OrderList->MaxContainers; Index++) {
            HiiValue.Value.u64 = GetArrayData (ValueArray, ValueType, Index);
            if (HiiValue.Value.u64 == 0) {
              break;
            }

            OneOfOption = ValueToOption (Question, &HiiValue);
            if (OneOfOption == NULL) {
              return EFI_NOT_FOUND;
            }

            RemoveEntryList (&OneOfOption->Link);
            InsertTailList (&Question->OptionListHead, &OneOfOption->Link);
          }
        }

        return EFI_DEVICE_ERROR;

      default:
        break;
      }

      break;

    case CHAR_CARRIAGE_RETURN:
      //
      // return the current selection
      //
      if (OrderedList) {
        ReturnValue = AllocateZeroPool (Question->CurrentValue.BufferLen);
        ASSERT (ReturnValue != NULL);
        Index = 0;
        Link = GetFirstNode (&Question->OptionListHead);
        while (!IsNull (&Question->OptionListHead, Link)) {
          OneOfOption = DISPLAY_QUESTION_OPTION_FROM_LINK (Link);
          Link = GetNextNode (&Question->OptionListHead, Link);

          SetArrayData (ReturnValue, ValueType, Index, OneOfOption->OptionOpCode->Value.u64);

          Index++;
          if (Index > OrderList->MaxContainers) {
            break;
          }
        }
        if (CompareMem (ReturnValue, ValueArray, Question->CurrentValue.BufferLen) == 0) {
          FreePool (ReturnValue);
          return EFI_DEVICE_ERROR;
        } else {
          gUserInput->InputValue.Buffer = ReturnValue;
          gUserInput->InputValue.BufferLen = Question->CurrentValue.BufferLen;
          Status = EFI_SUCCESS;
        }
      } else {
        ASSERT (CurrentOption != NULL);
        gUserInput->InputValue.Type = CurrentOption->OptionOpCode->Type;
        if (IsValuesEqual (&Question->CurrentValue.Value, &CurrentOption->OptionOpCode->Value, gUserInput->InputValue.Type)) {
          return EFI_DEVICE_ERROR;
        } else {
          SetValuesByType (&gUserInput->InputValue.Value, &CurrentOption->OptionOpCode->Value, gUserInput->InputValue.Type);
          Status = EFI_SUCCESS;
        }
      }

      gST->ConOut->SetAttribute (gST->ConOut, SavedAttribute);

      return EFI_SUCCESS;
      
    default:
      break;
    }
  } while (TRUE);

}