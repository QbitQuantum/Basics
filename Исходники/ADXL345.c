PUBLIC bool_t bShakereadResult( int16* ai16accel )
{
	static 	int16	ai16TmpAccel[3]={0, 0, 0};
	bool_t	bOk = TRUE;
	uint8	au8data[2];
	int16	max = 0x8000;
	uint8	num;				//	FIFOのデータ数
	uint8	i;
	int16	sum[32];
	uint8	count = 0;
	int16	x[33];
	int16	y[33];
	int16	z[33];

	//	FIFOでたまった個数を読み込む
	bOk &= bSMBusWrite(ADXL345_ADDRESS, ADXL345_FIFO_STATUS, 0, NULL );
	bOk &= bSMBusSequentialRead( ADXL345_ADDRESS, 1, &num );

	//	FIFOの中身を全部読む
	num = (num&0x7f);
	if( num == READ_FIFO ){
		//	各軸の読み込み
		for( i=0; i<num; i++ ){
			//	X軸
			bOk &= bGetAxis( ADXL345_IDX_X, au8data );
			x[i] = (((au8data[1] << 8) | au8data[0]));
		}
		for( i=0; i<num; i++ ){
			//	Y軸
			bOk &= bGetAxis( ADXL345_IDX_Y, au8data );
			y[i] = (((au8data[1] << 8) | au8data[0]));
		}
		for( i=0; i<num; i++ ){
			//	Z軸
			bOk &= bGetAxis( ADXL345_IDX_Z, au8data );
			z[i] = (((au8data[1] << 8) | au8data[0]));
		}
		//	FIFOの設定をもう一度
		bOk &= bSetFIFO();

		for( i=0; i<num; i++ ){
			x[i] = (x[i]<<2)/10;
			y[i] = (y[i]<<2)/10;
			z[i] = (z[i]<<2)/10;

			if( i == 0 ){
				sum[i] = ( x[i]-ai16TmpAccel[0] + y[i]-ai16TmpAccel[1] + z[i]-ai16TmpAccel[2] );
			}else{
				sum[i] = ( x[i]-x[i-1] + y[i]-y[i-1] + z[i]-z[i-1] );
			}

			if( sum[i] < 0 ){
				sum[i] *= -1;
			}

			max = sum[i]>max ? sum[i] : max;

			if( sum[i] > u16ThAccel ){
				count++;
			}
#if 0
			vfPrintf(& sSerStream, "\n\r%2d:%d,%d,%d %d", i, x[i], y[i], z[i], sum[i] );
			SERIAL_vFlush(E_AHI_UART_0);
		}
		vfPrintf( &sSerStream, "\n\r" );
#else
		}
#endif
		ai16accel[0] = max;
		ai16accel[1] = z[0];
		ai16accel[2] = count;
		ai16TmpAccel[0] = x[num-1];
		ai16TmpAccel[1] = y[num-1];
		ai16TmpAccel[2] = z[num-1];
	}else{