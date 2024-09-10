int main()
{
    // Initialize PortHandler instance
    // Set the port path
    // Get methods and members of PortHandlerLinux or PortHandlerWindows
    PortHandler *portHandler = PortHandler::GetPortHandler(DEVICENAME);

    // Initialize Packethandler instance
    // Set the protocol version
    // Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
    PacketHandler *packetHandler = PacketHandler::GetPacketHandler(PROTOCOL_VERSION);

    // Initialize Groupsyncwrite instance
    GroupSyncWrite groupSyncWrite(portHandler, packetHandler, ADDR_MX_GOAL_POSITION, LEN_MX_GOAL_POSITION);

    int index = 0;
    int dxl_comm_result = COMM_TX_FAIL;             // Communication result
    bool dxl_addparam_result = false;                // AddParam result
    int dxl_goal_position[2] = {DXL_MINIMUM_POSITION_VALUE, DXL_MAXIMUM_POSITION_VALUE};         // Goal position

    UINT8_T dxl_error = 0;                          // Dynamixel error
    UINT8_T param_goal_position[2];
    UINT16_T dxl1_present_position = 0, dxl2_present_position = 0;              // Present position

    // Open port
    if( portHandler->OpenPort() )
    {
        printf( "Succeeded to open the port!\n" );
    }
    else
    {
        printf( "Failed to open the port!\n" );
        printf( "Press any key to terminate...\n" );
        _getch();
        return 0;
    }

    // Set port baudrate
    if( portHandler->SetBaudRate(BAUDRATE) )
    {
        printf( "Succeeded to change the baudrate!\n" );
    }
    else
    {
        printf( "Failed to change the baudrate!\n" );
        printf( "Press any key to terminate...\n" );
        _getch();
        return 0;
    }

    // Enable Dynamixel#1 Torque
    dxl_comm_result = packetHandler->Write1ByteTxRx(portHandler, DXL1_ID, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
    if(dxl_comm_result != COMM_SUCCESS)
        packetHandler->PrintTxRxResult(dxl_comm_result);
    else if(dxl_error != 0)
        packetHandler->PrintRxPacketError(dxl_error);
    else
        printf("Dynamixel#%d has been successfully connected \n", DXL1_ID);

    // Enable Dynamixel#2 Torque
    dxl_comm_result = packetHandler->Write1ByteTxRx(portHandler, DXL2_ID, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
    if(dxl_comm_result != COMM_SUCCESS)
        packetHandler->PrintTxRxResult(dxl_comm_result);
    else if(dxl_error != 0)
        packetHandler->PrintRxPacketError(dxl_error);
    else
        printf("Dynamixel#%d has been successfully connected \n", DXL2_ID);

    while(1)
    {
        printf("Press any key to continue! (or press ESC to quit!)\n");
        if(_getch() == ESC_ASCII_VALUE)
            break;

        // Allocate goal position value into byte array
        param_goal_position[0] = DXL_LOBYTE(dxl_goal_position[index]);
        param_goal_position[1] = DXL_HIBYTE(dxl_goal_position[index]);

        // Add Dynamixel#1 goal position value to the Syncwrite storage
        dxl_addparam_result = groupSyncWrite.AddParam(DXL1_ID, param_goal_position);
        if( dxl_addparam_result != true )
        {
            fprintf(stderr, "[ID:%03d] groupSyncWrite addparam failed", DXL1_ID);
            return 0;
        }

        // Add Dynamixel#2 goal position value to the Syncwrite parameter storage
        dxl_addparam_result = groupSyncWrite.AddParam(DXL2_ID, param_goal_position);
        if( dxl_addparam_result != true )
        {
            fprintf(stderr, "[ID:%03d] groupSyncWrite addparam failed", DXL2_ID);
            return 0;
        }

        // Syncwrite goal position
        dxl_comm_result = groupSyncWrite.TxPacket();
        if(dxl_comm_result != COMM_SUCCESS)
            packetHandler->PrintTxRxResult(dxl_comm_result);

        // Clear syncwrite parameter storage
        groupSyncWrite.ClearParam();

        do
        {
            // Read Dynamixel#1 present position
            dxl_comm_result = packetHandler->Read2ByteTxRx(portHandler, DXL1_ID, ADDR_MX_PRESENT_POSITION, &dxl1_present_position, &dxl_error);
            if(dxl_comm_result != COMM_SUCCESS)
                packetHandler->PrintTxRxResult(dxl_comm_result);
            else if(dxl_error != 0)
                packetHandler->PrintRxPacketError(dxl_error);

            // Read Dynamixel#2 present position
            dxl_comm_result = packetHandler->Read2ByteTxRx(portHandler, DXL2_ID, ADDR_MX_PRESENT_POSITION, &dxl2_present_position, &dxl_error);
            if(dxl_comm_result != COMM_SUCCESS)
                packetHandler->PrintTxRxResult(dxl_comm_result);
            else if(dxl_error != 0)
                packetHandler->PrintRxPacketError(dxl_error);

            printf("[ID:%03d] GoalPos:%03d  PresPos:%03d\t[ID:%03d] GoalPos:%03d  PresPos:%03d\n", DXL1_ID, dxl_goal_position[index], dxl1_present_position, DXL2_ID, dxl_goal_position[index], dxl2_present_position);

        }while((abs(dxl_goal_position[index] - dxl1_present_position) > DXL_MOVING_STATUS_THRESHOLD) || (abs(dxl_goal_position[index] - dxl2_present_position) > DXL_MOVING_STATUS_THRESHOLD));

        // Change goal position
        if( index == 0 )
            index = 1;
        else
            index = 0;
    }

    // Disable Dynamixel#1 Torque
    dxl_comm_result = packetHandler->Write1ByteTxRx(portHandler, DXL1_ID, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
    if(dxl_comm_result != COMM_SUCCESS)
        packetHandler->PrintTxRxResult(dxl_comm_result);
    else if(dxl_error != 0)
        packetHandler->PrintRxPacketError(dxl_error);

    // Disable Dynamixel#2 Torque
    dxl_comm_result = packetHandler->Write1ByteTxRx(portHandler, DXL2_ID, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
    if(dxl_comm_result != COMM_SUCCESS)
        packetHandler->PrintTxRxResult(dxl_comm_result);
    else if(dxl_error != 0)
        packetHandler->PrintRxPacketError(dxl_error);


    // Close port
    portHandler->ClosePort();

    return 0;
}