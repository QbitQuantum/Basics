bool8 ObjReader::LoadObj(char8 *aFilename)
{
   FILE *ifp;
   char8 ch1, ch2, charBuffer[4096], valStr[20][4096];
   uint32 numRead;
   uint32 rawPositionIdx = 0;
   uint32 rawNormalIdx = 0;
   uint32 rawTexCoordIdx = 0;
   uint32 i;

   //first pass to count number of elements in each array
   errno_t result = fopen_s( &ifp, aFilename, "r" );

   if( result != 0 )
   {
       return false;
   }

   while (!feof(ifp))
   {
      fgets(charBuffer, 4096, ifp);
      numRead = sscanf_s(charBuffer, "%c%c%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n", &ch1, &ch2, 
         &valStr[0][0], &valStr[1][0], &valStr[2][0], &valStr[3][0], &valStr[4][0],
         &valStr[5][0], &valStr[6][0], &valStr[7][0], &valStr[8][0], &valStr[9][0],
         &valStr[10][0], &valStr[11][0], &valStr[12][0], &valStr[13][0], &valStr[14][0],
         &valStr[15][0], &valStr[16][0], &valStr[17][0], &valStr[18][0], &valStr[19][0]         
         );

      switch(ch1)
      {
         case 'g':
         break;
         case 'v':
            if(ch2 == ' ')
            {
               mNumRawPosition++;
            }
            else if(ch2 == 'n')
            {
               mNumRawNormal++;
            }
            else if(ch2 == 't')
            {
               mNumRawTexCoord++;
            }
         break;
         case 'f':
            mNumRawIndex += (numRead - 4) * 3;
         break;      
      }
   }

   //second pass to load in raw data
   fseek(ifp, 0, SEEK_SET);

   rawPositionIdx = 0;
   rawNormalIdx = 0;
   rawTexCoordIdx = 0;

   mRawPosition  = new float32 [mNumRawPosition * 3];
   mRawNormal  = new float32 [mNumRawNormal * 3];
   mRawTexCoord  = new float32 [mNumRawTexCoord * 2];
   mIndex  = new uint32 [mNumRawIndex];

   //for now allocate max size, and end of index condensing, reallocate arrays to optimal size
   mPosition = new float32 [mNumRawIndex * 3];
   mNormal = new float32 [mNumRawIndex * 3];
   mTexCoord = new float32 [mNumRawIndex * 2];
   
   mRawIndexTranslation = new uint32 [mNumRawIndex * 3];

   while (!feof(ifp))
   {
      fgets(charBuffer, 4096, ifp);
      //numRead = sscanf(charBuffer, "%c%c%s%s%s%s\n", &ch1, &ch2, &valStr[0][0], &valStr[1][0], &valStr[2][0], &valStr[3][0]);
      numRead = sscanf_s(charBuffer, "%c%c%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n", &ch1, &ch2, 
         &valStr[0][0], &valStr[1][0], &valStr[2][0], &valStr[3][0], &valStr[4][0],
         &valStr[5][0], &valStr[6][0], &valStr[7][0], &valStr[8][0], &valStr[9][0],
         &valStr[10][0], &valStr[11][0], &valStr[12][0], &valStr[13][0], &valStr[14][0],
         &valStr[15][0], &valStr[16][0], &valStr[17][0], &valStr[18][0], &valStr[19][0]         
         );

      
      switch(ch1)
      {
         case 'g':
         break;
         case 'v':
            if(ch2 == ' ')
            {
               mRawPosition [rawPositionIdx * 3 + 0] = (float32) atof(&valStr[0][0]);
               mRawPosition [rawPositionIdx * 3 + 1] = (float32) atof(&valStr[1][0]);
               mRawPosition [rawPositionIdx * 3 + 2] = (float32) atof(&valStr[2][0]);
               rawPositionIdx ++;
            }
            else if(ch2 == 'n')
            {
               mRawNormal [rawNormalIdx * 3 + 0] = (float32) atof(&valStr[0][0]);
               mRawNormal [rawNormalIdx * 3 + 1] = (float32) atof(&valStr[1][0]);
               mRawNormal [rawNormalIdx * 3 + 2] = (float32) atof(&valStr[2][0]);
               rawNormalIdx ++;
            }
            else if(ch2 == 't')
            {
               mRawTexCoord [rawTexCoordIdx * 2 + 0] = (float32) atof(&valStr[0][0]);
               mRawTexCoord [rawTexCoordIdx * 2 + 1] = (float32) atof(&valStr[1][0]);
               rawTexCoordIdx ++;
            }
         break;
         case 'f':
            //pack raw indices into array
            uint32 rawIndices[OR_MAX_FACE_VERTS][3];

            if(numRead < 5)
            {
            //error: face has less than 3 sides
            break;
            }

            for(i = 0; i < (numRead - 2); i++)
            {
               sscanf_s(&valStr[i][0], "%d/%d/%d", &rawIndices[i][0], &rawIndices[i][1], &rawIndices[i][2] ); 
               
               //convert indices to zero base instead of 1 base
               rawIndices[i][0]--;
               rawIndices[i][1]--;
               rawIndices[i][2]--;
            }

            for(i = 0; i < (numRead - 4); i++) //convert face polygon into a triangle fan e.g. (0,1,2) (0,2,3) (0,3,4) etc..
            {  //note that the first index looks funny (0, i+1, i+2) but is correct..
               mIndex [mNumIndex + 0] = LookupCreateIndex(rawIndices[0][0], rawIndices[0][1], rawIndices[0][2]);
               mIndex [mNumIndex + 1] = LookupCreateIndex(rawIndices[1+i][0], rawIndices[1+i][1], rawIndices[1+i][2]);
               mIndex [mNumIndex + 2] = LookupCreateIndex(rawIndices[2+i][0], rawIndices[2+i][1], rawIndices[2+i][2]);              
               mNumIndex += 3;
            }
         break;      
      }
   }

   //delete unnecessary raw data arrays
   delete [] mRawIndexTranslation;
   delete [] mRawPosition;
   delete [] mRawNormal;
   delete [] mRawTexCoord;

   CalculateTangentSpace();

   return TRUE;
}