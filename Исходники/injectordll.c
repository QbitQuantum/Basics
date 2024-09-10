/*
    Función: GetTypeOfApp
    Descripción: Obtiene el tipo de programa en funcion de la espera en la carga
                 de su interface grafico.
    Parametros: 
        program_name            - Nombre y ruta del programa a checkear
        
    Retorno: 
        _GUI_APP__ 
        _CONS_APP__
        _UNK_APP__ 
*/
int 
GetTypeOfApp( LPTSTR program_name )
{
    STARTUPINFO           startup_info;
    PROCESS_INFORMATION   process_information;
    int                   return_function;
    
    memset( & startup_info, 0, sizeof( STARTUPINFO ) );
    
    return_function = _UNK_APP__;
    
    if 
    ( 
        CreateProcess
        (  
            NULL                                  ,
            program_name                          ,
            NULL                                  ,
            NULL                                  ,
            FALSE                                 ,
            CREATE_SUSPENDED | CREATE_NEW_CONSOLE ,      
            NULL                                  ,
            NULL                                  ,
            & startup_info                        ,
            & process_information
        ) 
        == 
        0 
    )
        ShowGetLastErrorString( "GetTypeOfApp:CreateProcess(program_name)" );
    else
    {
        if ( WaitForInputIdle( process_information.hProcess, 0 ) == WAIT_FAILED)
            return_function = _CONS_APP__;
        else
            return_function = _GUI_APP__;
    }
    
    if ( TerminateProcess( process_information.hProcess, 0) == 0 )
        ShowGetLastErrorString( "GetTypeOfApp:TerminateProcess(program)" );
    
    return return_function;
}