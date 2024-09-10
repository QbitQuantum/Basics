/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initSockets
 *  Description:  This function blocks the system until all connections are established
 * =====================================================================================
 */
void *initSockets(  ) {
    int i;

    for ( i = 0; i < g_num_players; i++ ) {
        openPort( g_players[i].port, &g_players[i].socket, &g_players[i].newsocket );
        g_players[i].connected = 1;
        glutPostRedisplay( );
    }

    /* Uncoment this if you want to start right away after all players are connected */
    startGame( );

    return NULL;
}