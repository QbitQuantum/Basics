void preprocess(FILE* inf, wave_object_t *obj) {
    /*
      Scan through the file and count the number of vertices, texture
      coordinates, normals and faces
    */
    // Save original position in file
    size_t nv=0;
    size_t nn=0;
    size_t nt=0;
    size_t nf=0;
    size_t no = 0;
    char in_buffer[512] = "";
    size_t blen = 0;
    
    fpos_t original_pos;
    fgetpos(inf, &original_pos);

    // Go to the beginnning
    rewind(inf);

    while (!feof(inf)) {
        char *fgs = fgets(in_buffer, 512, inf);
        if (fgs == NULL) continue;
        blen = strlen(in_buffer);
        in_buffer[blen-1] = '\0';
        --blen;
        if (in_buffer[blen-1] == '\r') {
            in_buffer[blen-1] ='\0';
            --blen;
        }
        if (blen == 0) continue;
        enum obj_entry_type obj_type = get_entry_type(in_buffer);

        switch (obj_type) {
        case vertex:
            ++nv;
            break;
        case normal:
            ++nn;
            break;
        case text_coord:
            ++nt;
            break;
        case face:
            ++nf;
            break;
        case object:
            ++no;
            read_object_type(in_buffer, obj);
            break;
        default:
            break;
        }
    }
    obj->num_verts = nv;
    obj->verts = malloc(sizeof(RtPoint) * nv);
    
    obj->num_norms = nn;
    obj->norms = malloc(sizeof(RtPoint) * nn);
    
    obj->num_texts = nt;
    obj->text_coords = malloc(sizeof(text_coord_t) * nt);
    
    obj->num_faces = nf;
    obj->faces = malloc(sizeof(face_t) * nf);

    // Return to original position
    fsetpos(inf, &original_pos);
}