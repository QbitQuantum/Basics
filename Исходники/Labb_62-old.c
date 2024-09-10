void inputItem(ItemStruct* ior_item)
{
    int numberOfArgumentsRecived;
    int okFlag;

    do
    {
        //TODO (Extra): Blanka alla ch_arr innan vi skriver till dem!!
        printf_s("Name of item %d: ", (*ior_item).isId);
        okFlag = readLine(ior_item->isName, sizeof(ior_item->isName));

        if (ior_item->isName[0] == '\0')
        {
            printf_s("Name cannot be empty!\n");
            okFlag = FALSE;
        }
        else if (okFlag == FALSE)
        {
            // Inmatningen är för lång.
            printf_s("WARNING! The entered Name has been truncated!\n");
            okFlag = TRUE;
        }
        // scanf_s("%s", &ior_item->isName[0], sizeof(ior_item->isName)); // Bryter vid mellanslag
        // flushRestOfLine();
    } while (!okFlag);

    do
    {
        printf_s("Number of this item: ");
        numberOfArgumentsRecived = scanf_s("%f", &ior_item->isAmount); // Space after %f replaces flushRestOfLine
        flushRestOfLine();

        if (numberOfArgumentsRecived == 1)
        {
            break;
        }
        else
        {
            printf_s("*** Please enter a number! ***\n");
        }
    } while (TRUE);

    printf_s("Enter the Unit: ");
    okFlag = readLine(ior_item->isUnit, sizeof(ior_item->isUnit));

    // scanf_s("%s", &ior_item->isUnit[0], C_UNIT_NAME_LENGTH);
    // flushRestOfLine();
} // inputItem