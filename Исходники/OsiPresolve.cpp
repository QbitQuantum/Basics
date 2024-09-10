const CoinPresolveAction *OsiPresolve::presolve(CoinPresolveMatrix *prob)
{
  paction_ = 0;

  prob->status_=0; // say feasible

# if PRESOLVE_DEBUG
  const CoinPresolveAction *pactiond = 0 ;
  presolve_check_sol(prob) ;
# endif
  if ((presolveActions_&4)!=0)
    transferCosts(prob);

/*
  Fix variables before we get into the main transform loop.
*/
  paction_ = make_fixed(prob, paction_);

# if PRESOLVE_DEBUG
  check_and_tell(prob,paction_,pactiond) ;
# endif

  // if integers then switch off dual stuff
  // later just do individually
  bool doDualStuff = true;
  if ((presolveActions_&1)==0) {
    int i;
    int ncol = presolvedModel_->getNumCols();
    for (i=0;i<ncol;i++)
      if (presolvedModel_->isInteger(i))
	doDualStuff=false;
  }


# if CHECK_CONSISTENCY
  presolve_links_ok(prob->rlink_, prob->mrstrt_, prob->hinrow_, prob->nrows_);
# endif

/*
  If we're feasible, set up for the main presolve transform loop.
*/
  if (!prob->status_) {
# if 0
/*
  This block is used during debugging. See ATOI to see how it works. Some
  editing will be required to turn it all on.
*/
    bool slackd = ATOI("SLACKD")!=0;
    //bool forcing = ATOI("FORCING")!=0;
    bool doubleton = ATOI("DOUBLETON")!=0;
    bool forcing = ATOI("off")!=0;
    bool ifree = ATOI("off")!=0;
    bool zerocost = ATOI("off")!=0;
    bool dupcol = ATOI("off")!=0;
    bool duprow = ATOI("off")!=0;
    bool dual = ATOI("off")!=0;
# else
# if 1
    // normal operation --- all transforms enabled
    bool slackSingleton = true;
    bool slackd = true;
    bool doubleton = true;
    bool tripleton = true;
    //#define NO_FORCING
#ifndef NO_FORCING
    bool forcing = true;
#endif
    bool ifree = true;
    bool zerocost = true;
    bool dupcol = true;
    bool duprow = true;
    bool dual = doDualStuff;
# else
    // compile time selection of transforms.
    bool slackd = false;
    bool doubleton = true;
    bool tripleton = true;
    bool forcing = true;
    bool ifree = false;
    bool zerocost = false;
    bool dupcol = false;
    bool duprow = false;
    bool dual = false;
# endif
# endif
    // Switch off some stuff if would annoy set partitioning etc
    if ((presolveActions_&2)!=0) {
      doubleton = false;
      tripleton = false;
      ifree = false;
    }
    // stop x+y+z==1
    if ((presolveActions_&8)!=0)
      prob->setPresolveOptions(prob->presolveOptions()|4);
    // switch on stuff which can't be unrolled easily
    if ((presolveActions_&16)!=0)
      prob->setPresolveOptions(prob->presolveOptions()|16);
    // switch on gub stuff
    if ((presolveActions_&32)!=0)
      prob->setPresolveOptions(prob->presolveOptions()|32);

    /*
      The main loop (just below) starts with a minor loop that does
      inexpensive presolve transforms until convergence. At each iteration
      of this loop, next[Rows,Cols]ToDo is copied over to [rows,cols]ToDo.

      Then there's a block like the one here, which sets [rows,cols]ToDo for
      all rows & cols, followed by executions of a set of expensive
      transforms. Then we come back around for another iteration of the main
      loop. [rows,cols]ToDo is not reset as we come back around, so we dive
      into the inexpensive loop set up to process all.
    */

    int i;
    // say look at all
    if (!prob->anyProhibited()) {
      for (i=0;i<nrows_;i++)
	prob->rowsToDo_[i]=i;
      prob->numberRowsToDo_=nrows_;
      for (i=0;i<ncols_;i++)
	prob->colsToDo_[i]=i;
      prob->numberColsToDo_=ncols_;
    } else {
      // some stuff must be left alone
      prob->numberRowsToDo_=0;
      for (i=0;i<nrows_;i++)
	if (!prob->rowProhibited(i))
	    prob->rowsToDo_[prob->numberRowsToDo_++]=i;
      prob->numberColsToDo_=0;
      for (i=0;i<ncols_;i++)
	if (!prob->colProhibited(i))
	    prob->colsToDo_[prob->numberColsToDo_++]=i;
    }


    int iLoop;
    if (dupcol) {
      // maybe allow integer columns to be checked
      if ((presolveActions_&1)!=0)
	prob->setPresolveOptions(prob->presolveOptions()|1);
      possibleSkip;
      paction_ = dupcol_action::presolve(prob, paction_);
    }
    if (duprow) {
      possibleSkip;
      paction_ = duprow_action::presolve(prob, paction_);
    }
    // Check number rows dropped
    int lastDropped=0;
    /*
      Note that pass_ is incremented in testRedundant, evoked from
      implied_free_action. The bulk of testRedundant is executed every other
      pass.
    */
    prob->pass_=0;
    for (iLoop=0;iLoop<numberPasses_;iLoop++) {

#     ifdef PRESOLVE_SUMMARY
      printf("Starting major pass %d\n",iLoop+1);
#     endif

      const CoinPresolveAction * const paction0 = paction_;
      // look for substitutions with no fill
      //#define IMPLIED 3
#ifdef IMPLIED
      int fill_level=3;
#define IMPLIED2 1
#if IMPLIED!=3
#if IMPLIED>0&&IMPLIED<11
      fill_level=IMPLIED;
      printf("** fill_level == %d !\n",fill_level);
#endif
#if IMPLIED>11&&IMPLIED<21
      fill_level=-(IMPLIED-10);
      printf("** fill_level == %d !\n",fill_level);
#endif
#endif
#else
      int fill_level=2;
#endif
      int whichPass=0;
/*
  Apply inexpensive transforms until convergence.
*/
      while (1) {
	whichPass++;
	prob->pass_++;
	const CoinPresolveAction * const paction1 = paction_;

	if (slackd) {
	  bool notFinished = true;
	  while (notFinished) {
	    possibleBreak;
	    paction_ = slack_doubleton_action::presolve(prob, paction_,
							notFinished);
	  }
	  if (prob->status_)
	    break;
#	  if PRESOLVE_DEBUG
	  check_and_tell(prob,paction_,pactiond) ;
#	  endif
	}

	if (dual&&whichPass==1) {
	  possibleBreak;
	  // this can also make E rows so do one bit here
	  paction_ = remove_dual_action::presolve(prob, paction_);
	  if (prob->status_)
	    break;
	}

	if (doubleton) {
	  possibleBreak;
	  paction_ = doubleton_action::presolve(prob, paction_);
	  if (prob->status_)
	    break;
#	  if PRESOLVE_DEBUG
	  check_and_tell(prob,paction_,pactiond) ;
#	  endif
	}

	if (tripleton) {
	  possibleBreak;
	  paction_ = tripleton_action::presolve(prob, paction_);
	  if (prob->status_)
	    break;
#	  if PRESOLVE_DEBUG
	  check_and_tell(prob,paction_,pactiond) ;
#	  endif
	}

	if (zerocost) {
	  possibleBreak;
	  paction_ = do_tighten_action::presolve(prob, paction_);
	  if (prob->status_)
	    break;
#	  if PRESOLVE_DEBUG
	  check_and_tell(prob,paction_,pactiond) ;
#	  endif
	}

#ifndef NO_FORCING
	if (forcing) {
	  possibleBreak;
	  paction_ = forcing_constraint_action::presolve(prob, paction_);
	  if (prob->status_)
	    break;
#	  if PRESOLVE_DEBUG
	  check_and_tell(prob,paction_,pactiond) ;
#	  endif
	}
#endif

	if (ifree&&(whichPass%5)==1) {
	  possibleBreak;
	  paction_ = implied_free_action::presolve(prob, paction_,fill_level);
	  if (prob->status_)
	    break;
#	  if PRESOLVE_DEBUG
	  check_and_tell(prob,paction_,pactiond) ;
#	  endif
	}

#	if CHECK_CONSISTENCY
	presolve_links_ok(prob->rlink_,prob->mrstrt_,
			  prob->hinrow_,prob->nrows_) ;
#	endif

#	if 0 && PRESOLVE_DEBUG

    /*
      For reasons that escape me just now, the linker is unable to find
      this function. Copying the code from CoinPresolvePsdebug to the head
      of this routine works just fine. Library loading order looks ok. Other
      routines from CoinPresolvePsdebug are found. I'm stumped. -- lh --
    */

	presolve_no_zeros(prob->mcstrt_, prob->colels_, prob->hincol_,
			  prob->ncols_);
#	endif
#	if CHECK_CONSISTENCY
	prob->consistent();
#	endif


	// set up for next pass
	// later do faster if many changes i.e. memset and memcpy
	prob->numberRowsToDo_ = prob->numberNextRowsToDo_;
	int kcheck;	// debug?
	bool found=false;
	kcheck=-1;
	for (i=0;i<prob->numberNextRowsToDo_;i++) {
	  int index = prob->nextRowsToDo_[i];
	  prob->unsetRowChanged(index);
	  prob->rowsToDo_[i] = index;
	  if (index==kcheck) {
	    printf("row %d on list after pass %d\n",kcheck,
		   whichPass);
	    found=true;
	  }
	}
	if (!found&&kcheck>=0)
	  prob->rowsToDo_[prob->numberRowsToDo_++]=kcheck;
	prob->numberNextRowsToDo_=0;
	prob->numberColsToDo_ = prob->numberNextColsToDo_;
	kcheck=-1;
	found=false;
	for (i=0;i<prob->numberNextColsToDo_;i++) {
	  int index = prob->nextColsToDo_[i];
	  prob->unsetColChanged(index);
	  prob->colsToDo_[i] = index;
	  if (index==kcheck) {
	    printf("col %d on list after pass %d\n",kcheck,
		   whichPass);
	    found=true;
	  }
	}
	if (!found&&kcheck>=0)
	  prob->colsToDo_[prob->numberColsToDo_++]=kcheck;
	prob->numberNextColsToDo_=0;
	if (paction_ == paction1&&fill_level>0)
	  break;
      } // End of inexpensive transform loop

      // say look at all
      int i;
      if (!prob->anyProhibited()) {
	for (i=0;i<nrows_;i++)
	  prob->rowsToDo_[i]=i;
	prob->numberRowsToDo_=nrows_;
	for (i=0;i<ncols_;i++)
	  prob->colsToDo_[i]=i;
	prob->numberColsToDo_=ncols_;
      } else {
	// some stuff must be left alone
	prob->numberRowsToDo_=0;
	for (i=0;i<nrows_;i++)
	  if (!prob->rowProhibited(i))
	    prob->rowsToDo_[prob->numberRowsToDo_++]=i;
	prob->numberColsToDo_=0;
	for (i=0;i<ncols_;i++)
	  if (!prob->colProhibited(i))
	    prob->colsToDo_[prob->numberColsToDo_++]=i;
      }
      // now expensive things
      // this caused world.mps to run into numerical difficulties

#     ifdef PRESOLVE_SUMMARY
      printf("Starting expensive\n");
#     endif

      if (dual) {
	int itry;
	for (itry=0;itry<5;itry++) {
	  const CoinPresolveAction * const paction2 = paction_;
	  possibleBreak;
	  paction_ = remove_dual_action::presolve(prob, paction_);
#	  if PRESOLVE_DEBUG
	  check_and_tell(prob,paction_,pactiond) ;
#	  endif
	  if (prob->status_)
	    break;
	  if (ifree) {
#ifdef IMPLIED
#if IMPLIED2 ==0
	    int fill_level=0; // switches off substitution
#elif IMPLIED2!=99
	    int fill_level=IMPLIED2;
#endif
#endif
	    if ((itry&1)==0) {
	      possibleBreak;
	      paction_ = implied_free_action::presolve(prob, paction_,fill_level);
	    }
#	    if PRESOLVE_DEBUG
	    check_and_tell(prob,paction_,pactiond) ;
#	    endif
	    if (prob->status_)
	      break;
	  }
	  if (paction_ == paction2)
	    break;
	}
      } else if (ifree) {
	// just free
#ifdef IMPLIED
#if IMPLIED2 ==0
	int fill_level=0; // switches off substitution
#elif IMPLIED2!=99
	int fill_level=IMPLIED2;
#endif
#endif
	possibleBreak;
	paction_ = implied_free_action::presolve(prob, paction_,fill_level);
	if (prob->status_)
	  break;
      }

      if (dupcol) {
        // maybe allow integer columns to be checked
        if ((presolveActions_&1)!=0)
          prob->setPresolveOptions(prob->presolveOptions()|1);
	possibleBreak;
	paction_ = dupcol_action::presolve(prob, paction_);
#	if PRESOLVE_DEBUG
	check_and_tell(prob,paction_,pactiond) ;
#	endif
	if (prob->status_)
	  break;
      }

      if (duprow) {
	possibleBreak;
	paction_ = duprow_action::presolve(prob, paction_);
#	if PRESOLVE_DEBUG
	check_and_tell(prob,paction_,pactiond) ;
#	endif
	if (prob->status_)
	  break;
      }
      if ((presolveActions_&32)!=0) {
	possibleBreak;
	paction_ = gubrow_action::presolve(prob, paction_);
      }

      bool stopLoop=false;
      {
	int * hinrow = prob->hinrow_;
	int numberDropped=0;
	for (i=0;i<nrows_;i++)
	  if (!hinrow[i])
	    numberDropped++;
	//printf("%d rows dropped after pass %d\n",numberDropped,
	//     iLoop+1);
	if (numberDropped==lastDropped)
	  stopLoop=true;
	else
	  lastDropped = numberDropped;
      }
      // Do this here as not very loopy
      if (slackSingleton) {
        // On most passes do not touch costed slacks
        if (paction_ != paction0&&!stopLoop) {
	  possibleBreak;
          paction_ = slack_singleton_action::presolve(prob, paction_,NULL);
        } else {
          // do costed if Clp (at end as ruins rest of presolve)
	  possibleBreak;
          paction_ = slack_singleton_action::presolve(prob, paction_,NULL);
          stopLoop=true;
        }
      }
#if	PRESOLVE_DEBUG
      presolve_check_sol(prob,1);
#endif
      if (paction_ == paction0||stopLoop)
	break;

    } // End of major pass loop
  }
/*
  Final cleanup: drop zero coefficients from the matrix, then drop empty rows
  and columns.
*/
  if (!prob->status_) {
    paction_ = drop_zero_coefficients(prob, paction_);
#   if PRESOLVE_DEBUG
    check_and_tell(prob,paction_,pactiond) ;
#   endif

    paction_ = drop_empty_cols_action::presolve(prob, paction_);
#   if PRESOLVE_DEBUG
    check_and_tell(prob,paction_,pactiond) ;
#   endif

    paction_ = drop_empty_rows_action::presolve(prob, paction_);
#   if PRESOLVE_DEBUG
    check_and_tell(prob,paction_,pactiond) ;
#   endif
  }
  // Messages
  CoinMessages messages = CoinMessage(prob->messages().language());
  if (prob->status_) {
    if (prob->status_==1)
	  prob->messageHandler()->message(COIN_PRESOLVE_INFEAS,
					     messages)
					       <<prob->feasibilityTolerance_
					       <<CoinMessageEol;
    else if (prob->status_==2)
	  prob->messageHandler()->message(COIN_PRESOLVE_UNBOUND,
					     messages)
					       <<CoinMessageEol;
    else
	  prob->messageHandler()->message(COIN_PRESOLVE_INFEASUNBOUND,
					     messages)
					       <<CoinMessageEol;
    // get rid of data
    gutsOfDestroy();
  }
  return (paction_);
}