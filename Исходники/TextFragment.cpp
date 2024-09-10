bool TextFragment::format(vec2& location, 
                          float rect_width, 
                          bool limit_line_count, 
                          int& line_count,
                          bool single_line)
{
   bool abort = false;
   updateGlyphArrays(limit_line_count);
   // we are going to fill out the m_glyph_rendering_array
   // he is what is used to render in the draw() method.
   m_glyph_rendering_array.clear();
   m_rect_array.clear();
      
   size_t glyph_offset = 0;
   float line_begin = location.x;
      
   for(std::vector<WordInfo>::const_iterator word_info = m_glyph_words_array.begin();
       word_info != m_glyph_words_array.end() && !abort;
       word_info++)
   {
      if(single_line)
      {
         for(size_t i = 0;
             !abort && i < word_info->m_glyph_count;
             i++)
         {
            if(location.x + m_glyph_widths_array[glyph_offset + i].second > rect_width)
            {
               abort = true;
            }
            else
            {
               addGlyphItemToRenderingArray(glyph_offset + i, location);
            }
         }
      }
      else
      {
         if(location.x + word_info->m_width > rect_width)
         {
            m_rect_array.push_back(Rectf(line_begin, location.y - g_skin.getBaselineDrop(),
               location.x, location.y + g_skin.getBaselineRise()));
            if(limit_line_count)
            {
               line_count--;
               if(line_count == 0)
               {
                  abort = true;
               }
            }

            if(!abort)
            {
               moveLocationToNewline(location);
               line_begin = location.x;
            }
         }

         bool break_line_on_char = false;
         if(location.x == 0 && word_info->m_width > rect_width)
         {
            break_line_on_char = true;
         }

         for(size_t i = 0;
             i < word_info->m_glyph_count && !abort;
             i++)
         {
            if(break_line_on_char &&
               location.x + m_glyph_widths_array[glyph_offset + i].second > rect_width)
            {
               m_rect_array.push_back(Rectf(line_begin, location.y - g_skin.getBaselineDrop(),
                  location.x, location.y + g_skin.getBaselineRise()));

               if(limit_line_count)
               {
                  line_count--;
                  if(line_count == 0)
                  {
                     abort = true;
                  }
               }

               if(!abort)
               {
                  moveLocationToNewline(location);
                  line_begin = location.x;
               }
            }

            addGlyphItemToRenderingArray(glyph_offset + i, location);
         }

         if(word_info->m_newline)
         {
            m_rect_array.push_back(Rectf(line_begin, location.y - g_skin.getBaselineDrop(),
               location.x, location.y + g_skin.getBaselineRise()));

            if(limit_line_count)
            {
               line_count--;
               if(line_count == 0)
               {
                  abort = true;
               }
            }

            if(!abort)
            {
               moveLocationToNewline(location);
               line_begin = location.x;
            }
         }
      }

      glyph_offset += word_info->m_glyph_count;
   }

   m_rect_array.push_back(Rectf(line_begin, location.y - g_skin.getBaselineDrop(),
                                location.x, location.y + g_skin.getBaselineRise()));
   m_cumulative_rect = m_rect_array.front();
   for(size_t i = 1; i < m_rect_array.size(); i++)
   {
      m_cumulative_rect.include(m_rect_array[i]);
   }

   return abort;
}