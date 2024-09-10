    void FontBufferCache::Add(const std::string &text, const Point3 &position, const GameColor &color, texture_font_t *font)
    {
        HashedString hash(text.c_str());
        vertex_buffer_t *buffer = 0;
        if(Contains(text)) {
            buffer = m_vertexBufferMap.find(hash.getHashValue())->second;
            vertex_buffer_clear(buffer);
        } else {
            buffer = vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f");
            m_vertexBufferMap[hash.getHashValue()] = buffer;
        }

        F32 r = color.GetX(), g = color.GetY(), b = color.GetZ(), a = color.GetW();
        F32 x = 0.0f;

        U32 size = (U32)text.size();
        for(U32 i = 0; i < size; ++i) {
            texture_glyph_t *glyph = texture_font_get_glyph(font, text[i]);
            if(glyph != NULL) {
                I32 kerning = 0;
                if(i > 0) {
                    kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
                }
                x += (float)kerning;

                F32 x0 = (F32)(position.GetX() + x + glyph->offset_x);
                F32 y0 = (F32)(position.GetY() + glyph->offset_y);
                F32 x1 = (F32)(x0 + glyph->width);
                F32 y1 = (F32)(y0 - glyph->height);
                F32 s0 = glyph->s0;
                F32 t0 = glyph->t0;
                F32 s1 = glyph->s1;
                F32 t1 = glyph->t1;
                GLuint indices[6] = {0, 1, 2, 0, 2, 3};
                vertex_t vertices[4] = { { x0, y0, 0.0f,  s0, t0,  r, g, b, a },
                    { x0, y1, 0.0f,  s0, t1,  r, g, b, a },
                    { x1, y1, 0.0f,  s1, t1,  r, g, b, a },
                    { x1, y0, 0.0f,  s1, t0,  r, g, b, a }
                };
                vertex_buffer_push_back(buffer, vertices, 4, indices, 6);
                x += glyph->advance_x;
            }
        }
    }