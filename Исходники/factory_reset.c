int main()
{
    // Initialize PortHandler Structs
    // Set the port path
    // Get methods and members of PortHandlerLinux or PortHandlerWindows
    int port_num = PortHandler(DEVICENAME);

    // Initialize PacketHandler Structs 
    PacketHandler();

    int dxl_comm_result = COMM_TX_FAIL;             // Communication result

    UINT8_T dxl_error = 0;                          // Dynamixel error
    UINT8_T dxl_baudnum_read;                       // Read baudnum

    // Open port
    if (OpenPort(port_num))
    {
        printf("Succeeded to open the port!\n");
    }
    else
    {
        printf("Failed to open the port!\n");
        printf("Press any key to terminate...\n");
        _getch();
        return 0;
    }

    // Set port baudrate
    if (SetBaudRate(port_num, BAUDRATE))
    {
        printf("Succeeded to change the baudrate!\n");
    }
    else
    {
        printf("Failed to change the baudrate!\n");
        printf("Press any key to terminate...\n");
        _getch();
        return 0;
    }

    // Read present baudrate of the controller
    printf("Now the controller baudrate is : %d\n", GetBaudRate(port_num));

    // Try factoryreset
    printf("[ID:%03d] Try factoryreset : ", DXL_ID);
    FactoryReset(port_num, PROTOCOL_VERSION, DXL_ID, OPERATION_MODE);
    if ((dxl_comm_result = GetLastTxRxResult(port_num, PROTOCOL_VERSION)) != COMM_SUCCESS)
    {
        printf("Aborted\n");
        PrintTxRxResult(PROTOCOL_VERSION, dxl_comm_result);
        return 0;
    }
    else if ((dxl_error = GetLastRxPacketError(port_num, PROTOCOL_VERSION)) != 0)
        PrintRxPacketError(PROTOCOL_VERSION, dxl_error);

    // Wait for reset
    printf("Wait for reset...\n");
    msecSleep(2000);

    printf("[ID:%03d] FactoryReset Success!\n", DXL_ID);

    // Set controller baudrate to Dynamixel default baudrate
    if (SetBaudRate(port_num, FACTORYRST_DEFAULTBAUDRATE))
    {
        printf("Succeed to change the controller baudrate to : %d\n", FACTORYRST_DEFAULTBAUDRATE);
    }
    else
    {
        printf("Failed to change the controller baudrate\n");
        printf("Press any key to terminate...\n");
        _getch();
        return 0;
    }

    // Read Dynamixel baudnum
    dxl_baudnum_read = Read1ByteTxRx(port_num, PROTOCOL_VERSION, DXL_ID, ADDR_PRO_BAUDRATE);
    if ((dxl_comm_result = GetLastTxRxResult(port_num, PROTOCOL_VERSION)) != COMM_SUCCESS)
        PrintTxRxResult(PROTOCOL_VERSION, dxl_comm_result);
    else if ((dxl_error = GetLastRxPacketError(port_num, PROTOCOL_VERSION)) != 0)
        PrintRxPacketError(PROTOCOL_VERSION, dxl_error);
    else
        printf("[ID:%03d] DXL baudnum is now : %d\n", DXL_ID, dxl_baudnum_read);

    // Write new baudnum
    Write1ByteTxRx(port_num, PROTOCOL_VERSION, DXL_ID, ADDR_PRO_BAUDRATE, NEW_BAUDNUM);
    if ((dxl_comm_result = GetLastTxRxResult(port_num, PROTOCOL_VERSION)) != COMM_SUCCESS)
        PrintTxRxResult(PROTOCOL_VERSION, dxl_comm_result);
    else if ((dxl_error = GetLastRxPacketError(port_num, PROTOCOL_VERSION)) != 0)
        PrintRxPacketError(PROTOCOL_VERSION, dxl_error);
    else
        printf("[ID:%03d] Set Dynamixel baudnum to : %d\n", DXL_ID, NEW_BAUDNUM);

    // Set port baudrate to BAUDRATE
    if (SetBaudRate(port_num, BAUDRATE))
    {
        printf("Succeed to change the controller baudrate to : %d\n", BAUDRATE);
    }
    else
    {
        printf("Failed to change the controller baudrate\n");
        printf("Press any key to terminate...\n");
        _getch();
        return 0;
    }

    msecSleep(200);

    // Read Dynamixel baudnum
    dxl_baudnum_read = Read1ByteTxRx(port_num, PROTOCOL_VERSION, DXL_ID, ADDR_PRO_BAUDRATE);
    if ((dxl_comm_result = GetLastTxRxResult(port_num, PROTOCOL_VERSION)) != COMM_SUCCESS)
        PrintTxRxResult(PROTOCOL_VERSION, dxl_comm_result);
    else if ((dxl_error = GetLastRxPacketError(port_num, PROTOCOL_VERSION)) != 0)
        PrintRxPacketError(PROTOCOL_VERSION, dxl_error);
    else
        printf("[ID:%03d] Dynamixel Baudnum is now : %d\n", DXL_ID, dxl_baudnum_read);

    // Close port
    ClosePort(port_num);

    return 0;
}