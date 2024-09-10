void doPort(
        const void * const addr,
        const int parportfd,
        const unsigned char mask[NUM_REGISTERS],
        const unsigned char vals[NUM_REGISTERS],
        mxLogical * const out,
        const int n,
        const uint8_T * const data,
        const int numVals,
        const bool writing
        ) {
    static bool setup = false;

    uint64_T reg;
    unsigned char b;
    int result, i, j, reader, writer, offsets[NUM_REGISTERS] = OFFSETS; /*lame*/

    for (i = 0; i < NUM_REGISTERS; i++) {
        if (mask[i] != 0) {
            switch (offsets[i]) {
                case DATA_OFFSET:
                    reader = PPRDATA; /*need PPDATADIR set non-zero*/
                    writer = PPWDATA; /*need PPDATADIR set zero*/
                    break;
                case STATUS_OFFSET:
                    reader = PPRSTATUS;
                    break;
                case CONTROL_OFFSET:
                    reader = PPRCONTROL;
                    writer = PPWCONTROL;
                    break;
                case ECR_OFFSET:
                    if (USE_PPDEV) {
                        mexErrMsgTxt("ECR not supported under PPDEV (figure out correct PPSETMODE)");
                    }
                    break;
                default:
                    mexErrMsgTxt("bad offset");
                    break;
            }
            reg = *(uint64_T *)addr + offsets[i];
            readPort(reg,&b,parportfd,reader,offsets[i]);

            if (writing) {
                switch (offsets[i]) {
                    case STATUS_OFFSET:
                        mexErrMsgTxt("can't write to status register");
                        break;
                    case CONTROL_OFFSET:
                        for (j=4; j<=7; j++) {
                            if (getBit(mask[i],j)) {
                                mexErrMsgTxt("bad control bit for writing");
                            }
                        }
                        break;
                }
                if (DEBUG) {
                    printf("old %d:",i);
                    printBits(b);
                }
                b = (b & ~mask[i]) | vals[i]; /*frob*/
                if (DEBUG) {
                    printf(" -> ");
                    printBits(b);
                }
                if (offsets[i] != ECR_OFFSET && ENABLE_WRITE) {
                    if (USE_PPDEV) {
                        ppd(parportfd,writer,&b,"couldn't write pport");
                        /* printf("%d\n",offsets[i]); */
                    } else {
                        outb(b,reg);
                    }
                    if (out != NULL || DEBUG) {
                        readPort(reg,&b,parportfd,reader,offsets[i]);
                        
                        if (DEBUG) {
                            printf(" -> ");
                            printBits(b);
                            printf("\n");
                        }
                    }
                } else {
                    printf(" not actually writing to register, either writes disabled or ECR protection\n");
                }
            }

            if (out != NULL) {
                for (j = 0; j < numVals; j++) {
                    if (data[j+numVals] == offsets[i]) {
                        out[j+n*numVals] = getBit(b,data[j]);
                        if (DEBUG) {
                            printf("wrote a %d\n",out[j+n*numVals]);
                        }
                    }
                }
            }

        }
    }

}