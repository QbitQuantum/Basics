// Runs through all automops entries and dumps some basic info 
// Returns the number of used protocols
// 
int  automops_dump_all(struct automops* list)
{
	struct automops *head = list;
	struct automops *cur = list;
	struct fields *f=NULL;
	int anzmops=0, used=0;
	char str[64], ft[32];
	uint32_t SA=0, DA=0;
	uint8_t *x, *y;
	char bits_on[18], bits_off[18];
	int i=0, j=0;
		
	do {
		if (cur->used==-1) {
			fprintf(stderr, "AUTOMOPS: Initial element\n");
			if ((cur->next==cur)&&(cur->prev==cur))
				fprintf(stderr, "  No other elements found.\n");
			break;
		}
		if (cur->used>0) used++;
		anzmops++;
		SA=ntohl(cur->SA); x = (uint8_t*) &SA;
		DA=ntohl(cur->DA); y = (uint8_t*) &DA;
		char2bits(cur->layers_on, bits_on);
		char2bits(cur->layers_off, bits_off);
		fprintf(stderr, "Protocol %i: %s -- %s\n"
			" Layercodes:  X T U I M Q S E\n"
			"    requires  %s (0x%02x)\n" 
			"   conflicts  %s (0x%02x)\n"
			" L2: EtherType=%04x, sa=%02x:%02x:%02x:%02x:%02x:%02x, da=%02x:%02x:%02x:%02x:%02x:%02x\n"
			,
			anzmops, cur->name, cur->desc, 
			bits_on, cur->layers_on, bits_off, cur->layers_off,
			cur->etype, cur->sa[0], cur->sa[1], cur->sa[2], cur->sa[3], cur->sa[4], cur->sa[5],
			cur->da[0], cur->da[1], cur->da[2], cur->da[3], cur->da[4], cur->da[5]);
		if (cur->layers_on&MOPS_IP) {
			fprintf(stderr, " IP: proto=%i, SA=%u.%u.%u.%u, DA=%u.%u.%u.%u\n",
				cur->proto, *x, *(x+1), *(x+2), *(x+3), *y, *(y+1), *(y+2), *(y+3));
		} else {
			fprintf(stderr, " IP: ---\n");
		}
		// Walk through field data:
		f=cur->field; j=0;
		while (f!=NULL) {
			j++; // count number of fields
			if (verbose) {
				i=0;
				if (f->longdesc!=NULL) { 
					mz_strncpy(str, f->longdesc, 60);
					if (strnlen(str,60)>=59) i=1;
				}
				else {
					mz_strncpy(str, "-- no long description specified --", 60);
				}
				amp_type2str(f->type, ft);
				fprintf(stderr, "    %02i  Field [%i] '%s' -- %s\n"
					"        Description: %s%s\n"
					"        Type: %s %s %s (%lu/%lu) {%lu..%lu..%lu} shift: %i; %i chars\n"
					,f->i, f->index, f->name, f->shortdesc,
					str, (i) ? "..." : "", 
					ft, (f->constant) ? "FIXED" : "",
					(f->valname!=NULL) ? f->valname : "(no value name)" ,
					(long unsigned int) f->tlv_type, 
					(long unsigned int) f->tlv_len, 
					(long unsigned int) f->min, 
					(long unsigned int) f->val, 
					(long unsigned int) f->max,
					f->leftshift, f->str_s);
			}
			f=f->next;
		}
		if (verbose==0) fprintf(stderr, " %i fields defined.\n", j);
		//---------------------------------
		cur = cur->next;
	}  while (head != cur);
   
	return used;
}