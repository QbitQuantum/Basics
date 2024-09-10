int DisplayDevice::pick(int dim, const float *pos, const VMDDisplayList *cmdList,
			float &eyedist, int *unitcell, float window_size) {
  char *cmdptr = NULL;
  int tok;
  float newEyeDist, currEyeDist = eyedist;
  int tag = (-1), inRegion, currTag;
  float minX=0.0f, minY=0.0f, maxX=0.0f, maxY=0.0f;
  float fminX=0.0f, fminY=0.0f, fminZ=0.0f, fmaxX=0.0f, fmaxY=0.0f, fmaxZ=0.0f;
  float wpntpos[3], pntpos[3], cpos[3];

  if(!cmdList)
    return (-1);

  // initialize picking: find screen region to look for object
  if (dim == 2) {
    fminX = pos[0] - window_size;
    fmaxX = pos[0] + window_size;
    fminY = pos[1] - window_size;
    fmaxY = pos[1] + window_size;
    abs_screen_pos(fminX, fminY);
    abs_screen_pos(fmaxX, fmaxY);
#if defined(_MSC_VER)
    // Win32 lacks the C99 round() routine
    // Add +/- 0.5 then then round towards zero.
#if 1
    minX = (int) ((float) (fminX + (fminX >= 0.0f ?  0.5f : -0.5f)));
    maxX = (int) ((float) (fmaxX + (fmaxX >= 0.0f ?  0.5f : -0.5f)));
    minY = (int) ((float) (fminY + (fminY >= 0.0f ?  0.5f : -0.5f)));
    maxY = (int) ((float) (fmaxY + (fmaxY >= 0.0f ?  0.5f : -0.5f)));
#else
    minX = truncf(fminX + (fminX >= 0.0f ?  0.5f : -0.5f));
    maxX = truncf(fmaxX + (fmaxX >= 0.0f ?  0.5f : -0.5f));
    minY = truncf(fminY + (fminY >= 0.0f ?  0.5f : -0.5f));
    maxY = truncf(fmaxY + (fmaxY >= 0.0f ?  0.5f : -0.5f));
//    minX = floor(fminX + 0.5);
//    maxX = floor(fmaxX + 0.5);
//    minY = floor(fminY + 0.5);
//    maxY = floor(fmaxY + 0.5);
#endif
#else
    minX = round(fminX);
    maxX = round(fmaxX);
    minY = round(fminY);
    maxY = round(fmaxY);
#endif

  } else {
    fminX = pos[0] - window_size;
    fmaxX = pos[0] + window_size;
    fminY = pos[1] - window_size;
    fmaxY = pos[1] + window_size;
    fminZ = pos[2] - window_size;
    fmaxZ = pos[2] + window_size;
  }

  // make sure we do not disturb the regular transformation matrix
  transMat.dup();
  (transMat.top()).multmatrix(cmdList->mat);

  // Transform the current pick point for each periodic image 
  ResizeArray<Matrix4> pbcImages;
  ResizeArray<int> pbcCells;
  find_pbc_images(cmdList, pbcImages);
  find_pbc_cells(cmdList, pbcCells);
  int pbcimg;
  for (pbcimg=0; pbcimg<pbcImages.num(); pbcimg++) {
    transMat.dup();
    (transMat.top()).multmatrix(pbcImages[pbcimg]);

    // scan through the list, getting each command and executing it, until
    // the end of commands token is found
    VMDDisplayList::VMDLinkIter cmditer;
    cmdList->first(&cmditer);
    while((tok = cmdList->next(&cmditer, cmdptr)) != DLASTCOMMAND) {
      switch (tok) {
        case DPICKPOINT:
          // calculate the transformed position of the point
          {
            DispCmdPickPoint *cmd = (DispCmdPickPoint *)cmdptr;
            vec_copy(wpntpos, cmd->postag);
            currTag = cmd->tag;
          }
          (transMat.top()).multpoint3d(wpntpos, pntpos);

          // check if in picking region ... different for 2D and 3D
          if (dim == 2) {
            // convert the 3D world coordinate to 2D (XY) absolute screen 
            // coordinate, and a normalized Z coordinate.
            abs_screen_loc_3D(pntpos, cpos);
      
            // check to see if the projected picking position falls within the 
            // view frustum, with the XY coords falling within the displayed 
            // window, and the Z coordinate falling within the view volume
            // between the front and rear clipping planes.
            inRegion = (cpos[0] >= minX && cpos[0] <= maxX &&
                        cpos[1] >= minY && cpos[1] <= maxY &&
                        cpos[2] >= 0.0  && cpos[2] <= 1.0);
          } else {
            // just check to see if the position is in a box centered on our
            // pointer.  The pointer position should already be transformed.
            inRegion = (pntpos[0] >= fminX && pntpos[0] <= fmaxX &&	
                        pntpos[1] >= fminY && pntpos[1] <= fmaxY &&
                        pntpos[2] >= fminZ && pntpos[2] <= fmaxZ);
          }

          // Clip still-viable pick points against all active clipping planes
          if (inRegion) {
            // We must perform a check against all of the active
            // user-defined clipping planes to ensure that only pick points
            // associated with visible geometry can be selected.
            int cp;
            for (cp=0; cp < VMD_MAX_CLIP_PLANE; cp++) {
              // The final result is the intersection of all of the
              // individual clipping plane tests...
              if (cmdList->clipplanes[cp].mode) {
                float cpdist[3];
                vec_sub(cpdist, wpntpos, cmdList->clipplanes[cp].center);
                inRegion &= (dot_prod(cpdist, 
                                      cmdList->clipplanes[cp].normal) > 0.0f);
              }
            }
          }
      
          // has a hit occurred?
          if (inRegion) {
            // yes, see if it is closer to the eye position than earlier objects
            if(dim==2) 
              newEyeDist = DTOEYE(pntpos[0], pntpos[1], pntpos[2]);
            else 
              newEyeDist = DTOPOINT(pntpos[0],pntpos[1],pntpos[2]);

            if(currEyeDist < 0.0 || newEyeDist < currEyeDist) {
              currEyeDist = newEyeDist;
              tag = currTag;
              if (unitcell) {
                unitcell[0] = pbcCells[3*pbcimg  ];
                unitcell[1] = pbcCells[3*pbcimg+1];
                unitcell[2] = pbcCells[3*pbcimg+2];
              }
            }
          }
          break;

        case DPICKPOINT_ARRAY:
          // loop over all of the pick points in the pick point index array
          DispCmdPickPointArray *cmd = (DispCmdPickPointArray *)cmdptr;
          float *pickpos=NULL;
          float *crds=NULL;
          int *indices=NULL;
          cmd->getpointers(crds, indices); 

          int i;
          for (i=0; i<cmd->numpicks; i++) {
            pickpos = crds + i*3;
            if (cmd->allselected) {
              currTag = i + cmd->firstindex;
            } else {
              currTag = indices[i];
            }
            vec_copy(wpntpos, pickpos);

            (transMat.top()).multpoint3d(pickpos, pntpos);

            // check if in picking region ... different for 2D and 3D
            if (dim == 2) {
              // convert the 3D world coordinate to 2D absolute screen coord
              abs_screen_loc_3D(pntpos, cpos);

              // check to see if the position falls in our picking region
              // including the clipping region (cpos[2])
              inRegion = (cpos[0] >= minX && cpos[0] <= maxX &&
                          cpos[1] >= minY && cpos[1] <= maxY &&
                          cpos[2] >= 0.0  && cpos[2] <= 1.0);
            } else {
              // just check to see if the position is in a box centered on our
              // pointer.  The pointer position should already be transformed.
              inRegion = (pntpos[0] >= fminX && pntpos[0] <= fmaxX &&
                          pntpos[1] >= fminY && pntpos[1] <= fmaxY &&
                          pntpos[2] >= fminZ && pntpos[2] <= fmaxZ);
            }

            // Clip still-viable pick points against all active clipping planes
            if (inRegion) {
              // We must perform a check against all of the active
              // user-defined clipping planes to ensure that only pick points
              // associated with visible geometry can be selected.
              int cp;
              for (cp=0; cp < VMD_MAX_CLIP_PLANE; cp++) {
                // The final result is the intersection of all of the
                // individual clipping plane tests...
                if (cmdList->clipplanes[cp].mode) {
                  float cpdist[3];
                  vec_sub(cpdist, wpntpos, cmdList->clipplanes[cp].center);
                  inRegion &= (dot_prod(cpdist, 
                                        cmdList->clipplanes[cp].normal) > 0.0f);
                }
              }
            }

            // has a hit occurred?
            if (inRegion) {
              // yes, see if it is closer to the eye than earlier hits
              if (dim==2)
                newEyeDist = DTOEYE(pntpos[0], pntpos[1], pntpos[2]);
              else
                newEyeDist = DTOPOINT(pntpos[0],pntpos[1],pntpos[2]);

              if (currEyeDist < 0.0 || newEyeDist < currEyeDist) {
                currEyeDist = newEyeDist;
                tag = currTag;
                if (unitcell) {
                  unitcell[0] = pbcCells[3*pbcimg  ];
                  unitcell[1] = pbcCells[3*pbcimg+1];
                  unitcell[2] = pbcCells[3*pbcimg+2];
                }
              }
            }
          }
          break;
      }
    }

    // Pop the PBC image transform
    transMat.pop();
  } // end of loop over PBC images

  // make sure we do not disturb the regular transformation matrix
  transMat.pop();

  // return result; if tag >= 0, we found something
  eyedist = currEyeDist;
  return tag;
}