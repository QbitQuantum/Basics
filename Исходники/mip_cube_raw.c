int main(int argc, char **argv)
{
    int rv;
    int width = 256;
    int height = 256;
    int padded_width, padded_height;
    
    fb_info fb;
    rv = fb_open(0, &fb);
    if(rv!=0)
    {
        exit(1);
    }
    width = fb.fb_var.xres;
    height = fb.fb_var.yres;
    padded_width = etna_align_up(width, 64);
    padded_height = etna_align_up(height, 64);

    printf("padded_width %i padded_height %i\n", padded_width, padded_height);
    rv = viv_open();
    if(rv!=0)
    {
        fprintf(stderr, "Error opening device\n");
        exit(1);
    }
    printf("Succesfully opened device\n");

    etna_ctx *ctx = 0;
    if(etna_create(&ctx) != ETNA_OK)
    {
        printf("Unable to create context\n");
        exit(1);
    }

    /* Initialize buffers synchronization structure */
    etna_bswap_buffers *buffers = 0;
    if(etna_bswap_create(ctx, &buffers, (int (*)(void *, int))&fb_set_buffer, NULL, &fb) < 0)
    {
        fprintf(stderr, "Error creating buffer swapper\n");
        exit(1);
    }

    /* Allocate video memory */
    etna_vidmem *rt = 0; /* main render target */
    etna_vidmem *rt_ts = 0; /* tile status for main render target */
    etna_vidmem *z = 0; /* depth for main render target */
    etna_vidmem *z_ts = 0; /* depth ts for main render target */
    etna_vidmem *vtx = 0; /* vertex buffer */
    etna_vidmem *aux_rt = 0; /* auxilary render target */
    etna_vidmem *aux_rt_ts = 0; /* tile status for auxilary render target */
    etna_vidmem *tex = 0; /* texture */

    size_t rt_size = padded_width * padded_height * 4;
    size_t rt_ts_size = etna_align_up((padded_width * padded_height * 4)/0x100, 0x100);
    size_t z_size = padded_width * padded_height * 2;
    size_t z_ts_size = etna_align_up((padded_width * padded_height * 2)/0x100, 0x100);

    dds_texture *dds = 0;
    if(argc<2 || !dds_load(argv[1], &dds))
    {
        printf("Error loading texture\n");
        exit(1);
    }

    if(etna_vidmem_alloc_linear(&rt, rt_size, gcvSURF_RENDER_TARGET, gcvPOOL_DEFAULT, true)!=ETNA_OK ||
       etna_vidmem_alloc_linear(&rt_ts, rt_ts_size, gcvSURF_TILE_STATUS, gcvPOOL_DEFAULT, true)!=ETNA_OK ||
       etna_vidmem_alloc_linear(&z, z_size, gcvSURF_DEPTH, gcvPOOL_DEFAULT, true)!=ETNA_OK ||
       etna_vidmem_alloc_linear(&z_ts, z_ts_size, gcvSURF_TILE_STATUS, gcvPOOL_DEFAULT, true)!=ETNA_OK ||
       etna_vidmem_alloc_linear(&vtx, VERTEX_BUFFER_SIZE, gcvSURF_VERTEX, gcvPOOL_DEFAULT, true)!=ETNA_OK ||
       etna_vidmem_alloc_linear(&aux_rt, 0x4000, gcvSURF_RENDER_TARGET, gcvPOOL_SYSTEM, true)!=ETNA_OK ||
       etna_vidmem_alloc_linear(&aux_rt_ts, 0x100, gcvSURF_TILE_STATUS, gcvPOOL_DEFAULT, true)!=ETNA_OK ||
       etna_vidmem_alloc_linear(&tex, dds->size, gcvSURF_TEXTURE, gcvPOOL_DEFAULT, true)!=ETNA_OK
       )
    {
        fprintf(stderr, "Error allocating video memory\n");
        exit(1);
    }

    uint32_t tex_format = 0;
    uint32_t tex_base_width = dds->slices[0][0].width;
    uint32_t tex_base_height = dds->slices[0][0].height;
    uint32_t tex_base_log_width = (int)(logf(tex_base_width) * RCPLOG2 * 32.0f + 0.5f);
    uint32_t tex_base_log_height = (int)(logf(tex_base_height) * RCPLOG2 * 32.0f + 0.5f);
    printf("Loading compressed texture (format %i, %ix%i) log_width=%i log_height=%i\n", dds->fmt, tex_base_width, tex_base_height, tex_base_log_width, tex_base_log_height);
    if(dds->fmt == FMT_X8R8G8B8 || dds->fmt == FMT_A8R8G8B8)
    {
        for(int ix=0; ix<dds->num_mipmaps; ++ix)
        {
            printf("%08x: Tiling mipmap %i (%ix%i)\n", dds->slices[0][ix].offset, ix, dds->slices[0][ix].width, dds->slices[0][ix].height);
            etna_texture_tile((void*)((size_t)tex->logical + dds->slices[0][ix].offset), 
                    dds->slices[0][ix].data, dds->slices[0][ix].width, dds->slices[0][ix].height, dds->slices[0][ix].stride, 4);
        }
        tex_format = TEXTURE_FORMAT_X8R8G8B8;
    } else if(dds->fmt == FMT_DXT1 || dds->fmt == FMT_DXT3 || dds->fmt == FMT_DXT5 || dds->fmt == FMT_ETC1)
    {
        printf("Uploading compressed texture\n");
        memcpy(tex->logical, dds->data, dds->size);
        switch(dds->fmt)
        {
        case FMT_DXT1: tex_format = TEXTURE_FORMAT_DXT1; break;
        case FMT_DXT3: tex_format = TEXTURE_FORMAT_DXT2_DXT3; break;
        case FMT_DXT5: tex_format = TEXTURE_FORMAT_DXT4_DXT5; break;
        case FMT_ETC1: tex_format = TEXTURE_FORMAT_ETC1; break;
        }
    } else
    {
        printf("Unknown texture format\n");
        exit(1);
    }

    /* Phew, now we got all the memory we need.
     * Write interleaved attribute vertex stream.
     * Unlike the GL example we only do this once, not every time glDrawArrays is called, the same would be accomplished
     * from GL by using a vertex buffer object.
     */
    for(int vert=0; vert<NUM_VERTICES; ++vert)
    {
        int dest_idx = vert * (3 + 3 + 2);
        for(int comp=0; comp<3; ++comp)
            ((float*)vtx->logical)[dest_idx+comp+0] = vVertices[vert*3 + comp]; /* 0 */
        for(int comp=0; comp<3; ++comp)
            ((float*)vtx->logical)[dest_idx+comp+3] = vNormals[vert*3 + comp]; /* 1 */
        for(int comp=0; comp<2; ++comp)
            ((float*)vtx->logical)[dest_idx+comp+6] = vTexCoords[vert*2 + comp]; /* 2 */
    }

    for(int frame=0; frame<1000; ++frame)
    {
        if(frame%50 == 0)
            printf("*** FRAME %i ****\n", frame);
        /*   Compute transform matrices in the same way as cube egl demo */ 
        ESMatrix modelview, projection, modelviewprojection;
        ESMatrix inverse, normal; 
        esMatrixLoadIdentity(&modelview);
        esTranslate(&modelview, 0.0f, 0.0f, -8.0f);
        esRotate(&modelview, 45.0f, 1.0f, 0.0f, 0.0f);
        esRotate(&modelview, 45.0f, 0.0f, 1.0f, 0.0f);
        esRotate(&modelview, frame*0.5f, 0.0f, 0.0f, 1.0f);
        GLfloat aspect = (GLfloat)(height) / (GLfloat)(width);
        esMatrixLoadIdentity(&projection);
        esFrustum(&projection, -2.8f, +2.8f, -2.8f * aspect, +2.8f * aspect, 6.0f, 10.0f);
        esMatrixLoadIdentity(&modelviewprojection);
        esMatrixMultiply(&modelviewprojection, &modelview, &projection);
        esMatrixInverse3x3(&inverse, &modelview);
        esMatrixTranspose(&normal, &inverse);

        /* XXX part of this can be put outside the loop, but until we have usable context management
         * this is safest.
         */
        etna_set_state(ctx, VIVS_RA_CONTROL, 0x3);
        
        etna_set_state(ctx, VIVS_GL_MULTI_SAMPLE_CONFIG, 
                VIVS_GL_MULTI_SAMPLE_CONFIG_MSAA_SAMPLES_NONE |
                VIVS_GL_MULTI_SAMPLE_CONFIG_MSAA_ENABLES(0xf) /*|
                VIVS_GL_MULTI_SAMPLE_CONFIG_UNK12 |
                VIVS_GL_MULTI_SAMPLE_CONFIG_UNK16 */
                ); 
        etna_set_state(ctx, VIVS_GL_VERTEX_ELEMENT_CONFIG, 0x1);
        etna_set_state(ctx, VIVS_GL_VARYING_NUM_COMPONENTS,  
                VIVS_GL_VARYING_NUM_COMPONENTS_VAR0(4)| /* position */
                VIVS_GL_VARYING_NUM_COMPONENTS_VAR1(2)  /* texture coordinate */
                );
        etna_set_state(ctx, VIVS_GL_VARYING_TOTAL_COMPONENTS,
                VIVS_GL_VARYING_TOTAL_COMPONENTS_NUM(4 + 2)
                );
        etna_set_state_multi(ctx, VIVS_GL_VARYING_COMPONENT_USE(0), 2, (uint32_t[]){
                VIVS_GL_VARYING_COMPONENT_USE_COMP0(VARYING_COMPONENT_USE_USED) |
                VIVS_GL_VARYING_COMPONENT_USE_COMP1(VARYING_COMPONENT_USE_USED) |
                VIVS_GL_VARYING_COMPONENT_USE_COMP2(VARYING_COMPONENT_USE_USED) |
                VIVS_GL_VARYING_COMPONENT_USE_COMP3(VARYING_COMPONENT_USE_USED) |
                VIVS_GL_VARYING_COMPONENT_USE_COMP4(VARYING_COMPONENT_USE_USED) |
                VIVS_GL_VARYING_COMPONENT_USE_COMP5(VARYING_COMPONENT_USE_USED)
                , 0
                });

        etna_set_state(ctx, VIVS_PA_W_CLIP_LIMIT, 0x34000001);
        etna_set_state(ctx, VIVS_PA_SYSTEM_MODE, 0x11);
        etna_set_state(ctx, VIVS_PA_CONFIG, /* VIVS_PA_CONFIG_UNK22 | */
                                            VIVS_PA_CONFIG_CULL_FACE_MODE_CCW |
                                            VIVS_PA_CONFIG_FILL_MODE_SOLID |
                                            VIVS_PA_CONFIG_SHADE_MODEL_SMOOTH /* |
                                            VIVS_PA_CONFIG_POINT_SIZE_ENABLE |
                                            VIVS_PA_CONFIG_POINT_SPRITE_ENABLE*/);
        etna_set_state_f32(ctx, VIVS_PA_VIEWPORT_OFFSET_Z, 0.0);
        etna_set_state_f32(ctx, VIVS_PA_VIEWPORT_SCALE_Z, 1.0);
        etna_set_state_fixp(ctx, VIVS_PA_VIEWPORT_OFFSET_X, width << 15);
        etna_set_state_fixp(ctx, VIVS_PA_VIEWPORT_OFFSET_Y, height << 15);
        etna_set_state_fixp(ctx, VIVS_PA_VIEWPORT_SCALE_X, width << 15);
        etna_set_state_fixp(ctx, VIVS_PA_VIEWPORT_SCALE_Y, height << 15);
        etna_set_state(ctx, VIVS_PA_ATTRIBUTE_ELEMENT_COUNT, 0x200);
        etna_set_state(ctx, VIVS_PA_SHADER_ATTRIBUTES(0), 0x200);
        etna_set_state(ctx, VIVS_PA_SHADER_ATTRIBUTES(1), 0x200);

        etna_set_state(ctx, VIVS_SE_CONFIG, 0x0);
        etna_set_state(ctx, VIVS_SE_DEPTH_SCALE, 0x0);
        etna_set_state(ctx, VIVS_SE_DEPTH_BIAS, 0x0);
        etna_set_state_fixp(ctx, VIVS_SE_SCISSOR_LEFT, 0);
        etna_set_state_fixp(ctx, VIVS_SE_SCISSOR_TOP, 0);
        etna_set_state_fixp(ctx, VIVS_SE_SCISSOR_RIGHT, (width << 16) | 5);
        etna_set_state_fixp(ctx, VIVS_SE_SCISSOR_BOTTOM, (height << 16) | 5);

        etna_set_state(ctx, VIVS_PE_ALPHA_CONFIG,
                /* VIVS_PE_ALPHA_CONFIG_BLEND_ENABLE_COLOR | */
                /* VIVS_PE_ALPHA_CONFIG_BLEND_ENABLE_ALPHA | */
                VIVS_PE_ALPHA_CONFIG_SRC_FUNC_COLOR(BLEND_FUNC_ONE) |
                VIVS_PE_ALPHA_CONFIG_SRC_FUNC_ALPHA(BLEND_FUNC_ONE) |
                VIVS_PE_ALPHA_CONFIG_DST_FUNC_COLOR(BLEND_FUNC_ZERO) |
                VIVS_PE_ALPHA_CONFIG_DST_FUNC_ALPHA(BLEND_FUNC_ZERO) |
                VIVS_PE_ALPHA_CONFIG_EQ_COLOR(BLEND_EQ_ADD) |
                VIVS_PE_ALPHA_CONFIG_EQ_ALPHA(BLEND_EQ_ADD));
        etna_set_state(ctx, VIVS_PE_ALPHA_BLEND_COLOR, 
                VIVS_PE_ALPHA_BLEND_COLOR_B(0) | 
                VIVS_PE_ALPHA_BLEND_COLOR_G(0) | 
                VIVS_PE_ALPHA_BLEND_COLOR_R(0) | 
                VIVS_PE_ALPHA_BLEND_COLOR_A(0));
        etna_set_state(ctx, VIVS_PE_ALPHA_OP, /* VIVS_PE_ALPHA_OP_ALPHA_TEST */ 0);
        etna_set_state(ctx, VIVS_PE_STENCIL_CONFIG, VIVS_PE_STENCIL_CONFIG_REF_FRONT(0) |
                                                    VIVS_PE_STENCIL_CONFIG_MASK_FRONT(0xff) | 
                                                    VIVS_PE_STENCIL_CONFIG_WRITE_MASK(0xff) |
                                                    VIVS_PE_STENCIL_CONFIG_MODE_DISABLED);
        etna_set_state(ctx, VIVS_PE_STENCIL_OP, VIVS_PE_STENCIL_OP_FUNC_FRONT(COMPARE_FUNC_ALWAYS) |
                                                VIVS_PE_STENCIL_OP_FUNC_BACK(COMPARE_FUNC_ALWAYS) |
                                                VIVS_PE_STENCIL_OP_FAIL_FRONT(STENCIL_OP_KEEP) | 
                                                VIVS_PE_STENCIL_OP_FAIL_BACK(STENCIL_OP_KEEP) |
                                                VIVS_PE_STENCIL_OP_DEPTH_FAIL_FRONT(STENCIL_OP_KEEP) |
                                                VIVS_PE_STENCIL_OP_DEPTH_FAIL_BACK(STENCIL_OP_KEEP) |
                                                VIVS_PE_STENCIL_OP_PASS_FRONT(STENCIL_OP_KEEP) |
                                                VIVS_PE_STENCIL_OP_PASS_BACK(STENCIL_OP_KEEP));
        etna_set_state(ctx, VIVS_PE_COLOR_FORMAT, 
                VIVS_PE_COLOR_FORMAT_COMPONENTS(0xf) |
                VIVS_PE_COLOR_FORMAT_FORMAT(RS_FORMAT_X8R8G8B8) |
                VIVS_PE_COLOR_FORMAT_SUPER_TILED |
                VIVS_PE_COLOR_FORMAT_OVERWRITE);
        etna_set_state(ctx, VIVS_PE_DEPTH_CONFIG, 
                VIVS_PE_DEPTH_CONFIG_DEPTH_FORMAT_D16 |
                VIVS_PE_DEPTH_CONFIG_SUPER_TILED |
                VIVS_PE_DEPTH_CONFIG_EARLY_Z |
                /* VIVS_PE_DEPTH_CONFIG_WRITE_ENABLE | */
                VIVS_PE_DEPTH_CONFIG_DEPTH_FUNC(COMPARE_FUNC_ALWAYS) |
                VIVS_PE_DEPTH_CONFIG_DEPTH_MODE_Z
                /* VIVS_PE_DEPTH_CONFIG_ONLY_DEPTH */
                );
        etna_set_state(ctx, VIVS_PE_DEPTH_ADDR, z->address);
        etna_set_state(ctx, VIVS_PE_DEPTH_STRIDE, padded_width * 2);
        etna_set_state(ctx, VIVS_PE_HDEPTH_CONTROL, VIVS_PE_HDEPTH_CONTROL_FORMAT_DISABLED);
        etna_set_state_f32(ctx, VIVS_PE_DEPTH_NORMALIZE, 65535.0);
        etna_set_state(ctx, VIVS_PE_COLOR_ADDR, rt->address);
        etna_set_state(ctx, VIVS_PE_COLOR_STRIDE, padded_width * 4); 
        etna_set_state_f32(ctx, VIVS_PE_DEPTH_NEAR, 0.0);
        etna_set_state_f32(ctx, VIVS_PE_DEPTH_FAR, 1.0);
        etna_set_state_f32(ctx, VIVS_PE_DEPTH_NORMALIZE, 65535.0);

        etna_set_state(ctx, VIVS_GL_FLUSH_CACHE, VIVS_GL_FLUSH_CACHE_COLOR | VIVS_GL_FLUSH_CACHE_DEPTH);
        etna_set_state(ctx, VIVS_RS_FLUSH_CACHE, VIVS_RS_FLUSH_CACHE_FLUSH);
        etna_stall(ctx, SYNC_RECIPIENT_RA, SYNC_RECIPIENT_PE);

        /* Set up the resolve to clear tile status for main render target 
         * Regard the TS plane as an image of width 16 with 4 bytes per pixel (64 bytes per row)
         * XXX need to clear the depth ts too? we don't really use depth buffer in this sample
         * */
        etna_set_state(ctx, VIVS_TS_MEM_CONFIG, 0);
        etna_set_state(ctx, VIVS_RS_CONFIG,
                VIVS_RS_CONFIG_SOURCE_FORMAT(RS_FORMAT_X8R8G8B8) |
                VIVS_RS_CONFIG_DEST_FORMAT(RS_FORMAT_X8R8G8B8)
                );
        etna_set_state_multi(ctx, VIVS_RS_DITHER(0), 2, (uint32_t[]){0xffffffff, 0xffffffff});
        etna_set_state(ctx, VIVS_RS_DEST_ADDR, rt_ts->address); /* ADDR_B */
        etna_set_state(ctx, VIVS_RS_DEST_STRIDE, 0x40);
        etna_set_state(ctx, VIVS_RS_WINDOW_SIZE, 
                ((rt_ts_size/0x40) << VIVS_RS_WINDOW_SIZE_HEIGHT__SHIFT) |
                (16 << VIVS_RS_WINDOW_SIZE_WIDTH__SHIFT));
        etna_set_state(ctx, VIVS_RS_FILL_VALUE(0), 0x55555555);
        etna_set_state(ctx, VIVS_RS_CLEAR_CONTROL, 
                VIVS_RS_CLEAR_CONTROL_MODE_ENABLED1 |
                (0xffff << VIVS_RS_CLEAR_CONTROL_BITS__SHIFT));
        etna_set_state(ctx, VIVS_RS_EXTRA_CONFIG, 0);
        etna_set_state(ctx, VIVS_RS_KICKER, 0xbeebbeeb);
        /** Done */
       
        /* Now set up TS */
        etna_set_state(ctx, VIVS_TS_MEM_CONFIG, 
                VIVS_TS_MEM_CONFIG_DEPTH_FAST_CLEAR |
                VIVS_TS_MEM_CONFIG_COLOR_FAST_CLEAR |
                VIVS_TS_MEM_CONFIG_DEPTH_16BPP | 
                VIVS_TS_MEM_CONFIG_DEPTH_COMPRESSION);
        etna_set_state(ctx, VIVS_TS_DEPTH_CLEAR_VALUE, 0xffffffff);
        etna_set_state(ctx, VIVS_TS_DEPTH_STATUS_BASE, z_ts->address);
        etna_set_state(ctx, VIVS_TS_DEPTH_SURFACE_BASE, z->address);
        etna_set_state(ctx, VIVS_TS_COLOR_CLEAR_VALUE, 0xff303030);
        etna_set_state(ctx, VIVS_TS_COLOR_STATUS_BASE, rt_ts->address);
        etna_set_state(ctx, VIVS_TS_COLOR_SURFACE_BASE, rt->address);
        etna_set_state(ctx, VIVS_GL_FLUSH_CACHE, VIVS_GL_FLUSH_CACHE_COLOR | VIVS_GL_FLUSH_CACHE_DEPTH);

        /* set up texture unit */
        etna_set_state(ctx, VIVS_GL_FLUSH_CACHE, VIVS_GL_FLUSH_CACHE_TEXTURE);
        etna_set_state(ctx, VIVS_TE_SAMPLER_SIZE(0), 
                VIVS_TE_SAMPLER_SIZE_WIDTH(tex_base_width)|
                VIVS_TE_SAMPLER_SIZE_HEIGHT(tex_base_height));
        etna_set_state(ctx, VIVS_TE_SAMPLER_LOG_SIZE(0), 
                VIVS_TE_SAMPLER_LOG_SIZE_WIDTH(tex_base_log_width) |
                VIVS_TE_SAMPLER_LOG_SIZE_HEIGHT(tex_base_log_height));
        for(int ix=0; ix<dds->num_mipmaps; ++ix)
        {
            etna_set_state(ctx, VIVS_TE_SAMPLER_LOD_ADDR(0,ix), tex->address + dds->slices[0][ix].offset);
        }
        etna_set_state(ctx, VIVS_TE_SAMPLER_CONFIG0(0), 
                VIVS_TE_SAMPLER_CONFIG0_TYPE(TEXTURE_TYPE_2D)|
                VIVS_TE_SAMPLER_CONFIG0_UWRAP(TEXTURE_WRAPMODE_CLAMP_TO_EDGE)|
                VIVS_TE_SAMPLER_CONFIG0_VWRAP(TEXTURE_WRAPMODE_CLAMP_TO_EDGE)|
                VIVS_TE_SAMPLER_CONFIG0_MIN(TEXTURE_FILTER_LINEAR)|
                VIVS_TE_SAMPLER_CONFIG0_MIP(TEXTURE_FILTER_LINEAR)|
                VIVS_TE_SAMPLER_CONFIG0_MAG(TEXTURE_FILTER_LINEAR)|
                VIVS_TE_SAMPLER_CONFIG0_FORMAT(tex_format));
        etna_set_state(ctx, VIVS_TE_SAMPLER_LOD_CONFIG(0), 
                VIVS_TE_SAMPLER_LOD_CONFIG_MAX((dds->num_mipmaps - 1)<<5) | VIVS_TE_SAMPLER_LOD_CONFIG_MIN(0));
        //etna_set_state(ctx, VIVS_TE_SAMPLER_UNK2100(0), 0);
        //etna_set_state(ctx, VIVS_TE_SAMPLER_UNK2140(0), 0);

        /* shader setup */
        etna_set_state(ctx, VIVS_VS_START_PC, 0x0);
        etna_set_state(ctx, VIVS_VS_END_PC, vs_size/16);
        etna_set_state_multi(ctx, VIVS_VS_INPUT_COUNT, 3, (uint32_t[]){
                /* VIVS_VS_INPUT_COUNT */ VIVS_VS_INPUT_COUNT_UNK8(1) | VIVS_VS_INPUT_COUNT_COUNT(3),
                /* VIVS_VS_TEMP_REGISTER_CONTROL */ VIVS_VS_TEMP_REGISTER_CONTROL_NUM_TEMPS(6),
                /* VIVS_VS_OUTPUT(0) */ VIVS_VS_OUTPUT_O0(4) | 
                                        VIVS_VS_OUTPUT_O1(0) | 
                                        VIVS_VS_OUTPUT_O2(1)});
        etna_set_state_multi(ctx, VIVS_VS_INST_MEM(0), vs_size/4, vs);
        etna_set_state(ctx, VIVS_VS_OUTPUT_COUNT, 3);
        etna_set_state(ctx, VIVS_VS_LOAD_BALANCING, 0xf3f0542); /* depends on number of inputs/outputs/varyings? XXX how exactly */
        etna_set_state_multi(ctx, VIVS_VS_UNIFORMS(0), 16, (uint32_t*)&modelviewprojection.m[0][0]);
        etna_set_state_multi(ctx, VIVS_VS_UNIFORMS(16), 3, (uint32_t*)&normal.m[0][0]); /* u4.xyz */
        etna_set_state_multi(ctx, VIVS_VS_UNIFORMS(20), 3, (uint32_t*)&normal.m[1][0]); /* u5.xyz */
        etna_set_state_multi(ctx, VIVS_VS_UNIFORMS(24), 3, (uint32_t*)&normal.m[2][0]); /* u6.xyz */
        etna_set_state_multi(ctx, VIVS_VS_UNIFORMS(28), 16, (uint32_t*)&modelview.m[0][0]);
        etna_set_state_f32(ctx, VIVS_VS_UNIFORMS(19), 2.0); /* u4.w */
        etna_set_state_f32(ctx, VIVS_VS_UNIFORMS(23), 20.0); /* u5.w */
        etna_set_state_f32(ctx, VIVS_VS_UNIFORMS(27), 0.0); /* u6.w */
        etna_set_state_f32(ctx, VIVS_VS_UNIFORMS(45), 0.5); /* u11.y */
        etna_set_state_f32(ctx, VIVS_VS_UNIFORMS(44), 1.0); /* u11.x */
        etna_set_state(ctx, VIVS_VS_INPUT(0), VIVS_VS_INPUT_I0(0) | 
                                        VIVS_VS_INPUT_I1(1) | 
                                        VIVS_VS_INPUT_I2(2));

        etna_set_state(ctx, VIVS_PS_START_PC, 0x0);
        etna_set_state_multi(ctx, VIVS_PS_END_PC, 2, (uint32_t[]){
                /* VIVS_PS_END_PC */ ps_size/16,
                /* VIVS_PS_OUTPUT_REG */ 0x1});
        etna_set_state_multi(ctx, VIVS_PS_INST_MEM(0), ps_size/4, ps);
        etna_set_state(ctx, VIVS_PS_INPUT_COUNT, VIVS_PS_INPUT_COUNT_UNK8(31) | VIVS_PS_INPUT_COUNT_COUNT(3));
        etna_set_state(ctx, VIVS_PS_TEMP_REGISTER_CONTROL, VIVS_PS_TEMP_REGISTER_CONTROL_NUM_TEMPS(3));
        etna_set_state(ctx, VIVS_PS_CONTROL, VIVS_PS_CONTROL_UNK1);
        etna_set_state_f32(ctx, VIVS_PS_UNIFORMS(0), 1.0); /* u0.x */

        etna_set_state(ctx, VIVS_FE_VERTEX_STREAM_BASE_ADDR, vtx->address); /* ADDR_E */
        etna_set_state(ctx, VIVS_FE_VERTEX_STREAM_CONTROL, 
                VIVS_FE_VERTEX_STREAM_CONTROL_VERTEX_STRIDE((3 + 3 + 2)*4));
        etna_set_state(ctx, VIVS_FE_VERTEX_ELEMENT_CONFIG(0), 
                VIVS_FE_VERTEX_ELEMENT_CONFIG_TYPE_FLOAT |
                (ENDIAN_MODE_NO_SWAP << VIVS_FE_VERTEX_ELEMENT_CONFIG_ENDIAN__SHIFT) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_STREAM(0) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_NUM(3) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_NORMALIZE_OFF |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_START(0x0) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_END(0xc));
        etna_set_state(ctx, VIVS_FE_VERTEX_ELEMENT_CONFIG(1), 
                VIVS_FE_VERTEX_ELEMENT_CONFIG_TYPE_FLOAT |
                (ENDIAN_MODE_NO_SWAP << VIVS_FE_VERTEX_ELEMENT_CONFIG_ENDIAN__SHIFT) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_STREAM(0) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_NUM(3) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_NORMALIZE_OFF |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_START(0xc) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_END(0x18));
        etna_set_state(ctx, VIVS_FE_VERTEX_ELEMENT_CONFIG(2), 
                VIVS_FE_VERTEX_ELEMENT_CONFIG_TYPE_FLOAT |
                (ENDIAN_MODE_NO_SWAP << VIVS_FE_VERTEX_ELEMENT_CONFIG_ENDIAN__SHIFT) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_NONCONSECUTIVE |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_STREAM(0) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_NUM(2) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_NORMALIZE_OFF |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_START(0x18) |
                VIVS_FE_VERTEX_ELEMENT_CONFIG_END(0x20));

        for(int prim=0; prim<6; ++prim)
        {
            etna_draw_primitives(ctx, PRIMITIVE_TYPE_TRIANGLE_STRIP, prim*4, 2);
        }
#if 0
        /* resolve to self */
        etna_set_state(ctx, VIVS_GL_FLUSH_CACHE, VIVS_GL_FLUSH_CACHE_COLOR | VIVS_GL_FLUSH_CACHE_DEPTH);
        etna_set_state(ctx, VIVS_RS_CONFIG,
                VIVS_RS_CONFIG_SOURCE_FORMAT(RS_FORMAT_X8R8G8B8) |
                VIVS_RS_CONFIG_SOURCE_TILED |
                VIVS_RS_CONFIG_DEST_FORMAT(RS_FORMAT_X8R8G8B8) |
                VIVS_RS_CONFIG_DEST_TILED);
        etna_set_state(ctx, VIVS_RS_SOURCE_STRIDE, (padded_width * 4 * 4) | VIVS_RS_SOURCE_STRIDE_TILING);
        etna_set_state(ctx, VIVS_RS_DEST_STRIDE, (padded_width * 4 * 4) | VIVS_RS_DEST_STRIDE_TILING);
        etna_set_state(ctx, VIVS_RS_DITHER(0), 0xffffffff);
        etna_set_state(ctx, VIVS_RS_DITHER(1), 0xffffffff);
        etna_set_state(ctx, VIVS_RS_CLEAR_CONTROL, VIVS_RS_CLEAR_CONTROL_MODE_DISABLED);
        etna_set_state(ctx, VIVS_RS_EXTRA_CONFIG, 0); /* no AA, no endian switch */
        etna_set_state(ctx, VIVS_RS_SOURCE_ADDR, rt->address); /* ADDR_A */
        etna_set_state(ctx, VIVS_RS_DEST_ADDR, rt->address); /* ADDR_A */
        etna_set_state(ctx, VIVS_RS_WINDOW_SIZE, 
                VIVS_RS_WINDOW_SIZE_HEIGHT(padded_height) |
                VIVS_RS_WINDOW_SIZE_WIDTH(padded_width));
        etna_set_state(ctx, VIVS_RS_KICKER, 0xbeebbeeb);

        etna_set_state(ctx, VIVS_RS_FLUSH_CACHE, VIVS_RS_FLUSH_CACHE_FLUSH);

        etna_set_state(ctx, VIVS_TS_COLOR_STATUS_BASE, rt_ts->address); /* ADDR_B */
        etna_set_state(ctx, VIVS_TS_COLOR_SURFACE_BASE, rt->address); /* ADDR_A */
        etna_set_state(ctx, VIVS_GL_FLUSH_CACHE, VIVS_GL_FLUSH_CACHE_COLOR);
        etna_set_state(ctx, VIVS_TS_MEM_CONFIG, 
                VIVS_TS_MEM_CONFIG_DEPTH_FAST_CLEAR |
                VIVS_TS_MEM_CONFIG_DEPTH_16BPP | 
                VIVS_TS_MEM_CONFIG_DEPTH_COMPRESSION);
        etna_set_state(ctx, VIVS_GL_FLUSH_CACHE, VIVS_GL_FLUSH_CACHE_COLOR);
#endif
        etna_stall(ctx, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);

        /* copy to screen */
        etna_bswap_wait_available(buffers);
        etna_set_state(ctx, VIVS_GL_FLUSH_CACHE, VIVS_GL_FLUSH_CACHE_COLOR | VIVS_GL_FLUSH_CACHE_DEPTH);
        etna_set_state(ctx, VIVS_RS_CONFIG,
                VIVS_RS_CONFIG_SOURCE_FORMAT(RS_FORMAT_X8R8G8B8) |
                VIVS_RS_CONFIG_SOURCE_TILED |
                VIVS_RS_CONFIG_DEST_FORMAT(RS_FORMAT_X8R8G8B8) |
                VIVS_RS_CONFIG_SWAP_RB);
        etna_set_state(ctx, VIVS_RS_SOURCE_STRIDE, (padded_width * 4 * 4) | VIVS_RS_SOURCE_STRIDE_TILING);
        etna_set_state(ctx, VIVS_RS_DEST_STRIDE, fb.fb_fix.line_length);
        etna_set_state(ctx, VIVS_RS_DITHER(0), 0xffffffff);
        etna_set_state(ctx, VIVS_RS_DITHER(1), 0xffffffff);
        etna_set_state(ctx, VIVS_RS_CLEAR_CONTROL, VIVS_RS_CLEAR_CONTROL_MODE_DISABLED);
        etna_set_state(ctx, VIVS_RS_EXTRA_CONFIG, 
                0); /* no AA, no endian switch */
        etna_set_state(ctx, VIVS_RS_SOURCE_ADDR, rt->address); /* ADDR_A */
        etna_set_state(ctx, VIVS_RS_DEST_ADDR, fb.physical[buffers->backbuffer]); /* ADDR_J */
        etna_set_state(ctx, VIVS_RS_WINDOW_SIZE, 
                VIVS_RS_WINDOW_SIZE_HEIGHT(height) |
                VIVS_RS_WINDOW_SIZE_WIDTH(width));
        etna_set_state(ctx, VIVS_RS_KICKER, 0xbeebbeeb);

        etna_flush(ctx);
        etna_bswap_queue_swap(buffers);
    }
#ifdef DUMP
    bmp_dump32(fb.logical[1-backbuffer], width, height, false, "/mnt/sdcard/fb.bmp");
    printf("Dump complete\n");
#endif
    etna_bswap_free(buffers);
    etna_free(ctx);
    viv_close();
    return 0;
}