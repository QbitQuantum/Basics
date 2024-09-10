void LED_board::print_board(){
   for(int i = 0; i < NUM_ROW; i++){
        for(int j = 0; j < NUM_COL; j++){
            pc.printf("row_buffer[%d][%d] = %x\r\n", i, j, row_buffer[i][j]);
        }
    }
}