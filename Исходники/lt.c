void render(){
    int i, j;
    int color[3];
    int pos[2];

    for(i = 0; i < lastBlock; i++){
        color[0] = blockList[i].program[0] / 8.0 * 255;
        color[1] = blockList[i].program[INSTRUCTIONS / 2] / 8.0 * 255;
        color[2] = blockList[i].program[INSTRUCTIONS - 1] / 8.0 * 255;
        if(blockList[i].die){
            if(blockList[i].energy < 1){
                color[0] = color[0] - 70 < 0?0:color[0] - 70;
                color[1] = color[1] - 70 < 0?0:color[1] - 70;
                color[2] = color[2] - 70 < 0?0:color[2] - 70;
            }else{
                color[0] = color[0] - 90 < 0?0:color[0] - 70;
                color[1] = color[1] - 90 < 0?0:color[1] - 70;
                color[2] = color[2] - 90 < 0?0:color[2] - 70;
            }
        }
        pos[0] = blockList[i].x;
        pos[1] = blockList[i].y; 
        setpixel(pos[0], pos[1], color[0], color[1], color[2]);
    }
    SDL_Flip(screen);
    SDL_FillRect(screen, NULL, 0x000000);
}