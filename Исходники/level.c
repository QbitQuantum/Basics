level* level_load_file(char* filename) {
  
  for(int i = 0; i < num_tile_types; i++) {
    tile_counts[i] = 0;
  }
  
  level* l = malloc(sizeof(level));
  l->num_tile_sets = num_tile_types;
  l->tile_sets = malloc(sizeof(tile_set) * num_tile_types);
  l->tile_map = calloc(sizeof(int), MAX_WIDTH * MAX_HEIGHT);
  
  SDL_RWops* file = SDL_RWFromFile(filename, "r");
  char line[MAX_WIDTH];
  
  int y = 0;
  int x = 0;
  while(SDL_RWreadline(file, line, 1024)) {
    
    for(x = 0; x < strlen(line); x++) {
      char c = line[x];
      int type = tile_for_char(c);
      
      l->tile_map[x + y * MAX_WIDTH] = type;
      tile_counts[type]++;
    }
    
    y++;
  }
  
  SDL_RWclose(file);
  
  /* Start from 1, type 0 is none! */
  for(int i = 1; i < num_tile_types; i++) {
    
    int num_tiles = tile_counts[i];
    
    float* position_data = malloc(sizeof(float) * 3 * 4 * num_tiles);
    float* uv_data = malloc(sizeof(float) * 2 * 4 * num_tiles);
    
    int pos_i  = 0;
    int uv_i = 0;
    
    for(x = 0; x < MAX_WIDTH; x++)
    for(y = 0; y < MAX_HEIGHT; y++) {
      int type = l->tile_map[x + y * MAX_WIDTH];
      if( type == i ) {
        
        position_data[pos_i] = x * TILE_SIZE; pos_i++;
        position_data[pos_i] = y * TILE_SIZE; pos_i++;
        position_data[pos_i] = 0; pos_i++;
        
        position_data[pos_i] = (x+1) * TILE_SIZE; pos_i++;
        position_data[pos_i] = y * TILE_SIZE; pos_i++;
        position_data[pos_i] = 0; pos_i++;
        
        position_data[pos_i] = (x+1) * TILE_SIZE; pos_i++;
        position_data[pos_i] = (y+1) * TILE_SIZE; pos_i++;
        position_data[pos_i] = 0; pos_i++;
        
        position_data[pos_i] = x * TILE_SIZE; pos_i++;
        position_data[pos_i] = (y+1) * TILE_SIZE; pos_i++;
        position_data[pos_i] = 0; pos_i++;
        
        uv_data[uv_i] = 0; uv_i++;
        uv_data[uv_i] = 0; uv_i++;
        
        uv_data[uv_i] = 1; uv_i++;
        uv_data[uv_i] = 0; uv_i++;
        
        uv_data[uv_i] = 1; uv_i++;
        uv_data[uv_i] = 1; uv_i++;
        
        uv_data[uv_i] = 0; uv_i++;
        uv_data[uv_i] = 1; uv_i++;
        
      }
    }
    
    l->tile_sets[i].num_tiles = num_tiles;
    
    glGenBuffers(1, &l->tile_sets[i].positions_buffer);
    glGenBuffers(1, &l->tile_sets[i].texcoords_buffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, l->tile_sets[i].positions_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 4 * num_tiles, position_data, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, l->tile_sets[i].texcoords_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4 * num_tiles, uv_data, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    free(position_data);
    free(uv_data);
  
  }
    
  return l;
}