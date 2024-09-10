void USART_Driver::CloseAllPorts()
{
    for( int port = 0; port < TOTAL_USART_PORT; port++)
    {
        if ( USART_FLAG_STATE(Hal_Usart_State[port], HAL_USART_STATE::c_INITIALIZED))
        {
            Uninitialize(port);
        }
    }
}