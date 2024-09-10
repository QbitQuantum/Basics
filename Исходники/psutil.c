ps_font_info_type
ps_init (string font_name, tfm_global_info_type tfm_info)
{
  string base_encoding, mapping;
  ps_font_info_type ret;

  libfile_start ("postscript", "map");

  while ((mapping = libfile_line ()) != NULL
         && !STREQ (font_name, strtok (mapping, " \t")))
    ;

  libfile_close ();

  if (mapping == NULL)
    {
      WARNING2 ("%s: No information for font `%s'; using defaults",
                "postscript.map", font_name);
      ret.font_name = xstrdup (font_name);
      base_encoding = "adobestd";
    }
  else
    { /* We found it; dissect the rest of the line for what we need.
         The second word is the full PostScript font name, e.g.,
         `Times-BoldItalic'.  The third word is the base filename for
         the encoding vector.  */
      ret.font_name = strtok (NULL, " \t");
      base_encoding = strtok (NULL, " \t");
    }

  /* Read the encoding file.  We don't store this in the structure we
     return, since we've never needed it.  Perhaps we should anyway.  */
  encoding = read_encoding_file (base_encoding);

  /* The family name would be `Times' for the font `Times-BoldItalic', but it's
     `Helvetica' for `Helvetica'.  (It should be `Lucida' for
     `LucidaBright-Italic', but we don't handle that case -- maybe
     optional arg in mapping file?)  */
  ret.family_name = strchr (ret.font_name, '-');
  if (ret.family_name == NULL)
    ret.family_name = ret.font_name;  /* E.g., `Helvetica'.  */
  else
    ret.family_name
      = substring (ret.font_name, 0, ret.family_name - 1- ret.font_name);

  /* If the font name contains `Bold', that's the weight.  Otherwise,
     guess `Medium'.  (I don't know of any programs that actually care
     about this.  Again, perhaps it should be an optional arg in the
     mapping file.)  */
  ret.weight = strstr (ret.font_name, "Bold") ? "Bold" : "Medium";

  /* We should be able to compute the italic angle by somehow looking at
     the characters.  bdftops.ps rotates the `I' and takes the angle
     that minimizes the width, for example.  xx */
  ret.italic_angle = 0;
  
  /* Monospaced fonts have no stretch or shrink in their interword
     space (or shouldn't), but they do have a nonzero interword space
     (math fonts sometimes have all their interword space parameters set
     to zero).  */
  ret.monospace_p
    = TFM_FONT_PARAMETER (tfm_info, TFM_STRETCH_PARAMETER) == 0.0
      && TFM_FONT_PARAMETER (tfm_info, TFM_SPACE_PARAMETER) != 0.0;

  /* What might be a good way to compute this one?  xx */
  ret.underline_position = -100;
  
  /* Here we can use the rule thickness from the TFM file, if it's set.
     Otherwise, just guess.  (A better guess would be the dominant stem
     width in the font.)  */
  ret.underline_thickness
    = TFM_FONT_PARAMETER (tfm_info, TFM_DEFAULTRULETHICKNESS_PARAMETER)
      ? : 50;

  /* What to do about the UniqueID's?  Actually, I'm not sure they
     should really be necessary.  Adobe wants people to register their
     fonts to get a UniqueID from them, which is semi-reasonable, but a
     lot of trouble.  We just omit them.  */
  ret.unique_id = 0;
  
  /* If there is no version number in the TFM file, then just say it's
     version 0.  */
  ret.version = TFM_FONT_PARAMETER (tfm_info, TFM_VERSION_PARAMETER)
                ? dtoa (TFM_FONT_PARAMETER (tfm_info, TFM_VERSION_PARAMETER))
                : "0.0";

  return ret;
}