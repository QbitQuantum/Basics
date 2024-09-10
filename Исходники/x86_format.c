static int format_xml_insn( x86_insn_t *insn, char *buf, int len ) {
        char str[MAX_OP_XML_STRING];
        int i;

        STRNCAT( buf, "<x86_insn>\n", len );

        STRNCATF( buf, "\t<address rva=\"0x%08X\" ", insn->addr, len );
        STRNCATF( buf, "offset=\"0x%08X\" ", insn->offset, len );
        STRNCATF( buf, "size=%d bytes=\"", insn->size, len );

        for ( i = 0; i < insn->size; i++ ) {
                STRNCATF( buf, "%02X ", insn->bytes[i], len );
        }
        STRNCAT( buf, "\"/>\n", len );

        STRNCAT( buf, "\t<prefix type=\"", len );
        len -= format_insn_prefix_str( insn->prefix, buf, len );
        STRNCATF( buf, "\" string=\"%s\"/>\n", insn->prefix_string, len );

        STRNCATF( buf, "\t<mnemonic group=\"%s\" ",
                  get_insn_group_str (insn->group), len );
        STRNCATF( buf, "type=\"%s\" ", get_insn_type_str (insn->type), len );
        STRNCATF( buf, "string=\"%s\"/>\n", insn->mnemonic, len );

        STRNCAT( buf, "\t<flags type=set>\n", len );
        STRNCAT( buf, "\t\t<flag name=\"", len );
        len -= format_insn_eflags_str( insn->flags_set, buf, len );
        STRNCAT( buf, "\"/>\n\t</flags>\n", len );


        STRNCAT( buf, "\t<flags type=tested>\n", len );
        STRNCAT( buf, "\t\t<flag name=\"", len );
        len -= format_insn_eflags_str( insn->flags_tested, buf, len );
        STRNCAT( buf, "\"/>\n\t</flags>\n", len );

	if ( x86_operand_1st( insn ) ) {
        	x86_format_operand( x86_operand_1st(insn), str,
                           sizeof str, xml_syntax);
        	STRNCAT( buf, "\t<operand name=dest>\n", len );
        	STRNCAT( buf, str, len );
        	STRNCAT( buf, "\t</operand>\n", len );
	}

	if ( x86_operand_2nd( insn ) ) {
        	x86_format_operand( x86_operand_2nd( insn ), str,
                           sizeof str, xml_syntax);
        	STRNCAT( buf, "\t<operand name=src>\n", len );
        	STRNCAT( buf, str, len );
        	STRNCAT( buf, "\t</operand>\n", len );
	}

	if ( x86_operand_3rd( insn ) ) {
        	x86_format_operand( x86_operand_3rd(insn), str,
                           sizeof str, xml_syntax);
        	STRNCAT( buf, "\t<operand name=imm>\n", len );
        	STRNCAT( buf, str, len );
        	STRNCAT( buf, "\t</operand>\n", len );
	}

        STRNCAT( buf, "</x86_insn>\n", len );

        return strlen (buf);
}