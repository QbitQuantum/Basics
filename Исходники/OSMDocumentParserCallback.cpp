/**
    Parser callback for OSMDocument files
*/
void OSMDocumentParserCallback::StartElement(const char *name, const char** atts) {
    // START RELATIONS CODE
    if (strcmp(name, "member") == 0) {
        // std::cout << "In member..." << std::endl;

        if (m_pActRelation && atts != NULL) {
            const char** attribut = (const char**)atts;
            while (*attribut != NULL) {
                const char* name = *attribut++;
                const char* value = *attribut++;
                if (strcmp(name, "ref") == 0) {
                    long long wayRefId = atoll(value);
                    m_pActRelation->AddWayRef(wayRefId);
                }
            }
        }
    }
    // END RELATIONS CODE


    if (strcmp(name, "nd") == 0) {
        if (m_pActWay && atts != NULL) {
            const char* name = *atts++;
            const char* value = *atts++;
            if (strcmp(name, "ref") == 0) {
                long long nodeRefId = atoll(value);
                m_pActWay->AddNodeRef(m_rDocument.FindNode(nodeRefId));
                Node * node = m_rDocument.FindNode(nodeRefId);
                if (node != 0) {
                    node->numsOfUse+=1;
                } else {
                    std::cout << "Reference nd=" << nodeRefId
                              << " has no corresponding Node Entry (Maybe Node entry after Reference?)" << std::endl;
                }
            }
        }
    } else if (strcmp(name, "node") == 0) {
        if (atts != NULL) {
            long long id =-1;
            double lat =-1;
            double lon =-1;
            const char** attribut = (const char**)atts;
            while (*attribut != NULL) {
                const char* name = *attribut++;
                const char* value = *attribut++;
                if (strcmp(name, "id") == 0) {
                    id = atoll(value);
                } else if (strcmp(name, "lat") == 0) {
                    lat = atof(value);
                } else if (strcmp(name, "lon") == 0) {
                    lon = atof(value);
                }
            }
            if (id > 0) m_rDocument.AddNode(new Node(id, lat, lon));
        }
    } else if (strcmp(name, "relation") == 0) {   // THIS IS THE RELATION CODE...
        if (atts != NULL) {
            long long id =-1;
            const char** attribut = (const char**)atts;
            while (*attribut != NULL) {
                const char* name = *attribut++;
                const char* value = *attribut++;
                if (strcmp(name, "id") == 0) {
                    id = atoll(value);
                }
            }
            if (id > 0) m_pActRelation = new Relation(id);
            // std::cout<<"Starting relation: "<<id<<std::endl;
        }
    } else if (strcmp(name, "tag") == 0) {  // END OF THE RELATIONS CODE
        // <tag k="name" v="Pf�nderweg"/>
        if (atts != NULL) {
            std::string k;
            std::string v;
            const char** attribut = (const char**)atts;
            while (*attribut != NULL) {
                const char* name = *attribut++;
                const char* value = *attribut++;
                if (strcmp(name, "k") == 0) {
                    k = value;
                } else if (strcmp(name, "v") == 0) {
                    v = value;
                }
            }
            if (!k.empty()) {
                //  CHECKING OUT SOME DATA...
                // std::cout<<"k: "<<k<<", v: "<<v<<std::endl;
                // std::cout<<"m_pActWay: "<<m_rDocument.m_rConfig.m_Types.count(k)<<std::endl;
                // std::cout<<"thecount: "<<m_rDocument.m_rConfig.m_Types.count(k)<<std::endl;
                if (m_pActWay && k.compare("name") == 0) {
                    m_pActWay->name = v;
                } else if (m_pActWay && k.compare("oneway") == 0) {  // checks ONEWAY tag
                    if ((v.compare("yes") == 0) || (v.compare("true") == 0) || (v.compare("1") == 0)) {
                        m_pActWay->oneWayType = YES;
                    } else {}
                    // check false conditions: 0, no, false
                    if ((v.compare("no") == 0) || (v.compare("false") == 0) || (v.compare("0") == 0)) {
                        m_pActWay->oneWayType = NO;
                    } else {}
                    // check revers conditions: -1
                    if ((v.compare("-1") == 0)) {
                        m_pActWay->oneWayType = REVERSED;
                    }
                    // in case roundabout, if there is not additional oneway tag, set default oneway to YES
                } else if (m_pActWay && k.compare("junction") == 0 && v.compare("roundabout") == 0) {
                    if (m_pActWay->oneWayType == UNKNOWN) m_pActWay->oneWayType= YES;
                }
                // handle 3 cases if the key contains maxspeed
                else if (m_pActWay && k.find("maxspeed") != std::string::npos) {
                    // If the value contains mph, strip unit, convert to kph.
                    if (v.find("mph") != std::string::npos) {
                        // Assume format is /[0-9]{1,3} ?mph/
                        v = my_utils::read_number_substring(v);
                        std::ostringstream ostr;
                        ostr << floor(atoi(v.c_str()) * 1.60934);
                        v = ostr.str();
                    }
                    // handle maxspeed:forward tag
                    if (k.compare("maxspeed:forward") == 0) {
                        int mspeed_fwd = 50;

                        if (my_utils::is_number(v)) {
                            mspeed_fwd = atoi(v.c_str());
                        } else {
                            // TODO: handle non-numeric values, ex.: RO:urban
                            std::cout << "unknown maxspeed1 value: " << v << std::endl;
                        }
                        m_pActWay->maxspeed_forward = mspeed_fwd;
                    }
                    // handler maxspeed:backward
                    else if (k.compare("maxspeed:backward") == 0) {
                        int mspeed_backwd = 50;

                        if (my_utils::is_number(v)) {
                            mspeed_backwd = atoi(v.c_str());
                        } else {
                            // TODO: handle non-numeric values, ex.: RO:urban
                            std::cout << "unknown maxspeed2 value: " << v << std::endl;
                        }
                        m_pActWay->maxspeed_backward = mspeed_backwd;
                    } else if (k.compare("maxspeed") == 0) {
                        int mspeed_fwd = 50;
                        int mspeed_backwd = 50;

                        if (my_utils::is_number(v)) {
                            mspeed_fwd = atoi(v.c_str());
                            mspeed_backwd = atoi(v.c_str());
                        } else {
                            // TODO: handle non-numeric values, ex.: RO:urban
                            std::cout << "unknown maxspeed3 value: " << v << std::endl;
                        }
                        m_pActWay->maxspeed_backward = mspeed_backwd;
                        m_pActWay->maxspeed_forward = mspeed_fwd;
                    }
                }
                // else if (m_pActWay && k.compare("highway") == 0)
                else if (m_pActWay && m_rDocument.m_rConfig.m_Types.count(k)) {
                    m_pActWay->type = k;
                    m_pActWay->clss = v;

                    if (m_rDocument.m_rConfig.m_Types.count(m_pActWay->type) && m_rDocument.m_rConfig.m_Types[m_pActWay->type]->m_Classes.count(m_pActWay->clss)) {
                        m_pActWay->AddTag(k, v);

                        // std::cout<<"Added tag: "<<k<<" "<<v<<std::endl;

                        // set default maxspeed values from classes, if not set previously (default: -1)
                        if (m_pActWay->maxspeed_forward <= 0) {
                            int newValue = m_rDocument.m_rConfig.m_Types[m_pActWay->type]->m_Classes[m_pActWay->clss]->default_maxspeed;
                            m_pActWay->maxspeed_forward = newValue;
                        }
                        if (m_pActWay->maxspeed_backward <= 0) {
                            int newValue = m_rDocument.m_rConfig.m_Types[m_pActWay->type]->m_Classes[m_pActWay->clss]->default_maxspeed;
                            m_pActWay->maxspeed_backward = newValue;
                        }
                    }
                }
                // START TAG FOR RELATION
                else if (m_pActRelation && m_rDocument.m_rConfig.m_Types.count(k))  {
                    if (m_rDocument.m_rConfig.m_Types.count(k) && m_rDocument.m_rConfig.m_Types[k]->m_Classes.count(v)) {
                        m_pActRelation->AddTag(k, v);
                        // std::cout<<"Added Relation tag: "<<k<<" "<<v<<std::endl;
                    }
                    // std::cout<<"Relations tag: "<<k<<" "<<v<<std::endl;
                }
                if (m_pActRelation && k.compare("name") == 0) {
                    m_pActRelation->name = v;
                }
                // END TAG FOR RELATION
            }
        }
    } else if (strcmp(name, "way") == 0) {
        if (atts != NULL) {
            long long id =-1;
            bool visibility = false;
            const char** attribut = (const char**)atts;
            while (*attribut != NULL) {
                const char* name = *attribut++;
                const char* value = *attribut++;
                if (strcmp(name, "id") == 0) {
                    id = atoll(value);
                } else if (strcmp(name, "visible") == 0) {
                    visibility = strcmp(value, "true") == 0;
                }
            }
            if (id > 0) {
                m_pActWay = new Way(id, visibility, id , -1, -1);
            }
        }
    } else if (strcmp(name, "osm") == 0) {
    }
}