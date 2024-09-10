static void parseAnimKeys( Animation *anim,int type ){

	int cnt=0;
	short t_flags;
	in.sgetn( (char*)&t_flags,2 );
	in.pubseekoff( 8,ios_base::cur );
	in.sgetn( (char*)&cnt,2 );
	in.pubseekoff( 2,ios_base::cur );
	_log( "ANIM_TRACK: frames="+itoa( cnt ) );
	Vector pos,axis,scale;
	float angle;
	Quat quat;
	for( int k=0;k<cnt;++k ){
		int time;
		short flags;
		in.sgetn( (char*)&time,4 );
		in.sgetn( (char*)&flags,2 );
		float tens=0,cont=0,bias=0,ease_to=0,ease_from=0;
		if( flags & 1 ) in.sgetn( (char*)&tens,4 );
		if( flags & 2 ) in.sgetn( (char*)&cont,4 );
		if( flags & 4 ) in.sgetn( (char*)&bias,4 );
		if( flags & 8 ) in.sgetn( (char*)&ease_to,4 );
		if( flags & 16 ) in.sgetn( (char*)&ease_from,4 );
		switch( type ){
		case 0xb020:	//POS_TRACK_TAG
			in.sgetn( (char*)&pos,12 );
			if( conv ) pos=conv_tform*pos;
//			_log( "POS_KEY: time="+itoa(time)+" pos="+ftoa( pos.x )+","+ftoa( pos.y )+","+ftoa( pos.z ) );
			if( time<=anim_len ) anim->setPositionKey( time,pos );
			break;
		case 0xb021:	//ROT_TRACK_TAG
			in.sgetn( (char*)&angle,4 );
			in.sgetn( (char*)&axis,12 );
//			_log( "ROT_KEY: time="+itoa(time)+" angle="+ftoa(angle)+" axis="+ftoa(axis.x)+","+ftoa(axis.y)+","+ftoa(axis.z) );
			if( axis.length()>EPSILON ){
				if( flip_tris ) angle=-angle;
				if( conv ) axis=conv_tform.m*axis;
				quat=Quat( cosf( angle/2 ),axis.normalized()*sinf( angle/2 ) )*quat;
				quat.normalize();
			}
			if( time<=anim_len ) anim->setRotationKey( time,quat );
			break;
		case 0xb022:	//SCL_TRACK_TAG
			in.sgetn( (char*)&scale,12 );
			if( conv ) scale=conv_tform.m*scale;
//			scale.x=fabs(scale.x);scale.y=fabs(scale.y);scale.z=fabs(scale.z);
			_log( "SCL_KEY: time="+itoa(time)+" scale="+ftoa( scale.x )+","+ftoa( scale.y )+","+ftoa( scale.z ) );
			if( time<=anim_len ) anim->setScaleKey( time,scale );
			break;
		}
	}
}