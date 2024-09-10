ChattyPostDataRef getChattyPostDataRefFromJSONPost(const JsonTree& post)
{
   ChattyPostDataRef post_data_ref = ChattyPostData::create();

   post_data_ref->m_id = fromString<uint32_t>(post["id"].getValue());
   post_data_ref->m_thread_id = fromString<uint32_t>(post["threadId"].getValue());
   post_data_ref->m_parent_id = fromString<uint32_t>(post["parentId"].getValue());
   post_data_ref->m_author = post["author"].getValue();
   post_data_ref->m_body = post["body"].getValue();

   replaceEncodingsInString(post_data_ref->m_body);

   std::string strvalue = post["category"].getValue();
   if(strvalue.length() > 0)
   {
           if(strvalue == "ontopic")        post_data_ref->m_category = category_type::NORMAL;
      else if(strvalue == "nws")            post_data_ref->m_category = category_type::NWS;
      else if(strvalue == "stupid")         post_data_ref->m_category = category_type::STUPID;
      else if(strvalue == "political")      post_data_ref->m_category = category_type::POLITICAL;
      else if(strvalue == "tangent")        post_data_ref->m_category = category_type::OFFTOPIC;
      else if(strvalue == "informative")    post_data_ref->m_category = category_type::INFORMATIVE;
      else if(strvalue == "nuked")          post_data_ref->m_category = category_type::NUKED;
   }

   strvalue = post["date"].getValue();
   if(strvalue.length() > 0)
   {
      std::tm post_time;
      memset(&post_time, 0, sizeof(std::tm));
      
#if defined(CINDER_MSW)
      sscanf_s(strvalue.c_str(), "%d-%d-%dT%d:%d",
               &post_time.tm_year,
               &post_time.tm_mon,
               &post_time.tm_mday,
               &post_time.tm_hour,
               &post_time.tm_min);
#else
      sscanf(strvalue.c_str(), "%d-%d-%dT%d:%d",
               &post_time.tm_year,
               &post_time.tm_mon,
               &post_time.tm_mday,
               &post_time.tm_hour,
               &post_time.tm_min);
#endif

      post_time.tm_year -= 1900;
      post_time.tm_mon -= 1;

#if defined(CINDER_MSW)
      post_data_ref->m_date_time = _mkgmtime(&post_time);
#else
      post_data_ref->m_date_time = timegm(&post_time); // and I have no idea if this is right
#endif
      // if mac doesn't have _mkgmtime, need to find a way to convert UTC to local
      //post_data_ref->m_date_time = std::mktime(&post_time);
   }

   if(post.hasChild("lols"))
   {
      const JsonTree& lols = post.getChild("lols");
      for(size_t lol_i = 0; lol_i < lols.getNumChildren(); lol_i++)
      {
         const JsonTree& lol = lols.getChild(lol_i);
         strvalue = lol["tag"].getValue();
         if(strvalue.length() > 0)
         {
            lol_type which_lol = LOL;
                 if(strvalue == "lol") which_lol = lol_type::LOL;
            else if(strvalue == "inf") which_lol = lol_type::INF;
            else if(strvalue == "unf") which_lol = lol_type::UNF;
            else if(strvalue == "tag") which_lol = lol_type::TAG;
            else if(strvalue == "wtf") which_lol = lol_type::WTF;
            else if(strvalue == "ugh") which_lol = lol_type::UGH;

            post_data_ref->m_lol_count[which_lol] = fromString<unsigned int>(lol["count"].getValue());
         }
      }
   }

   return post_data_ref;
}