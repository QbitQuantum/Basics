int CVPParser::Parse(const char *str)
{
    int i,iline = 0;
    bool inProgram = false;
    std::stringstream input(str);
    struct nvfx_src none = nvfx_src(nvfx_reg(NVFXSR_NONE,0));

    while(!input.eof()) {
        char line[256];
        opcode *opc = NULL;
        struct nvfx_insn *insn = NULL;

        input.getline(line,255);
        iline++;

        for(i=0; i<256; i++) {
            char c = line[i];

            if(c=='\n' || c=='\r' || c==';')
                c = 0;
            if(c=='\t')
                c = ' ';

            line[i] = c;
            if(c==0) break;
        }

        if(line[0]=='#') {
            ParseComment(line);
            continue;
        }

        if(!inProgram) {
            if(strncmp(line,"!!VP2.0",7)==0)
                inProgram = true;
            else if(strncmp(line,"!!ARBvp1.0",10)==0)
                inProgram = true;

            continue;
        }

        char *label = NULL;
        char *col_ptr = NULL;
        char *opcode = NULL;
        char *ptr = line;

        if((col_ptr = strstr((char*)ptr,":"))!=NULL) {
            int j = 0;
            bool valid = true;

            while((ptr+j)<col_ptr) {
                if(j==0 && !(isLetter(ptr[j]) || ptr[j]=='_')) valid = false;
                if(!(isLetter(ptr[j]) || isDigit(ptr[j]) || ptr[j]=='_')) valid = false;
                j++;
            }

            if(valid) {
                label = strtok(ptr,":\x20");
                ptr = col_ptr + 1;
            }
        }

        opcode = strtok(ptr," ");

        if(label) {
            jmpdst d;

            strcpy(d.ident,label);
            d.location = m_nInstructions;
            m_lIdent.push_back(d);
        }

        if(opcode) {
            char *param_str = SkipSpaces(strtok(NULL,"\0"));
            if(strcasecmp(opcode,"OPTION")==0) {
                if(strncasecmp(param_str,"NV_vertex_program3",18)==0)
                    m_nOption |= NV_OPTION_VP3;
                continue;
            } else if(strcasecmp(opcode,"PARAM")==0)
                continue;
            else if(strcasecmp(opcode,"TEMP")==0)
                continue;
            else {
                opc = FindOpcode(opcode);

                insn = &m_pInstructions[m_nInstructions];

                if(!opc) continue;

                InitInstruction(insn,opc->opcode);
                if(opc->opcode==OPCODE_END) {
                    m_nInstructions++;
                    break;
                }

                char *opc_ext = opcode + strlen(opc->mnemonic);
                if(m_nOption&(NV_OPTION_VP2|NV_OPTION_VP3)) {
                    if(opc_ext[0]=='C') {
                        insn->cc_update = TRUE;

                        if(m_nOption&NV_OPTION_VP3 && (opc_ext[1]=='0' || opc_ext[1]=='1')) {
                            switch(opc_ext[1]) {
                            case '0':
                                insn->cc_update_reg = 0;
                                break;
                            case '1':
                                insn->cc_update_reg = 1;
                                break;
                            }
                            opc_ext++;
                        }
                        opc_ext++;
                    }
                }
                if(opc_ext[0]=='_') {
                    if(strncasecmp(opc_ext,"_sat",4)==0) insn->sat = TRUE;
                }
                ParseInstruction(insn,opc,param_str);
                m_nInstructions++;
            }
        }
    }

    for(std::list<jmpdst>::iterator r=m_lJmpDst.begin(); r!=m_lJmpDst.end(); r++) {
        bool found = false;

        for(std::list<jmpdst>::iterator i=m_lIdent.begin(); i!=m_lIdent.end(); i++) {
            if(strcmp(r->ident,i->ident)==0) {
                found = true;
                m_pInstructions[r->location].dst = nvfx_reg(NVFXSR_RELOCATED,i->location);
                break;
            }
        }

        if(found==false) {
            fprintf(stderr,"Identifier \'%s\' not found.\n",r->ident);
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}