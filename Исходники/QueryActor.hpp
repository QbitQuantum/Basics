    void QueryHandler(const QueryMessage &message, const Theron::Address from)
        {
            search::QueryInfo qi=*(message.query);
            std::string resKey(message.resKey);
            delete message.query;
            std::string segString;
            char *output=new char[qi.query.length()*9];
            char *input=new char[qi.query.length()*3];
            memset(output,0,qi.query.length()*9);
            memset(input,0,qi.query.length()*3);
            try 
            {
                UErrorCode  error = U_ZERO_ERROR;
                ucnv_convert("GBK","UTF-8",input,  qi.query.length()*3, qi.query.c_str(), qi.query.length(), &error );
                
                
                bool ret = result->ParagraphProcessing(input, output);
                if (ret)
                {
                    int oLen=strlen(output);
                    char *utf8out=new char[oLen*3];
                    memset(utf8out,0,oLen*3);
                    ucnv_convert("UTF-8","GBK",utf8out,  oLen*3, output, oLen, &error );
                    
                    segString=std::string(utf8out);
                    delete [] utf8out;
                }
            }
            catch (...) {
            }
            delete [] output;
            delete [] input;
            std::list<std::string> segList;
            if(segString.length()>0)
            {
                std::vector<std::string> resv;
                boost::algorithm::split( resv, segString, boost::algorithm::is_any_of(" ") );
                for(std::vector<std::string>::iterator it=resv.begin();it!=resv.end();++it)
                {
                    std::vector<std::string> tmpv;
                    boost::algorithm::split( tmpv, *it, boost::algorithm::is_any_of("/") );
                    if(tmpv.size()>1&&tmpv[1]!="w")
                        segList.push_back(std::string("K")+tmpv[0]);
                }
            }
            search::DocList *dList=new search::DocList();
            if(segList.size()>0)
            {
                Xapian::Query query(Xapian::Query::OP_AND,segList.begin(), segList.end());
                
                while(1)
                {
                    try
                    {
                        db.reopen();
                        Xapian::Enquire  enquire(db);
                        enquire.set_query(query);
                        Xapian::MSet matches = enquire.get_mset(0, 100);
                        for (Xapian::MSetIterator i = matches.begin(); i != matches.end(); ++i) {
                            Xapian::Document doc = i.get_document();
                            search::IndexInfo info;
                            info.uid=doc.get_value(1);
                            info.attMap.insert(std::make_pair(std::string("title"),doc.get_value(2)));
                            info.content=doc.get_data();
                            dList->docList.push_back(info);
                        }
                        std::cout<<"doc size:"<<dList->docList.size()<<std::endl;
                        break;
                    }catch(Xapian::DatabaseModifiedError exception)
                    {
                        std::cout<<"try agian"<<std::endl;
                    }catch(...)
                    {
                        break;
                    }
                    
                }
                

            }
            Send(QueryResponceMessage(dList,resKey.c_str()), from);
            
        }