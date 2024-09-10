Keys::Keys() {
    catch_dist = conf.rfloat("game:key_catch_distance");

	num_keys = conf.rint("game:num_keys");
    keys_left = num_keys;
	float keys_min_distance = conf.rfloat("game:keys_min_distance");
	float keys_towers_distance = conf.rfloat("game:keys_towers:distance");

	keys = (Key **) calloc(num_keys, sizeof (Key *));

	for (int i = 0; i < num_keys; i++) {
	    keys[i] = new Key(conf.rstring("models:key"));
	    Vertex* pos = NULL;
	    do {
	     	pos = GLManager::randomVertex();
        	g_map->adjustPlayableCoords(pos);

	       	for(int j = 0; j < i && pos != NULL; j++) {
	       		if (pos->distance(keys[j]->coords) < keys_min_distance)
	       			pos = NULL;
	       	}
        	// as chaves nao podem estar muito proximas das torres
        	for(int j = 0; j < g_towers->num_towers && pos != NULL; j++) {
        		if (pos->distance(g_towers->towers[j]->coords) < keys_towers_distance)
        			pos = NULL;
        		}
        	// as chaves tem que ficar na area jogavel do terreno
        } while(pos == NULL);

		pos->y = g_map->triangulateHeight(pos->x, pos->z);
	    keys[i]->set_pos(pos);
    }

}