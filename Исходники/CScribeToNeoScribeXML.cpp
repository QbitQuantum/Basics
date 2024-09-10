Staff* CScribeToNeoScribeXML::Scribe2MEIXMLStaff(const CScribeReaderVisitable& scribe_data, const scribe_part& partit, StaffGrp* staffgrp, const int i)
{
    
    std::string staffnum("s");
    staffnum += std::to_string(i); //autogenerate staff ids
    
    //finish score definitions
    //add staff definition for current part
    //NB. look to alternatively embedding these in staffs
    StaffDef* staffdef = new StaffDef;
    
    //define staff from data
    staffgrp->addChild(staffdef);
    staffdef->addAttribute("id", staffnum);
    staffdef->addAttribute("lines", std::to_string(partit.initial_staff_data.staff_lines));
    staffdef->addAttribute("label", CScribeCodes::voice_labels[partit.voice_type].c_str());
    
    //define clef from data
    Clef* clef = new Clef;
    staffdef->addChild(clef);
    
    scribe_clef loc_clef;
    loc_clef.clef_line = partit.initial_staff_data.clef_line;
    loc_clef.clef = partit.initial_staff_data.clef;
    //convert scribe-based clef position to mei
    //int mei_clef_line = ((loc_clef.clef_line + 1)/2) - 1; = incorrect
    int mei_clef_line = 1 + (loc_clef.clef_line-3)/2;
    //4-line staves are numbered 3, 5, 7, 9 in scribe
    //if (partit->staff_lines<=4) mei_clef_line -= (5 - partit->staff_lines);
    
    clef->addAttribute("line", std::to_string(mei_clef_line)); //these need to be set for each staff/part
    clef->addAttribute("shape", std::string(&(partit.initial_staff_data.clef),1).c_str()); //the first event in stored memory should be the initial clef
    
    Staff* staff = new Staff;
    
    staff->addAttribute("id", staffnum);
    staff->addAttribute("source", partit.abbrev_ms);
    //folio on which part appears
    
    Pb* pb = new Pb; //new ELEMENT?
    staff->addChild(pb);
    pb->addAttribute("n", partit.folios);
    //first staff on which part appears
    Sb* sb = new Sb;
    sb->addAttribute("n", "0"); //set to "0" since this isn't encoded in scribe; data will need to be enhanced later
    staff->addChild(sb);
    
    coloration_type current_color = coloration_type::full_black; // this needs to be better handled with a default coloration in a part
    
    for (std::vector<scribe_row>::const_iterator rowit = partit.rows.begin(); rowit!=partit.rows.end(); rowit++)
    {
        if (rowit->is_comment) {
            //check it this is the correct way to handle a comment
            
            MeiCommentNode* comment = new MeiCommentNode;
            comment->setValue(rowit->comment);
            staff->addChild(comment);
            //NB. syl can have a type (eg. initial) attribute and also encode color as <rend> child element
        } else {
            
            //syllable container (holds syllables, notes, neumes, and ligatures)
            Syllable* syllable = new Syllable; //neumes.h
            staff->addChild(syllable);
            
            //add actual syllable if present
            if (!rowit->syllable.empty()) {
                Syl* syl = new Syl;
                syl->setValue(rowit->syllable);
                syllable->addChild(syl);
            }
            
            //extract events - notes, rests ligatures, uneumes and/or ligatures
            for (std::vector<scribe_event>::const_iterator eventit = rowit->events.begin(); eventit!=rowit->events.end(); eventit++ )
            {
                current_color = eventit->local_coloration;
                
                //use temp TiXML pointer which is either syllable, uneume/ineume or ligature - add notes to this, but make sure that uneume/inueme/ligature pointer is preinserted into syllable
                //handle events for each row
                code_t event_type = scribe_data.GetCodes()->get_code_type(eventit->code);//codes->get_code_type(eventit->code);
                //foster parent will change roles according to child elements that need to be added
                MeiElement* foster = syllable;
                
                switch (event_type)
                {
                    case code_t::ineume:
                    {
#ifdef IGNOREGAPS
                        Ineume* ineume = new Ineume;
                        //ineume->addAttribute("name", scribe_data.GetCodes()->code_to_name(eventit->code));
                        foster->addChild(ineume);
                        foster = ineume;
                        
#else                   //this needs work, hence excluded
                        if (!eventit->preceding_gap || foster->getChildren().empty())
                        {
                            Ineume* ineume = new Ineume;
                            //ineume->addAttribute("name", scribe_data.GetCodes()->code_to_name(eventit->code));
                            foster->addChild(ineume);
                            foster = ineume;
                        }
                        else
                        {
                            MeiElement* lastNeume = foster->getChildren().back();
                            if (lastNeume->getName() == "ineume")
                            {
                                Ineume* newNeume = new Ineume(*dynamic_cast<Ineume*>(lastNeume));
                                /*for (std::vector<MeiElement*>::const_iterator child = lastNeume->getChildren().begin(); child!=lastNeume->getChildren().end(); child++ ) {
                                    MeiElement* clone = new MeiElement(**child);
                                    newNeume->addChild(clone);
                                }*/
                                foster->removeChild(lastNeume);
                                foster->addChild(newNeume);
                                //delete lastNeume;
                                foster = newNeume;
                            }
                            else
                                foster = lastNeume;
                        }
#endif
                        goto do_note;
                        break;
                    }
                    case code_t::uneume:
                    {
                        Uneume* uneume = new Uneume;
                        uneume->addAttribute("name", scribe_data.GetCodes()->code_to_name(eventit->code));
                        foster->addChild(uneume);
                        foster = uneume;
                        goto do_note;
                        break;
                    }
                    case code_t::ligature:
                    {
                        Ligature* ligature = new Ligature; //mensural.h
                        ligature->addAttribute("name", scribe_data.GetCodes()->code_to_name(eventit->code));
                        foster->addChild(ligature);
                        foster = ligature;
                        if (current_color!=coloration_type::full_black)
                        {
                            switch (current_color) {
                                case full_red:
                                    ligature->addAttribute("color", "red");
                                    break;
                                case void_red:
                                    ligature->addAttribute("color", "red");
                                    ligature->addAttribute("void", "true"); //this seems a sensible solution for this problem and a suitable additional attribute to the MEI description
                                    break;
                                case void_black:
                                    ligature->addAttribute("void", "true"); //**
                                    break;
                                case full_blue:
                                    ligature->addAttribute("color", "blue");
                                    break;
                                default:
                                    break;
                            }
                        }
                        //goto do_note;
                        //break;
                    }
                    case code_t::note:
                    do_note:
                    {
                        for (auto i = eventit->pitch_num.begin(); i!=eventit->pitch_num.end(); i++)
                        {
                            int note_count = 1;
                            MeiElement* temp_foster = foster;
                            
                            //handle note attributes according to type
                            if ( foster->getName()=="ineume" )
                            {
                                Uneume* temp_uneume = new Uneume;  //handle ineumes
                                //find uneume names
                                temp_uneume->addAttribute("name", CScribeReaderVisitable::get_ineume_part(eventit->code, i - eventit->pitch_num.begin(), note_count));
                                foster->addChild(temp_uneume);
                                temp_foster = temp_uneume; //allow notes to be children of uneume
                            } else if ((eventit->code=="B" || eventit->code=="V" || eventit->code=="L") && eventit->pitch_num.size()>1 && scribe_data.GetType()==chant && i!=eventit->pitch_num.begin()) //codes like virga and punctum may be followed by several pitch numbers, indicating a sequence of simple neumes
                            {
                                Uneume* temp_uneume = new Uneume;
                                temp_uneume->addAttribute("name", scribe_data.GetCodes()->code_to_name(eventit->code));
                                foster->getParent()->addChild(temp_uneume); //link to syllable element, not uneume!
                                temp_foster = temp_uneume;
                            }
                            //also handle ligatures
                            auto j = 0;
                            //insert note or notes for unneumes in ineumes
                            for (; j < note_count ; j++)
                            {
                                //convert note location to pitch name
                                // need to handle dots as element rather than attribute?
                                char pitch_name = loc_clef.get_pitch_name(*i);
                                int octave = loc_clef.get_octave(*i);
                                
                                Note* note = new Note;
                                if (foster->getName()=="syllable")
                                {
                                    note->addAttribute("dur", scribe_data.GetCodes()->code_to_name(eventit->code));
                                }
                                else if (foster->getName()=="ligature")
                                {
                                    note->addAttribute("dur", scribe_data.get_ligature_part(eventit->code, j));
                                }
                                note->addAttribute("pname", std::string(&pitch_name,1));
                                note->addAttribute("oct", std::to_string(octave));
                                int note_loc = *i - 3; //3 is bottom line in Scribe, 0 in MEI
                                note->addAttribute("loc", std::to_string( note_loc ));
                                if (current_color!=coloration_type::full_black)
                                {
                                    switch (current_color) {
                                        case full_red:
                                            note->addAttribute("color", "red");
                                            break;
                                        case void_red:
                                            note->addAttribute("color", "red");
                                            note->addAttribute("void", "true"); //this seems a sensible solution for this problem and a suitable additional attribute to the MEI description
                                            break;
                                        case void_black:
                                            note->addAttribute("void", "true"); //**
                                            break;
                                        case full_blue:
                                            note->addAttribute("color", "blue");
                                            break;
                                        default:
                                            break;
                                    }
                                }
                                temp_foster->addChild(note);
                            }
                            i+=j-1;
                        }
                    }
                        break;
                        //dot needs to be handled as a unique element in our extended definition
                        /*Stinson, 7 July 2013: Further notes on DOT
                         The code has two arguments: the first is the substantive position on the staff; the second refines that position up or down and is capable of five variants: 0 = exactly on the line or exactly in the middle of the space between the lines; -1 = 0.1 of the space between the lines below (or for +, above) the space or line; -2= 0.2 of the space below the normal position for that line or space; -3 = 0.3 below the normal position; -4 = 0.4 below the normal position.
                         Only values between 0 and 4 are permitted as the second argument as 5 would be the equivalent of having the dot on the next numbered line or space, e.g. '7 -5', if it were permitted, would be the same as '6 0'.*/
                    case code_t::dot:
                    {
                        Dot* dot = new Dot;
                        char pitch_name = loc_clef.get_pitch_name(eventit->pitch_num[0]);
                        int octave = loc_clef.get_octave(eventit->pitch_num[0]);
                        dot->addAttribute("ploc", std::string(&pitch_name,1));
                        dot->addAttribute("oloc", std::to_string(octave));
                        /*vo: records the vertical adjustment of a feature's programmatically-determined location in terms of staff interline distance; that is, in units of 1/2 the distance between adjacent staff lines. (MEI2013)*/
                        //only set for non-defult positions
                        if (eventit->pitch_num[1]!=0)
                        {
                            float v_pos = eventit->pitch_num[1]/10.0*2;
                            dot->addAttribute("vo", to_string_with_precision(v_pos,1));
                        }
                        foster->addChild(dot);
                    }
                        break;
                    case code_t::rest:
                    {
                        Rest* rest = new Rest;
                        foster->addChild(rest);
                        switch (*(eventit->code.c_str())) {
                                //rests of type 'R' has two associated pitch numbers from which we might infer the type
                            case generic_rest:
                            {
                                int end = eventit->pitch_num[0];
                                int start = eventit->pitch_num[1];
                                int rest_type = start-end;
                                switch (rest_type) {
                                    case minim_rest:
                                        rest->addAttribute("type", "minima");
                                        break;
                                    case semibreve_rest:
                                        rest->addAttribute("type", "semibrevis");
                                        break;
                                    case breve_rest:
                                        rest->addAttribute("type", "brevis");
                                        break;
                                    case long_rest:
                                        rest->addAttribute("type", "longa imperfecta");
                                        break;
                                    case perf_long_rest:
                                        rest->addAttribute("type", "long perfecta");
                                        break;
                                    default:
                                        break;
                                }
                                char ploc = loc_clef.get_pitch_name(start);
                                rest->addAttribute("ploc", std::string(&ploc,1));
                                rest->addAttribute("oloc", std::to_string(loc_clef.get_octave(start)));
                                break;
                                //also process 'RSM', semiminim rest
                            }
                                //case semiminim_rest:
                                //rest->SetAttribute("type", "semiminim");
                                //    break;
                            default:
                                rest->addAttribute("type", scribe_data.GetCodes()->code_to_name(eventit->code));
                                if (!eventit->pitch_num.empty()) {
                                    char pitch_name = loc_clef.get_pitch_name(eventit->pitch_num[0]);
                                    int octave = loc_clef.get_octave(eventit->pitch_num[0]);
                                    rest->addAttribute("ploc", std::string(&pitch_name,1));
                                    rest->addAttribute("oloc", std::to_string(octave));
                                }
                                break;
                        }
                    }
                        break;
                    // non-standard mensuration signs
                    case code_t::mensuration:
                    {
                        Mensur* mensuration_sign = new Mensur;
                        foster->addChild(mensuration_sign);
                        
                        if (eventit->code == "MO" || eventit->code == "MC" || eventit->code == "MO." || eventit->code == "MC.")
                        {
                            char the_sign = eventit->code[1];
                            mensuration_sign->addAttribute("sign", std::string(&the_sign,1));
                            if (eventit->code.size()==3 && eventit->code[2]=='.') {
                                mensuration_sign->addAttribute("dot", "true");
                            }
                            //also able to set attribute 'orient' to reversed for reversed signs; and slash attribute for cut signs
                        }
                        if (eventit->code == ".D." || eventit->code == ".Q." || eventit->code == ".SI." || eventit->code == ".P." || eventit->code == ".N." || eventit->code == ".O." || eventit->code == ".I.") //also .SG.?
                        {
                            //these are wholly new to the MEI schema; the whole dot-letter-dot sign is encoded
                            mensuration_sign->addAttribute("sign", eventit->code);
                        }
                        break;
                    }
                    case code_t::barline:
                    {
                        BarLine* barline = new BarLine;
                        foster->addChild(barline);
                        if (eventit->code == "QBAR") {
                            
                            barline->addAttribute("rend", "quarter"); //non-standard data type for rend.
                        }
                        if (eventit->code == "HBAR") {
                            
                            barline->addAttribute("rend", "half");
                        }
                        if (eventit->code == "WBAR") {
                            
                            barline->addAttribute("rend", "single");
                        }
                        if (eventit->code == "DBAR") {
                            
                            barline->addAttribute("rend", "dbl");
                        }
                        
                        //modern bar editorial - ignore?
                        if (eventit->code == "MBAR") {
                            
                            barline->addAttribute("barplace", "takt");
                            barline->addAttribute("taktplace", std::string(9,1));
                        }
                        
                        //also able to see rend attribute
                        
                        break;
                    }
                    case code_t::clef:
                    {
                        //NB. old clefchange element superceded; clefGrp used for simultaneous clefs
                        loc_clef.clef_line = *(eventit->pitch_num.begin());
                        loc_clef.clef = *(eventit->code.c_str());
                        Clef* clef = new Clef;
                        clef->addAttribute("line", std::to_string( ((loc_clef.clef_line + 1)/2) - 1));
                        clef->addAttribute("shape", std::string(&(loc_clef.clef),1).c_str());
                        foster->addChild(clef);
                        break;
                    }
                        //The MEI accidental names are not used: diesis, b-rotundum and b-quadratum are. Other variants may be added. All ms accidentials in Scribe (as they should be in NeoScribe) are independent elements
                    case code_t::accidental:
                    {
                        Accid* accid = new Accid;
                        accid->addAttribute("accidental", scribe_data.GetCodes()->code_to_name(eventit->code));
                        if (!eventit->pitch_num.empty()) {
                            char ploc = loc_clef.get_pitch_name(eventit->pitch_num[0]);
                            int oloc = loc_clef.get_octave(eventit->pitch_num[0]);
                            accid->addAttribute("ploc", std::string(&ploc,1));
                            accid->addAttribute("oloc", std::to_string(oloc));
                        }
                        foster->addChild(accid);
                        break;
                    }
                    case code_t::other:
                        //lucunae
                    default:
                        break;
                }
                
            }
            
        }
    }
    
    return staff;
}