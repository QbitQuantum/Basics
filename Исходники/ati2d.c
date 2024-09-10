int __stdcall srv_2d(ioctl_t *io)
{
    u32_t *inp;
    u32_t *outp;

    inp = io->input;
    outp = io->output;

    switch(io->io_code)
    {
        case SRV_GETVERSION:
            if(io->out_size==4)
            {
                *outp = API_VERSION;
                return 0;
            }
            break;

        case PX_CREATE:
            if(io->inp_size==7)
                return CreatePixmap((pixmap_t*)inp);
            break;

        case PX_DESTROY:
            if(io->inp_size==7)
                return DestroyPixmap((pixmap_t*)inp);
            break;

        case PX_CLEAR:
            if(io->inp_size==2)
                return ClearPixmap((io_clear_t*)inp);
            break;

        case PX_DRAW_RECT:
            if(io->inp_size==7)
                return DrawRect((io_draw_t*)inp);
            break;

        case PX_FILL_RECT:
            if(io->inp_size==10)
                return FillRect((io_fill_t*)inp);
            break;

        case PX_LINE:
            if(io->inp_size==6)
                return Line((io_draw_t*)inp);
            break;

        case PX_BLIT:
            if(io->inp_size==8)
                return Blit((io_blit_t*)inp);
            break;

        case  PX_BLIT_TRANSPARENT:
            if(io->inp_size==9)
                return BlitTransparent((io_blit_t*)inp);
            break;

        case PX_BLIT_ALPHA:
            if(io->inp_size==9)
                return RadeonComposite((io_blit_t*)inp);
            break;

        default:
            return ERR_PARAM;
  };

  return ERR_PARAM;
}