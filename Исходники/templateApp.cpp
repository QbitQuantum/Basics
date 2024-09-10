void templateAppInit(int width, int height) {

    atexit(templateAppExit);

    gfx = new GFX;

    glViewport(0.0f, 0.0f, width, height);

    gfx->set_matrix_mode(PROJECTION_MATRIX);
    gfx->load_identity();
    // Adjust "Field of View Y" angle for devices which has an aspect
    // ratio which is wider than the origin iPhone (3:2).  Devices which
    // have a narrower aspect ratio (such as iPad) work fine, as is.
    const float iPhoneOriginalWidth =320.0f;
    const float iPhoneOriginalHeight=480.0f;
    const float originalFovy=45.0f;
    float fovy(originalFovy);
    if (height*iPhoneOriginalWidth > width*iPhoneOriginalHeight) {
        float   h = (iPhoneOriginalHeight*0.5f) / tanf(originalFovy*0.5f*DEG_TO_RAD);
        fovy = 2.0f * atan2f(((float)height)*0.5, h) * RAD_TO_DEG;
    }
    gfx->set_perspective(fovy,
                         (float)width / (float)height,
                           0.1f,
                         100.0f,
                           0.0f);

    obj = new OBJ(OBJ_FILE, true);

    for (auto objmesh=obj->objmesh.begin();
         objmesh!=obj->objmesh.end(); ++objmesh) {
        console_print("%s: %d: GL_TRIANGLES\n",
                      objmesh->name,
                      objmesh->objtrianglelist[0].n_indice_array);

        /* Built-in method that implements the NvTriStrip library.
         * For more information, check the obj.cpp source code in
         * order to implement it inside your own apps.
         */
        objmesh->optimize(128);

        console_print("%s: %d: GL_TRIANGLE_STRIP\n",
                      objmesh->name,
                      objmesh->objtrianglelist[0].n_indice_array);


        objmesh->build();

        objmesh->free_vertex_data();
    }


    for (auto texture=obj->texture.begin();
         texture!=obj->texture.end(); ++texture) {
        (*texture)->build(obj->texture_path,
                          TEXTURE_MIPMAP | TEXTURE_16_BITS, // Automatically convert the texture to 16 bits.
                          TEXTURE_FILTER_2X,
                          0.0f);
    }


    for (auto objmaterial=obj->objmaterial.begin();
         objmaterial!=obj->objmaterial.end(); ++objmaterial) {
        objmaterial->build(new PROGRAM((char *)"default",
                                       VERTEX_SHADER,
                                       FRAGMENT_SHADER,
                                       true,
                                       true,
                                       program_bind_attrib_location,
                                       NULL));
        
        objmaterial->set_draw_callback(material_draw_callback);
    }
}