void Reed_solomon_code::do_forney(uint8_t* data,int len,uint8_t* pos, int pos_len, uint8_t* sigma, int sigma_len, uint8_t* omega, int omega_len){
	for(int i=0;i<pos_len;i++){
		uint8_t zlog=255-shared_galois.log_tbl[pos[i]];
		uint8_t ov=shared_galois.calc_omega_value(omega,omega_len,zlog);
		uint8_t dv=shared_galois.calc_sigma_dash_value(sigma,sigma_len,zlog);
		data[shared_galois.to_pos(len,pos[i])]^=shared_galois.div_exp(shared_galois.div(ov,dv),zlog);
	}
}