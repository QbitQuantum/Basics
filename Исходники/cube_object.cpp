/**
 * Actually do the recognition using the specified language mode. If none
 * is specified, the default language model in the CubeRecoContext is used.
 * @return the sorted list of alternate answers
 * @param word_mode determines whether recognition is done as a word or a phrase
 */
WordAltList *CubeObject::Recognize(LangModel *lang_mod, bool word_mode) {
  if (char_samp_ == NULL) {
    return NULL;
  }

  // clear alt lists
  Cleanup();

  // no specified language model, use the one in the reco context
  if (lang_mod == NULL) {
    lang_mod = cntxt_->LangMod();
  }

  // normalize if necessary
  if (cntxt_->SizeNormalization()) {
    Normalize();
  }

  // assume not de-slanted by default
  deslanted_ = false;

  // create a beam search object
  if (beam_obj_ == NULL) {
    beam_obj_ = new BeamSearch(cntxt_, word_mode);
  }

  // create a cube search object
  if (srch_obj_ == NULL) {
    srch_obj_ = new CubeSearchObject(cntxt_, char_samp_);
  }

  // run a beam search against the tesslang model
  alt_list_ = beam_obj_->Search(srch_obj_, lang_mod);

  // deslant (if supported by language) and re-reco if probability is low enough
  if (cntxt_->HasItalics() == true &&
      (alt_list_ == NULL || alt_list_->AltCount() < 1 ||
       alt_list_->AltCost(0) > CubeUtils::Prob2Cost(kMinProbSkipDeslanted))) {

    if (deslanted_beam_obj_ == NULL) {
      deslanted_beam_obj_ = new BeamSearch(cntxt_);
    }

    if (deslanted_srch_obj_ == NULL) {
      deslanted_char_samp_ = char_samp_->Clone();
      if (deslanted_char_samp_ == NULL) {
        fprintf(stderr, "Cube ERROR (CubeObject::Recognize): could not "
                "construct deslanted CharSamp\n");
        return NULL;
      }

      if (deslanted_char_samp_->Deslant() == false) {
        return NULL;
      }

      deslanted_srch_obj_ = new CubeSearchObject(cntxt_, deslanted_char_samp_);
    }

    // run a beam search against the tesslang model
    deslanted_alt_list_ = deslanted_beam_obj_->Search(deslanted_srch_obj_,
                                                      lang_mod);
    // should we use de-slanted altlist?
    if (deslanted_alt_list_ != NULL &&  deslanted_alt_list_->AltCount() > 0) {
      if (alt_list_ == NULL || alt_list_->AltCount() < 1 ||
          deslanted_alt_list_->AltCost(0) < alt_list_->AltCost(0)) {
        deslanted_ = true;
        return deslanted_alt_list_;
      }
    }
  }

  return alt_list_;
}