/*!
    This function decodes some data into image changes.

    Returns the number of bytes consumed.
*/
int QGIFFormat::decode(QImage *image, const uchar *buffer, int length,
                       int *nextFrameDelay, int *loopCount)
{
    // We are required to state that
    //    "The Graphics Interchange Format(c) is the Copyright property of
    //    CompuServe Incorporated. GIF(sm) is a Service Mark property of
    //    CompuServe Incorporated."

    image->detach();
    int bpl = image->bytesPerLine();
    unsigned char *bits = image->bits();

#define LM(l, m) (((m)<<8)|l)
    digress = false;
    const int initial = length;
    while (!digress && length) {
        length--;
        unsigned char ch=*buffer++;
        switch (state) {
          case Header:
            hold[count++]=ch;
            if (count==6) {
                // Header
                gif89=(hold[3]!='8' || hold[4]!='7');
                state=LogicalScreenDescriptor;
                count=0;
            }
            break;
          case LogicalScreenDescriptor:
            hold[count++]=ch;
            if (count==7) {
                // Logical Screen Descriptor
                swidth=LM(hold[0], hold[1]);
                sheight=LM(hold[2], hold[3]);
                gcmap=!!(hold[4]&0x80);
                //UNUSED: bpchan=(((hold[4]&0x70)>>3)+1);
                //UNUSED: gcmsortflag=!!(hold[4]&0x08);
                gncols=2<<(hold[4]&0x7);
                bgcol=(gcmap) ? hold[5] : -1;
                //aspect=hold[6] ? double(hold[6]+15)/64.0 : 1.0;

                trans_index = -1;
                count=0;
                ncols=gncols;
                if (gcmap) {
                    ccount=0;
                    state=GlobalColorMap;
                    globalcmap = new QRgb[gncols+1]; // +1 for trans_index
                    globalcmap[gncols] = Q_TRANSPARENT;
                } else {
                    state=Introducer;
                }
            }
            break;
          case GlobalColorMap: case LocalColorMap:
            hold[count++]=ch;
            if (count==3) {
                QRgb rgb = qRgb(hold[0], hold[1], hold[2]);
                if (state == LocalColorMap) {
                    if (ccount < lncols)
                        localcmap[ccount] =  rgb;
                } else {
                    globalcmap[ccount] = rgb;
                }
                if (++ccount >= ncols) {
                    if (state == LocalColorMap)
                        state=TableImageLZWSize;
                    else
                        state=Introducer;
                }
                count=0;
            }
            break;
          case Introducer:
            hold[count++]=ch;
            switch (ch) {
              case ',':
                state=ImageDescriptor;
                break;
              case '!':
                state=ExtensionLabel;
                break;
              case ';':
                  // ### Changed: QRect(0, 0, swidth, sheight)
                state=Done;
                break;
              default:
                digress=true;
                // Unexpected Introducer - ignore block
                state=Error;
            }
            break;
          case ImageDescriptor:
            hold[count++]=ch;
            if (count==10) {
                int newleft=LM(hold[1], hold[2]);
                int newtop=LM(hold[3], hold[4]);
                int newwidth=LM(hold[5], hold[6]);
                int newheight=LM(hold[7], hold[8]);

                // disbelieve ridiculous logical screen sizes,
                // unless the image frames are also large.
                if (swidth/10 > qMax(newwidth,200))
                    swidth = -1;
                if (sheight/10 > qMax(newheight,200))
                    sheight = -1;

                if (swidth <= 0)
                    swidth = newleft + newwidth;
                if (sheight <= 0)
                    sheight = newtop + newheight;

                QImage::Format format = trans_index >= 0 ? QImage::Format_ARGB32 : QImage::Format_RGB32;
                if (image->isNull()) {
                    (*image) = QImage(swidth, sheight, format);
                    bpl = image->bytesPerLine();
                    bits = image->bits();
                    memset(bits, 0, image->byteCount());
                }

                disposePrevious(image);
                disposed = false;

                left = newleft;
                top = newtop;
                width = newwidth;
                height = newheight;

                right=qMax(0, qMin(left+width, swidth)-1);
                bottom=qMax(0, qMin(top+height, sheight)-1);
                lcmap=!!(hold[9]&0x80);
                interlace=!!(hold[9]&0x40);
                //bool lcmsortflag=!!(hold[9]&0x20);
                lncols=lcmap ? (2<<(hold[9]&0x7)) : 0;
                if (lncols) {
                    if (localcmap)
                        delete [] localcmap;
                    localcmap = new QRgb[lncols+1];
                    localcmap[lncols] = Q_TRANSPARENT;
                    ncols = lncols;
                } else {
                    ncols = gncols;
                }
                frame++;
                if (frame == 0) {
                    if (left || top || width<swidth || height<sheight) {
                        // Not full-size image - erase with bg or transparent
                        if (trans_index >= 0) {
                            fillRect(image, 0, 0, swidth, sheight, color(trans_index));
                            // ### Changed: QRect(0, 0, swidth, sheight)
                        } else if (bgcol>=0) {
                            fillRect(image, 0, 0, swidth, sheight, color(bgcol));
                            // ### Changed: QRect(0, 0, swidth, sheight)
                        }
                    }
                }

                if (disposal == RestoreImage) {
                    int l = qMin(swidth-1,left);
                    int r = qMin(swidth-1,right);
                    int t = qMin(sheight-1,top);
                    int b = qMin(sheight-1,bottom);
                    int w = r-l+1;
                    int h = b-t+1;

                    if (backingstore.width() < w
                        || backingstore.height() < h) {
                        // We just use the backing store as a byte array
                        backingstore = QImage(qMax(backingstore.width(), w),
                                              qMax(backingstore.height(), h),
                                              QImage::Format_RGB32);
                        memset(bits, 0, image->byteCount());
                    }
                    const int dest_bpl = backingstore.bytesPerLine();
                    unsigned char *dest_data = backingstore.bits();
                    for (int ln=0; ln<h; ln++) {
                        memcpy(FAST_SCAN_LINE(dest_data, dest_bpl, ln),
                               FAST_SCAN_LINE(bits, bpl, t+ln) + l, w*sizeof(QRgb));
                    }
                }

                count=0;
                if (lcmap) {
                    ccount=0;
                    state=LocalColorMap;
                } else {
                    state=TableImageLZWSize;
                }
                x = left;
                y = top;
                accum = 0;
                bitcount = 0;
                sp = stack;
                firstcode = oldcode = 0;
                needfirst = true;
                out_of_bounds = left>=swidth || y>=sheight;
            }
            break;
          case TableImageLZWSize: {
            lzwsize=ch;
            if (lzwsize > max_lzw_bits) {
                state=Error;
            } else {
                code_size=lzwsize+1;
                clear_code=1<<lzwsize;
                end_code=clear_code+1;
                max_code_size=2*clear_code;
                max_code=clear_code+2;
                int i;
                for (i=0; i<clear_code; i++) {
                    table[0][i]=0;
                    table[1][i]=i;
                }
                state=ImageDataBlockSize;
            }
            count=0;
            break;
          } case ImageDataBlockSize:
            expectcount=ch;
            if (expectcount) {
                state=ImageDataBlock;
            } else {
                state=Introducer;
                digress = true;
                newFrame = true;
            }
            break;
          case ImageDataBlock:
            count++;
            accum|=(ch<<bitcount);
            bitcount+=8;
            while (bitcount>=code_size && state==ImageDataBlock) {
                int code=accum&((1<<code_size)-1);
                bitcount-=code_size;
                accum>>=code_size;

                if (code==clear_code) {
                    if (!needfirst) {
                        code_size=lzwsize+1;
                        max_code_size=2*clear_code;
                        max_code=clear_code+2;
                    }
                    needfirst=true;
                } else if (code==end_code) {
                    bitcount = -32768;
                    // Left the block end arrive
                } else {
                    if (needfirst) {
                        firstcode=oldcode=code;
                        if (!out_of_bounds && image->height() > y && firstcode!=trans_index)
                            ((QRgb*)FAST_SCAN_LINE(bits, bpl, y))[x] = color(firstcode);
                        x++;
                        if (x>=swidth) out_of_bounds = true;
                        needfirst=false;
                        if (x>=left+width) {
                            x=left;
                            out_of_bounds = left>=swidth || y>=sheight;
                            nextY(bits, bpl);
                        }
                    } else {
                        incode=code;
                        if (code>=max_code) {
                            *sp++=firstcode;
                            code=oldcode;
                        }
                        while (code>=clear_code+2) {
                            *sp++=table[1][code];
                            if (code==table[0][code]) {
                                state=Error;
                                break;
                            }
                            if (sp-stack>=(1<<(max_lzw_bits))*2) {
                                state=Error;
                                break;
                            }
                            code=table[0][code];
                        }
                        *sp++=firstcode=table[1][code];
                        code=max_code;
                        if (code<(1<<max_lzw_bits)) {
                            table[0][code]=oldcode;
                            table[1][code]=firstcode;
                            max_code++;
                            if ((max_code>=max_code_size)
                             && (max_code_size<(1<<max_lzw_bits)))
                            {
                                max_code_size*=2;
                                code_size++;
                            }
                        }
                        oldcode=incode;
                        const int h = image->height();
                        const QRgb *map = lcmap ? localcmap : globalcmap;
                        QRgb *line = 0;
                        if (!out_of_bounds && h > y)
                            line = (QRgb*)FAST_SCAN_LINE(bits, bpl, y);
                        while (sp>stack) {
                            const uchar index = *(--sp);
                            if (!out_of_bounds && h > y && index!=trans_index) {
                                if (index > ncols)
                                    line[x] = Q_TRANSPARENT;
                                else
                                    line[x] = map ? map[index] : 0;
                            }
                            x++;
                            if (x>=swidth) out_of_bounds = true;
                            if (x>=left+width) {
                                x=left;
                                out_of_bounds = left>=swidth || y>=sheight;
                                nextY(bits, bpl);
                                if (!out_of_bounds && h > y)
                                    line = (QRgb*)FAST_SCAN_LINE(bits, bpl, y);
                            }
                        }
                    }
                }
            }
            partialNewFrame = true;
            if (count==expectcount) {
                count=0;
                state=ImageDataBlockSize;
            }
            break;
          case ExtensionLabel:
            switch (ch) {
            case 0xf9:
                state=GraphicControlExtension;
                break;
            case 0xff:
                state=ApplicationExtension;
                break;
#if 0
            case 0xfe:
                state=CommentExtension;
                break;
            case 0x01:
                break;
#endif
            default:
                state=SkipBlockSize;
            }
            count=0;
            break;
          case ApplicationExtension:
            if (count<11) hold[count]=ch;
            count++;
            if (count==hold[0]+1) {
                if (qstrncmp((char*)(hold+1), "NETSCAPE", 8)==0) {
                    // Looping extension
                    state=NetscapeExtensionBlockSize;
                } else {
                    state=SkipBlockSize;
                }
                count=0;
            }
            break;
          case NetscapeExtensionBlockSize:
            expectcount=ch;
            count=0;
            if (expectcount) state=NetscapeExtensionBlock;
            else state=Introducer;
            break;
          case NetscapeExtensionBlock:
            if (count<3) hold[count]=ch;
            count++;
            if (count==expectcount) {
                *loopCount = hold[1]+hold[2]*256;
                state=SkipBlockSize; // Ignore further blocks
            }
            break;
          case GraphicControlExtension:
            if (count<5) hold[count]=ch;
            count++;
            if (count==hold[0]+1) {
                disposePrevious(image);
                disposal=Disposal((hold[1]>>2)&0x7);
                //UNUSED: waitforuser=!!((hold[1]>>1)&0x1);
                int delay=count>3 ? LM(hold[2], hold[3]) : 1;
                // IE and mozilla use a minimum delay of 10. With the minimum delay of 10
                // we are compatible to them and avoid huge loads on the app and xserver.
                *nextFrameDelay = (delay < 2 ? 10 : delay) * 10;

                bool havetrans=hold[1]&0x1;
                trans_index = havetrans ? hold[4] : -1;

                count=0;
                state=SkipBlockSize;
            }
            break;
          case SkipBlockSize:
            expectcount=ch;
            count=0;
            if (expectcount) state=SkipBlock;
            else state=Introducer;
            break;
          case SkipBlock:
            count++;
            if (count==expectcount) state=SkipBlockSize;
            break;
          case Done:
            digress=true;
            /* Netscape ignores the junk, so we do too.
            length++; // Unget
            state=Error; // More calls to this is an error
            */
            break;
          case Error:
            return -1; // Called again after done.
        }
    }