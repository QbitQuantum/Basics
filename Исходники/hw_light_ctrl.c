/*********************************************************************
 * @fn      hwLight_UpdateColorMode
 *
 * @brief   Calculates the new xy of hue/sat value on color mode change
 *
 * @param   NewColorMode - Color Mode Attribute value
 *
 * @return  none
 */
void hwLight_UpdateColorMode(uint8 NewColorMode)
{
  uint8 idx, chosenIdx=0;
  uint32 currDist=0, minDist = 0xFFFFF;

  if( NewColorMode != zclColor_ColorMode )
  {
    if( NewColorMode == COLOR_MODE_CURRENT_X_Y )
    {
      //update the current xy values from hue and sat
      zclColor_CurrentX = hueToX[zclColor_CurrentHue];
      zclColor_CurrentY = hueToY[zclColor_CurrentHue];

      hwLight_satToXy( &zclColor_CurrentX, &zclColor_CurrentY, zclColor_CurrentSaturation );
    }
    else if( NewColorMode == COLOR_MODE_CURRENT_HUE_SATURATION )
    {
      //update the current hue/sat values from xy
      //Loop thrugh hueToX/Y tables and look for the value closest to the
      //zclColor_CurrentX and zclColor_CurrentY
      for( idx = 0; idx != 0xFF; idx++ )
      {
        currDist = ( (uint32)DISTANCE(hueToX[idx], zclColor_CurrentX)
                     + DISTANCE(hueToY[idx], zclColor_CurrentY) );

        if ( currDist < minDist )
        {
          chosenIdx = idx;
          minDist = currDist;
        }
      }
      zclColor_CurrentHue = chosenIdx;

      zclColor_EnhancedCurrentHue = (uint16)zclColor_CurrentHue << 8;

      zclColor_CurrentSaturation = hwLight_XyToSat( zclColor_CurrentX, zclColor_CurrentY, zclColor_CurrentHue );
    }
    else //do nothing COLOR_MODE_COLOR_TEMPERATURE not supported
    {
    }
  }

  return;
}