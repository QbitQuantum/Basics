int
main( int argc, char *argv[] )
{
     DFBResult ret;
     bool      quit = false;
     Test      test;

     ret = Initialize( &test, &argc, &argv );
     if (ret)
          goto error;

     ret = InitGL( &test );
     if (ret)
          goto error;

     ret = InitTexture( &test, &test.texture, 256, 256 );
     if (ret)
          goto error;

     /*
      * Main Loop
      */
     while (!quit) {
          static int frames = 0;
          static double tRot0 = -1.0, tRate0 = -1.0;
          double dt, t = direct_clock_get_millis() / 1000.0;

          if (tRot0 < 0.0)
             tRot0 = t;
          dt = t - tRot0;
          tRot0 = t;

          /* advance rotation for next frame */
          angle += 70.0 * dt;  /* 70 degrees per second */
          if (angle > 3600.0)
             angle -= 3600.0;

          ret = RenderTexture( &test, &test.texture );
          if (ret)
               goto error;

          ret = RenderGL( &test );
          if (ret)
               goto error;

          /*
           * Show the rendered buffer
           */
          test.primary->Flip( test.primary, NULL, DSFLIP_ONSYNC );


          frames++;

          if (tRate0 < 0.0)
             tRate0 = t;
          if (t - tRate0 >= 5.0) {
             GLfloat seconds = t - tRate0;
             GLfloat fps = frames / seconds;
             printf("%d frames in %3.1f seconds = %6.3f FPS\n", frames, seconds,
                   fps);
             tRate0 = t;
             frames = 0;
          }


          DFBInputEvent evt;

          /*
           * Process events
           */
          while (test.events->GetEvent( test.events, DFB_EVENT(&evt) ) == DFB_OK) {
               switch (evt.type) {
                    case DIET_KEYPRESS:
                         switch (evt.key_symbol) {
                              case DIKS_ESCAPE:
                                   quit = true;
                                   break;
                              case DIKS_CURSOR_UP:
                                   inc_rotx = 5.0;
                                   break;
                              case DIKS_CURSOR_DOWN:
                                   inc_rotx = -5.0;
                                   break;
                              case DIKS_CURSOR_LEFT:
                                   inc_roty = 5.0;
                                   break;
                              case DIKS_CURSOR_RIGHT:
                                   inc_roty = -5.0;
                                   break;
                              case DIKS_PAGE_UP:
                                   inc_rotz = 5.0;
                                   break;
                              case DIKS_PAGE_DOWN:
                                   inc_rotz = -5.0;
                                   break;
                              default:
                                   ;
                         }
                         break;
                    case DIET_KEYRELEASE:
                         switch (evt.key_symbol) {
                              case DIKS_CURSOR_UP:
                                   inc_rotx = 0;
                                   break;
                              case DIKS_CURSOR_DOWN:
                                   inc_rotx = 0;
                                   break;
                              case DIKS_CURSOR_LEFT:
                                   inc_roty = 0;
                                   break;
                              case DIKS_CURSOR_RIGHT:
                                   inc_roty = 0;
                                   break;
                              case DIKS_PAGE_UP:
                                   inc_rotz = 0;
                                   break;
                              case DIKS_PAGE_DOWN:
                                   inc_rotz = 0;
                                   break;
                              default:
                                   ;
                         }
                         break;
                    case DIET_AXISMOTION:
                         if (evt.flags & DIEF_AXISREL) {
                              switch (evt.axis) {
                                   case DIAI_X:
                                        view_rot[1] += evt.axisrel / 2.0;
                                        break;
                                   case DIAI_Y:
                                        view_rot[0] += evt.axisrel / 2.0;
                                        break;
                                   case DIAI_Z:
                                        view_rot[2] += evt.axisrel / 2.0;
                                        break;
                                   default:
                                        ;
                              }
                         }
                         break;
                    default:
                         ;
               }
          }

          view_rot[0] += inc_rotx;
          view_rot[1] += inc_roty;
          view_rot[2] += inc_rotz;
     }


error:
     Shutdown( &test );

     return ret;
}