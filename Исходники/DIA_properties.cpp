void DIA_properties( void )
{

 char text[80];
 uint16_t hh, mm, ss, ms;
 GtkWidget *dialog;
 uint8_t gmc, qpel,vop;
 uint32_t info=0;
 const char *yesno[2]={QT_TR_NOOP("No"),QT_TR_NOOP("Yes")};
 uint32_t war,har;

    if (playing)
        return;
  
    text[0] = 0;
    if (!avifileinfo)
        return;
  
        // Fetch info
        info=video_body->getSpecificMpeg4Info();
        vop=!!(info & ADM_VOP_ON);
        qpel=!!(info & ADM_QPEL_ON);
        gmc=!!(info & ADM_GMC_ON);
        
        dialog = create_dialog1();

        gtk_register_dialog(dialog);

        sprintf(text, QT_TR_NOOP("%lu x %lu"), avifileinfo->width,avifileinfo->height);
        FILL_ENTRY(label_size);

        sprintf(text, QT_TR_NOOP("%2.3f fps"), (float) avifileinfo->fps1000 / 1000.F);
        FILL_ENTRY(label_fps);

        sprintf(text, QT_TR_NOOP("%ld frames"), avifileinfo->nb_frames);
        FILL_ENTRY(label_number);

        sprintf(text, "%s", fourCC::tostring(avifileinfo->fcc));
        FILL_ENTRY(label_videofourcc);

        if (avifileinfo->nb_frames)
          {
                frame2time(avifileinfo->nb_frames, avifileinfo->fps1000,
                          &hh, &mm, &ss, &ms);
                sprintf(text, QT_TR_NOOP("%02d:%02d:%02d.%03d"), hh, mm, ss, ms);
                FILL_ENTRY(label_duration);	
  
          }
        // Fill in vop, gmc & qpel
        SET_YES(labelPacked,vop);
        SET_YES(labelGMC,gmc);
        SET_YES(labelQP,qpel);
        // Aspect ratio 
        const char *s;
        war=video_body->getPARWidth();
        har=video_body->getPARHeight();
        getAspectRatioFromAR(war,har, &s);
        sprintf(text, QT_TR_NOOP("%s (%u:%u)"), s,war,har);
        FILL_ENTRY(labelAspectRatio);	
        // Now audio
        WAVHeader *wavinfo=NULL;
        if (currentaudiostream) wavinfo=currentaudiostream->getInfo();
          if(wavinfo)
          {
              
              switch (wavinfo->channels)
                {
                case 1:
                    sprintf(text, QT_TR_NOOP("Mono"));
                    break;
                case 2:
                    sprintf(text, QT_TR_NOOP("Stereo"));
                    break;
                default:
                    sprintf(text, "%d",wavinfo->channels);
                    break;
                }
                FILL_ENTRY(label1_audiomode);
              
                sprintf(text, QT_TR_NOOP("%lu Hz"), wavinfo->frequency);
                FILL_ENTRY(label_fq);
                sprintf(text, QT_TR_NOOP("%lu Bps / %lu kbps"), wavinfo->byterate,      wavinfo->byterate * 8 / 1000);
                FILL_ENTRY(label_bitrate);
                sprintf(text, "%s", getStrFromAudioCodec(wavinfo->encoding));
                FILL_ENTRY(label1_audiofourcc);
                // Duration in seconds too
                if(currentaudiostream && wavinfo->byterate>1)
                {
                        uint32_t l=currentaudiostream->getLength();
                        double du;
                        du=l;
                        du*=1000;
                        du/=wavinfo->byterate;
                        ms2time((uint32_t)floor(du), &hh, &mm, &ss, &ms);
                        sprintf(text, QT_TR_NOOP("%02d:%02d:%02d.%03d"), hh, mm, ss, ms);
						FILL_ENTRY(label_audioduration);

						sprintf(text, QT_TR_NOOP("%.2f MB"), l / 1048576.F);
						FILL_ENTRY(labelFileSize);
                }                
                SET_YES(labelVbr, currentaudiostream->isVBR());
        } else
          {
			  DISABLE_WIDGET(frame2);
          }
  
        gtk_dialog_run(GTK_DIALOG(dialog));	
        gtk_unregister_dialog(dialog);
        gtk_widget_destroy(dialog);
}