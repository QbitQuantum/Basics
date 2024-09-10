bool CKey::mf_CKey_0040(const char * arg_0,const char * arg_1,bool arg_2)
{
	int local_00;
	int local_01;
	int local_02;
	int local_03;
	bool local_04;
	unsigned char local_05[16];
	char local_06[120];

	if (! (arg_2||!m_bln_unk304) ) {
		return m_bln_unk303;
	}
	if (!arg_2) {
		m_bln_unk304=true;
	}

	local_00=strlen(arg_0);
	if (local_00==0) {
		if (!arg_2) {
			m_bln_unk303=true;
		}
		return true;
	}
	if (! (m_bln_unk308||local_00>=2) ) {
		return false;
	}
	m_bln_unk303=false;
	if (! ((int)*arg_0!='%'||local_00!=33) ) {
		ny_aschash2binhash(arg_0+1,local_05);
		if (memcmp((unsigned char *)m_hash_tabun,local_05,16)==0) {
			m_bln_unk303=true;
			return true;
		}
		return false;
	}

	if (*arg_1!=0) {
		if ((int)*arg_1=='#') {
			ny_htmlproc_5(arg_1+1,gbuf400_004);
			if (strcmp(m_char11_nazo2,gbuf400_004)!=0) {
				return false;
			}
			bool dummy;	//orphan jumpの再現用。これをしなくても、制御構造を変えれば出ると思われ
		} else {
			if (strcmp(m_char11_nazo2,arg_1)!=0) {
				return false;
			}
		}
	}

	strcpy(gbuf400_002,mf_CKey_0260());
	if ((unsigned char)gbuf400_002[0]=='@') {
		return false;
	}
	strcpy(gbuf400_003,arg_0);
	local_02=0;
	local_03=0;
	_mbslwr(gbuf400_002);
	_mbslwr(gbuf400_003);
	for (local_01=0; local_01<30; local_01++) {
		gbuf7800_200[local_01*1024]=0;
		*((int *)(local_06+local_01*4))=0;
	}
	local_04=false;
	for (local_01=0; local_01<local_00; local_01++) {
		if (! ((*(gbuf400_003+local_01)==0||(unsigned char)*(gbuf400_003+local_01)==' ')||!((unsigned char)*(gbuf400_003+local_01)!=129)&&(unsigned char)*((gbuf400_003+1)+local_01)=='@') ) {
			*((gbuf7800_200+local_02*1024)+local_03)=*(gbuf400_003+local_01);
			local_03=local_03+1;
			continue;
		}
		if (local_03<2) {
			local_03=0;
		}
		*((int *)(local_06+local_02*4))=local_03;
		*((gbuf7800_200+local_02*1024)+local_03)=0;
		if (local_03>=2) {
			if (*(gbuf7800_200+local_02*1024)!='-') {
				local_04=true;
			}
			if (local_02>=29) break;
			local_02=local_02+1;
		}
		local_03=0;
		if (*(gbuf400_003+local_01)==' ') continue;
		local_01=local_01+1;
	}
	if (! (!(!(local_02!=0)&&(local_03<2||(unsigned char)*(((struct_charptrd *)gbuf7800_200)->d1)=='-'))&&(local_02<=0||local_04)) ) {
		return false;
	}
	if (local_03<2) {
		local_03=0;
	}
	*((int *)(local_06+local_02*4))=local_03;
	*((gbuf7800_200+local_02*1024)+local_03)=0;
	for (local_03=0; local_03<=local_02; local_03++) {
		if (*(gbuf7800_200+local_03*1024)==0||!(gbuf7800_200[local_03*1024]!='-')&&*(gbuf7800_200+local_03*1024+1)==0) continue;
		if (gbuf7800_200[local_03*1024]=='-') {
			if (_mbsstr(gbuf400_002,&gbuf7800_200[local_03*1024+1])==0) continue;
			return false;
		}
		if (_mbsstr(gbuf400_002,&gbuf7800_200[local_03*1024])!=0) continue;
		return false;
	}
	if (!arg_2) {
		m_bln_unk303=true;
	}
	return true;

}