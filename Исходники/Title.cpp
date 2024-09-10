// returns false and sets g_errno on error
bool Title::setTitle ( Xml *xml, Words *words, int32_t maxTitleLen, Query *query,
                       LinkInfo *linkInfo, Url *firstUrl, const char *filteredRootTitleBuf, int32_t filteredRootTitleBufSize,
                       uint8_t contentType, uint8_t langId, int32_t niceness ) {
	// make Msg20.cpp faster if it is just has
	// Msg20Request::m_setForLinkInfo set to true, no need to extricate a title.
	if ( maxTitleLen <= 0 ) {
		return true;
	}

	m_niceness = niceness;
	m_maxTitleLen = maxTitleLen;

	// if this is too big the "first line" algo can be huge!!!
	// and really slow everything way down with a huge title candidate
	int32_t maxTitleWords = 128;

	// assume no title
	reset();

	int32_t NW = words->getNumWords();

	//
	// now get all the candidates
	//

	// . allow up to 100 title CANDIDATES
	// . "as" is the word # of the first word in the candidate
	// . "bs" is the word # of the last word IN the candidate PLUS ONE
	int32_t n = 0;
	int32_t as[MAX_TIT_CANDIDATES];
	int32_t bs[MAX_TIT_CANDIDATES];
	float scores[MAX_TIT_CANDIDATES];
	Words *cptrs[MAX_TIT_CANDIDATES];
	int32_t types[MAX_TIT_CANDIDATES];
	int32_t parent[MAX_TIT_CANDIDATES];

	// record the scoring algos effects
	float  baseScore        [MAX_TIT_CANDIDATES];
	float  noCapsBoost      [MAX_TIT_CANDIDATES];
	float  qtermsBoost      [MAX_TIT_CANDIDATES];
	float  inCommonCandBoost[MAX_TIT_CANDIDATES];

	// reset these
	for ( int32_t i = 0 ; i < MAX_TIT_CANDIDATES ; i++ ) {
		// assume no parent
		parent[i] = -1;
	}

	// xml and words class for each link info, rss item
	Xml   tx[MAX_TIT_CANDIDATES];
	Words tw[MAX_TIT_CANDIDATES];
	int32_t  ti = 0;

	// restrict how many link texts and rss blobs we check for titles
	// because title recs like www.google.com have hundreds and can
	// really slow things down to like 50ms for title generation
	int32_t kcount = 0;
	int32_t rcount = 0;

	//int64_t x = gettimeofdayInMilliseconds();

	// . get every link text
	// . TODO: repeat for linkInfo2, the imported link text
	for ( Inlink *k = NULL; linkInfo && (k = linkInfo->getNextInlink(k)) ; ) {
		// breathe
		QUICKPOLL(m_niceness);
		// fast skip check for link text
		if ( k->size_linkText >= 3 && ++kcount >= 20 ) continue;
		// fast skip check for rss item
		if ( k->size_rssItem > 10 && ++rcount >= 20 ) continue;

		// set Url
		Url u;
		u.set( k->getUrl(), k->size_urlBuf );

		// is it the same host as us?
		bool sh = true;

		// skip if not from same host and should be
		if ( firstUrl->getHostLen() != u.getHostLen() ) {
			sh = false;
		}

		// skip if not from same host and should be
		if ( strncmp( firstUrl->getHost(), u.getHost(), u.getHostLen() ) ) {
			sh = false;
		}

		// get the link text
		if ( k->size_linkText >= 3 ) {
			char *p    = k->getLinkText();
			int32_t  plen = k->size_linkText - 1;
			if ( ! verifyUtf8 ( p , plen ) ) {
				log("title: set4 bad link text from url=%s", k->getUrl());
				continue;
			}

			// now the words.
			if ( !tw[ti].set( k->getLinkText(), k->size_linkText - 1, true, 0 ) ) {
				return false;
			}

			// set the bookends, it is the whole thing
			cptrs   [n] = &tw[ti];
			as      [n] = 0;
			bs      [n] = tw[ti].getNumWords();
			// score higher if same host
			if ( sh ) scores[n] = 1.05;
			// do not count so high if remote!
			else      scores[n] = 0.80;
			// set the type
			if ( sh ) types [n] = TT_LINKTEXTLOCAL;
			else      types [n] = TT_LINKTEXTREMOTE;
			// another candidate
			n++;
			// use xml and words
			ti++;
			// break out if too many already. save some for below.
			if ( n + 30 >= MAX_TIT_CANDIDATES ) break;
		}
		// get the rss item
		if ( k->size_rssItem <= 10 ) continue;
		// . returns false and sets g_errno on error
		// . use a 0 for niceness
		if ( ! k->setXmlFromRSS ( &tx[ti] , 0 ) ) return false;
		// get the word range
		int32_t tslen;
		bool isHtmlEnc;
		char *ts = tx[ti].getRSSTitle ( &tslen , &isHtmlEnc );
		// skip if not in the rss
		if ( ! ts ) continue;
		// skip if empty
		if ( tslen <= 0 ) continue;
		// now set words to that
		if ( !tw[ti].set( ts, tslen, true, 0 ) ) {
			return false;
		}

		// point to that
		cptrs   [n] = &tw[ti];
		as      [n] = 0;
		bs      [n] = tw[ti].getNumWords();
		// increment since we are using it
		ti++;
		// base score for rss title
		if ( sh ) scores[n] = 5.0;
		// if not same host, treat like link text
		else      scores[n] = 2.0;
		// set the type
		if ( sh ) types [n] = TT_RSSITEMLOCAL;
		else      types [n] = TT_RSSITEMREMOTE;
		// advance
		n++;
		// break out if too many already. save some for below.
		if ( n + 30 >= MAX_TIT_CANDIDATES ) break;
	}

	//logf(LOG_DEBUG,"title: took1=%" PRId64,gettimeofdayInMilliseconds()-x);
	//x = gettimeofdayInMilliseconds();

	// . set the flags array
	// . indicates what words are in title candidates already, but
	//   that is set below
	// . up here we set words that are not allowed to be in candidates,
	//   like words that are in a link that is not a self link
	// . alloc for it
	char *flags = NULL;
	char localBuf[10000];

	int32_t  need = words->getNumWords();
	if ( need <= 10000 ) {
		flags = (char *)localBuf;
	} else {
		flags = (char *)mmalloc(need,"TITLEflags");
	}

	if ( ! flags ) {
		return false;
	}

	// clear it
	memset ( flags , 0 , need );

	// check tags in body
	nodeid_t *tids = words->getTagIds();

	// scan to set link text flags
	// loop over all "words" in the html body
	char inLink   = false;
	char selfLink = false;
	for ( int32_t i = 0 ; i < NW ; i++ ) {
		// breathe
		QUICKPOLL(m_niceness);

		// if in a link that is not self link, cannot be in a candidate
		if ( inLink && ! selfLink ) {
			flags[i] |= 0x02;
		}

		// out of a link
		if ( tids[i] == (TAG_A | BACKBIT) ) {
			inLink = false;
		}

		// if not start of <a> tag, skip it
		if ( tids[i] != TAG_A ) {
			continue;
		}

		// flag it
		inLink = true;

		// get the node in the xml
		int32_t xn = words->getNodes()[i];

		// is it a self link?
		int32_t len;
		char *link = xml->getString(xn,"href",&len);

		// . set the url class to this
		// . TODO: use the base url in the doc
		Url u;
		u.set( link, len, true, false );

		// compare
		selfLink = u.equals ( firstUrl );

		// skip if not selfLink
		if ( ! selfLink ) {
			continue;
		}

		// if it is a selflink , check for an "onClick" tag in the
		// anchor tag to fix that Mixx issue for:
		// http://www.npr.org/templates/story/story.php?storyId=5417137

		int32_t  oclen;
		char *oc = xml->getString(xn,"onclick",&oclen);

		if ( ! oc ) {
			oc = xml->getString(xn,"onClick",&oclen);
		}

		// assume not a self link if we see that...
		if ( oc ) {
			selfLink = false;
		}

		// if this <a href> link has a "title" attribute, use that
		// instead! that thing is solid gold.
		int32_t  atlen;
		char *atitle = xml->getString(xn,"title",&atlen);

		// stop and use that, this thing is gold!
		if ( ! atitle || atlen <= 0 ) {
			continue;
		}

		// craziness? ignore it...
		if ( atlen > 400 ) {
			continue;
		}

		// if it contains permanent, permalink or share, ignore it!
		if ( strncasestr ( atitle, "permalink", atlen ) ||
		     strncasestr ( atitle,"permanent", atlen) ||
		     strncasestr ( atitle,"share", atlen) ) {
			continue;
		}

		// do not count the link text as viable
		selfLink = false;

		// aw, dammit
		if ( ti >= MAX_TIT_CANDIDATES ) {
			continue;
		}

		// other dammit
		if ( n >= MAX_TIT_CANDIDATES ) {
			break;
		}

		// ok, process it
		if ( ! tw[ti].set ( atitle, atlen, true, 0 )) {
			return false;
		}

		// set the bookends, it is the whole thing
		cptrs   [n] = &tw[ti];
		as      [n] = 0;
		bs      [n] = tw[ti].getNumWords();
		scores  [n] = 3.0; // not ALWAYS solid gold!
		types   [n] = TT_TITLEATT;

		// we are using the words class
		ti++;

		// advance
		n++;

		// break out if too many already. save some for below.
		if ( n + 20 >= MAX_TIT_CANDIDATES ) {
			break;
		}
	}

	//logf(LOG_DEBUG,"title: took2=%" PRId64,gettimeofdayInMilliseconds()-x);
	//x = gettimeofdayInMilliseconds();

	//int64_t *wids = WW->getWordIds();
	// . find the last positive scoring guy
	// . do not consider title candidates after "r" if "r" is non-zero
	// . FIXES http://larvatusprodeo.net/2009/01/07/partisanship-politics-and-participation/

	// the candidate # of the title tag
	int32_t tti = -1;

	// allow up to 4 tags from each type
	char table[512];

	// sanity check
	if ( getNumXmlNodes() > 512 ) { g_process.shutdownAbort(true); }

	// clear table counts
	memset ( table , 0 , 512 );

	// the first word
	char *wstart = NULL;
	if ( NW > 0 ) {
		wstart = words->getWord(0);
	}

	// loop over all "words" in the html body
	for ( int32_t i = 0 ; i < NW ; i++ ) {
		// come back up here if we encounter another "title-ish" tag
		// within our first alleged "title-ish" tag
	subloop:
		// stop after 30k of text
		if ( words->getWord(i) - wstart > 200000 ) {
			break; // 1106
		}

		// get the tag id minus the back tag bit
		nodeid_t tid = tids[i] & BACKBITCOMP;


		// pen up and pen down for these comment like tags
		if ( tid == TAG_SCRIPT || tid == TAG_STYLE ) {
			// ignore "titles" in script or style tags
			if ( ! (tids[i] & BACKBIT) ) {
				continue;
			}
		}

		/// @todo ALC we should allow more tags than just link
		// skip if not a good tag. we're already checking for title tag in Title::setTitleFromTags
		if (tid != TAG_A) {
			continue;
		}

		// must NOT be a back tag
		if ( tids[i] & BACKBIT ) {
			continue;
		}

		// skip if we hit our limit
		if ( table[tid] >= 4 ) {
			continue;
		}

		// skip over tag/word #i
		i++;

		// no words in links, unless it is a self link
		if ( i < NW && (flags[i] & 0x02) ) {
			continue;
		}

		// the start should be here
		int32_t start = -1;

		// do not go too far
		int32_t max = i + 200;

		// find the corresponding back tag for it
		for (  ; i < NW && i < max ; i++ ) {
			// hey we got it, BUT we got no alnum word first
			// so the thing was empty, so loop back to subloop
			if ( (tids[i] & BACKBITCOMP) == tid  &&   
			     (tids[i] & BACKBIT    ) && 
			     start == -1 ) {
				goto subloop;
			}

			// if we hit another title-ish tag, loop back up
			if ( (tids[i] & BACKBITCOMP) == TAG_TITLE || (tids[i] & BACKBITCOMP) == TAG_A ) {
				// if no alnum text, restart at the top
				if ( start == -1 ) {
					goto subloop;
				}

				// otherwise, break out and see if title works
				break;
			}

			// if we hit a breaking tag...
			if ( isBreakingTagId ( tids[i] & BACKBITCOMP ) &&
			     // do not consider <span> tags breaking for 
			     // our purposes. i saw a <h1><span> setup before.
			     tids[i] != TAG_SPAN ) {
				break;
			}

			// skip if not alnum word
			if ( ! words->isAlnum(i) ) {
				continue;
			}

			// if we hit an alnum word, break out
			if ( start == -1 ) {
				start = i;
			}
		}

		// if no start was found, must have had a 0 score in there
		if ( start == -1 ) {
			continue;
		}

		// if we exhausted the doc, we are done
		if ( i >= NW ) {
			break;
		}

		// skip if way too big!
		if ( i >= max ) {
			continue;
		}

		// if was too long do not consider a title
		if ( i - start > 300 ) {
			continue;
		}

		// . skip if too many bytes
		// . this does not include the length of word #i, but #(i-1)
		if ( words->getStringSize ( start , i ) > 1000 ) {
			continue;
		}

		// count it
		table[tid]++;

		// max it out if we are positive scoring. stop after the
		// first positive scoring guy in a section. this might
		// hurt the "Hamlet" thing though...

		// store a point to the title tag guy. Msg20.cpp needs this
		// because the zak's proximity algo uses it in Summary.cpp
		// and in Msg20.cpp

		// only get the first one! often the 2nd on is in an iframe!! which we now expand into here.
		if ( tid == TAG_TITLE && m_titleTagStart == -1 ) {
			m_titleTagStart = start;
			m_titleTagEnd   = i;

			// save the candidate # because we always use this
			// as the title if we are a root
			if ( tti < 0 ) {
				tti = n;
			}
		}

		// point to words class of the body that was passed in to us
		cptrs[n] = words;
		as[n] = start;
		bs[n] = i;
		if ( tid == TAG_B ) {
			types[n] = TT_BOLDTAG;
			scores[n] = 1.0;
		} else if ( tid == TAG_H1 ) {
			types[n] = TT_HTAG;
			scores[n] = 1.8;
		} else if ( tid == TAG_H2 ) {
			types[n] = TT_HTAG;
			scores[n] = 1.7;
		} else if ( tid == TAG_H3 ) {
			types[n] = TT_HTAG;
			scores[n] = 1.6;
		} else if ( tid == TAG_TITLE ) {
			types[n] = TT_TITLETAG;
			scores[n] = 3.0;
		} else if ( tid == TAG_DIV ) {
			types[n] = TT_DIVTAG;
			scores[n] = 1.0;
		} else if ( tid == TAG_TD ) {
			types[n] = TT_TDTAG;
			scores[n] = 1.0;
		} else if ( tid == TAG_P ) {
			types[n] = TT_PTAG;
			scores[n] = 1.0;
		} else if ( tid == TAG_FONT ) {
			types[n] = TT_FONTTAG;
			scores[n] = 1.0;
		} else if ( tid == TAG_A ) {
			types[n] = TT_ATAG;
			// . self link is very powerful BUT
			//   http://www.npr.org/templates/story/story.php?storyId=5417137
			//   doesn't use it right! so use
			//   1.3 instead of 3.0. that has an "onClick" thing in the
			//   <a> tag, so check for that!
			// this was bad for
			// http://www.spiritualwoman.net/?cat=191
			// so i am demoting from 3.0 to 1.5
			scores[n] = 1.5;
		}

		// count it
		n++;

		// start loop over at tag #i, for loop does an i++, so negate
		// that so this will work
		i--;

		// break out if too many already. save some for below.
		if ( n + 10 >= MAX_TIT_CANDIDATES ) {
			break;
		}
	}

	//logf(LOG_DEBUG,"title: took3=%" PRId64,gettimeofdayInMilliseconds()-x);
	//x = gettimeofdayInMilliseconds();

	// to handle text documents, throw in the first line of text
	// as a title candidate, just make the score really low
	bool textDoc = (contentType == CT_UNKNOWN || contentType == CT_TEXT);

	if (textDoc) {
		// make "i" point to first alphabetical word in the document
		int32_t i ;

		for ( i = 0 ; i < NW && !words->isAlpha(i) ; i++);

		// if we got a first alphabetical word, then assume that to be the start of our title
		if ( i < NW && n < MAX_TIT_CANDIDATES ) {
			// first word in title is "t0"
			int32_t t0 = i;
			// find end of first line
			int32_t numWords = 0;

			// set i to the end now. we MUST find a \n to terminate the
			// title, otherwise we will not have a valid title
			while (i < NW && numWords < maxTitleWords && (words->isAlnum(i) || !words->hasChar(i, '\n'))) {
				if(words->isAlnum(i)) {
					numWords++;
				}

				++i;
			}

			// "t1" is the end
			int32_t t1 = -1;

			// we must have found our \n in order to set "t1"
			if (i <= NW && numWords < maxTitleWords ) {
				t1 = i;
			}

			// set the ptrs
			cptrs   [n] =  words;

			// this is the last resort i guess...
			scores  [n] =  0.5;
			types   [n] =  TT_FIRSTLINE;
			as      [n] =  t0;
			bs      [n] =  t1;

			// add it as a candidate if t0 and t1 were valid
			if (t0 >= 0 && t1 > t0) {
				n++;
			}
		}
	}

	//logf(LOG_DEBUG,"title: took4=%" PRId64,gettimeofdayInMilliseconds()-x);
	//x = gettimeofdayInMilliseconds();

	{
		// now add the last url path to contain underscores or hyphens
		char *pstart = firstUrl->getPath();

		// get first url
		Url *fu = firstUrl;

		// start at the end
		char *p = fu->getUrl() + fu->getUrlLen();

		// end pointer
		char *pend = NULL;

		// come up here for each path component
		while ( p >= pstart ) {
			// save end
			pend = p;

			// skip over /
			if ( *p == '/' ) {
				p--;
			}

			// now go back to next /
			int32_t count = 0;
			for ( ; p >= pstart && *p !='/' ; p-- ) {
				if ( *p == '_' || *p == '-' ) {
					count++;
				}
			}

			// did we get it?
			if ( count > 0 ) {
				break;
			}
		}

		// did we get any?
		if ( p > pstart && n < MAX_TIT_CANDIDATES ) {
			// now set words to that
			if ( ! tw[ti].set ( p, (pend - p), true, 0 )) {
				return false;
			}

			// point to that
			cptrs   [n] = &tw[ti];
			as      [n] = 0;
			bs      [n] = tw[ti].getNumWords();
			scores  [n] = 1.0;
			types   [n] = TT_URLPATH;

			// increment since we are using it
			ti++;

			// advance
			n++;
		}
	}

	// save old n
	int32_t oldn = n;

	// . do not split titles if we are a root url maps.yahoo.com was getting "Maps" for the title
	if ( firstUrl->isRoot() ) {
		oldn = -2;
	}

	// point to list of \0 separated titles
	const char *rootTitleBuf    = NULL;
	const char *rootTitleBufEnd = NULL;

	// get the root title if we are not root!
	if (filteredRootTitleBuf) {
#ifdef _VALGRIND_
		VALGRIND_CHECK_MEM_IS_DEFINED(filteredRootTitleBuf,filteredRootTitleBufSize);
#endif
		// point to list of \0 separated titles
		rootTitleBuf    = filteredRootTitleBuf;
		rootTitleBufEnd =  filteredRootTitleBuf + filteredRootTitleBufSize;
	}

	{
		// convert into an array
		int32_t nr = 0;
		const char *pr = rootTitleBuf;
		const char *rootTitles[20];
		int32_t  rootTitleLens[20];

		// loop over each root title segment
		for ( ; pr && pr < rootTitleBufEnd ; pr += strnlen(pr,rootTitleBufEnd-pr) + 1 ) {
			// if we had a query...
			if ( query ) {
				Matches m;

				m.setQuery ( query );

				// see if root title segment has query terms in it
				m.addMatches ( const_cast<char*>(pr), strnlen(pr,rootTitleBufEnd-pr), MF_TITLEGEN, m_niceness );

				// if matches query, do NOT add it, we only add it for
				// removing from the title of the page...
				if ( m.getNumMatches() ) {
					continue;
				}
			}
			// point to it. it should start with an alnum already
			// since it is the "filtered" list of root titles...
			// if not, fix it in xmldoc then.
			rootTitles   [nr] = pr;
			rootTitleLens[nr] = strlen(pr);
			// advance
			nr++;
			// no breaching
			if ( nr >= 20 ) break;
		}

		// now split up candidates in children candidates by tokenizing
		// using :, | and - as delimters.
		// the hyphen must have a space on at least one side, so "cd-rom" does
		// not create a pair of tokens...
		// FIX: for the title:
		// Best Careers 2009: Librarian - US News and World Report
		// we need to recognize "Best Careers 2009: Librarian" as a subtitle
		// otherwise we don't get it as the title. so my question is are we
		// going to have to do all the permutations at some point? for now
		// let's just add in pairs...
		for ( int32_t i = 0 ; i < oldn && n + 3 < MAX_TIT_CANDIDATES ; i++ ) {
			// stop if no root title segments
			if ( nr <= 0 ) break;
			// get the word info
			Words *w = cptrs[i];
			int32_t   a = as[i];
			int32_t   b = bs[i];
			// init
			int32_t lasta = a;
			char prev  = false;
			// char length in bytes
			//int32_t charlen = 1;
			// see how many we add
			int32_t added = 0;
			char *skipTo = NULL;
			bool qualified = true;
			// . scan the words looking for a token
			// . sometimes the candidates end in ": " so put in "k < b-1"
			// . made this from k<b-1 to k<b to fix
			//   "Hot Tub Time Machine (2010) - IMDb" to strip IMDb
			for ( int32_t k = a ; k < b && n + 3 < MAX_TIT_CANDIDATES; k++){
				// get word
				char *wp = w->getWord(k);
				// skip if not alnum
				if ( ! w->isAlnum(k) ) {
					// in order for next alnum word to
					// qualify for "clipping" if it matches
					// the root title, there has to be more
					// than just spaces here, some punct.
					// otherwise title
					// "T. D. Jakes: Biography from Answers.com"
					// becomes
					// "T. D. Jakes: Biography from"
					qualified=isWordQualified(wp,w->getWordLen(k));
					continue;
				}
				// gotta be qualified!
				if ( ! qualified ) continue;
				// skip if in root title
				if ( skipTo && wp < skipTo ) continue;
				// does this match any root page title segments?
				int32_t j;
				for ( j = 0 ; j < nr ; j++ ) {
					// . compare to root title
					// . break out if we matched!
					if ( ! strncmp( wp, rootTitles[j], rootTitleLens[j] ) ) {
						break;
					}
				}

				// if we did not match a root title segment,
				// keep on chugging
				if ( j >= nr ) continue;
				// . we got a root title match!
				// . skip over
				skipTo = wp + rootTitleLens[j];
				// must land on qualified punct then!!
				int32_t e = k+1;
				for ( ; e<b && w->getWord(e)<skipTo ; e++ );
				// ok, word #e must be a qualified punct
				if ( e<b &&
				     ! isWordQualified(w->getWord(e),w->getWordLen(e)))
					// assume no match then!!
					continue;
				// if we had a previous guy, reset the end of the
				// previous candidate
				if ( prev ) {
					bs[n-2] = k;
					bs[n-1] = k;
				}
				// . ok, we got two more candidates
				// . well, only one more if this is not the 1st time
				if ( ! prev ) {
					cptrs   [n] = cptrs   [i];
					scores  [n] = scores  [i];
					types   [n] = types   [i];
					as      [n] = lasta;
					bs      [n] = k;
					parent  [n] = i;
					n++;
					added++;
				}
				// the 2nd one
				cptrs   [n] = cptrs   [i];
				scores  [n] = scores  [i];
				types   [n] = types   [i];
				as      [n] = e + 1;
				bs      [n] = bs      [i];
				parent  [n] = i;
				n++;
				added++;

				// now add in the last pair as a whole token
				cptrs   [n] = cptrs   [i];
				scores  [n] = scores  [i];
				types   [n] = types   [i];
				as      [n] = lasta;
				bs      [n] = bs      [i];
				parent  [n] = i;
				n++;
				added++;

				// nuke the current candidate then since it got
				// split up to not contain the root title...
				//cptrs[i] = NULL;

				// update this
				lasta = k+1;

				// if we encounter another delimeter we will have to revise bs[n-1], so note that
				prev = true;
			}

			// nuke the current candidate then since it got
			// split up to not contain the root title...
			if ( added ) {
				scores[i] = 0.001;
				//cptrs[i] = NULL;
			}

			// erase the pair if that there was only one token
			if ( added == 3 ) n--;
		}
	}

	for ( int32_t i = 0 ; i < n ; i++ ) baseScore[i] = scores[i];
	
	//
	// . now punish by 0.85 for every lower case non-stop word it has
	// . reward by 1.1 if has a non-stopword in the query
	//
	for ( int32_t i = 0 ; i < n ; i++ ) {
		// point to the words
		Words *w = cptrs[i];

		// skip if got nuked above
		if ( ! w ) {
			continue;
		}

		// the word ptrs
		char **wptrs = w->getWordPtrs();

		// skip if empty
		if ( w->getNumWords() <= 0 ) {
			continue;
		}

		// get the word boundaries
		int32_t a = as[i];
		int32_t b = bs[i];

		// record the boosts
		float ncb = 1.0;
		float qtb = 1.0;

		// a flag
		char uncapped = false;

		// scan the words in this title candidate
		for ( int32_t j = a ; j < b ; j++ ) {
			// skip stop words
			if ( w->isQueryStopWord( j, langId ) ) {
				continue;
			}

			// punish if uncapitalized non-stopword
			if ( ! w->isCapitalized(j) ) {
				uncapped = true;
			}

			// skip if no query
			if ( ! query ) {
				continue;
			}

			int64_t wid = w->getWordId(j);

			// reward if in the query
			if ( query->getWordNum(wid) >= 0 ) {
				qtb       *= 1.5;
				scores[i] *= 1.5;
			}
		}

		// . only punish once if missing a capitalized word hurts us for:
		//   http://content-uk.cricinfo.com/ausvrsa2008_09/engine/current/match/351682.html
		if ( uncapped ) {
			ncb *= 1.00;
			scores[i] *= 1.00;
		}

		// punish if a http:// title thingy
		char *s = wptrs[a];
		int32_t size = w->getStringSize(a,b);
		if ( size > 9 && memcmp("http://", s, 7) == 0 ) {
			ncb *= .10;
		}
		if ( size > 14 && memcmp("h\0t\0t\0p\0:\0/\0/", s, 14) == 0 ) {
			ncb *= .10;
		}

		// set these guys
		scores[i] *= ncb;

		noCapsBoost[i]  = ncb;
		qtermsBoost[i]  = qtb;
	}

	// . now compare each candidate to the other candidates
	// . give a boost if matches
	for ( int32_t i = 0 ; i < n ; i++ ) {
		// point to the words
		Words *w1 = cptrs[i];

		// skip if got nuked above
		if ( ! w1 ) {
			continue;
		}

		int32_t a1 = as[i];
		int32_t b1 = bs[i];

		// reset some flags
		char localFlag1 = 0;
		char localFlag2 = 0;

		// record the boost
		float iccb = 1.0;

		// total boost
		float total = 1.0;

		// to each other candidate
		for ( int32_t j = 0 ; j < n ; j++ ) {
			// not to ourselves
			if ( j == i ) {
				continue;
			}

			// or our derivatives
			if ( parent[j] == i ) {
				continue;
			}

			// or derivates to their parent
			if ( parent[i] == j ) {
				continue;
			}

			// only check parents now. do not check kids.
			// this was only for when doing percent contained
			// not getSimilarity() per se
			//if ( parent[j] != -1 ) continue;

			// TODO: do not accumulate boosts from a parent
			// and its kids, subtitles...
			//
			// do not compare type X to type Y
			if ( types[i] == TT_TITLETAG ) {
				if ( types[j] == TT_TITLETAG ) {
					continue;
				}
			}

			// do not compare a div candidate to another div cand
			// http://friendfeed.com/foxiewire?start=30
			// likewise, a TD to another TD
			// http://content-uk.cricinfo.com/ausvrsa2008_09/engine/match/351681.html
			// ... etc.
			if ( types[i] == TT_BOLDTAG ||
			     types[i] == TT_HTAG    ||
			     types[i] == TT_DIVTAG  ||
			     types[i] == TT_TDTAG   ||
			     types[i] == TT_FONTTAG    ) {
				if ( types[j] == types[i] ) continue;
			}
			// . do not compare one kid to another kid
			// . i.e. if we got "x | y" as a title and "x | z"
			//   as a link text, it will emphasize "x" too much
			//   http://content-uk.cricinfo.com/ausvrsa2008_09/engine/current/match/351682.html
			if ( parent[j] != -1 && parent[i] != -1 ) continue;

			// . body type tags are mostly mutually exclusive
			// . for the legacy.com url mentioned below, we have
			//   good stuff in <td> tags, so this hurts us...
			// . but for the sake of 
			//   http://larvatusprodeo.net/2009/01/07/partisanship-politics-and-participation/
			//   i put bold tags back

			if ( types[i] == TT_LINKTEXTLOCAL ) {
				if ( types[j] == TT_LINKTEXTLOCAL ) continue;
			}
			if ( types[i] == TT_RSSITEMLOCAL ) {
				if ( types[j] == TT_RSSITEMLOCAL ) continue;
			}

			// only compare to one local link text for each i
			if ( types[j] == TT_LINKTEXTLOCAL && localFlag1 ) {
				continue;
			}
			if ( types[j] == TT_RSSITEMLOCAL  && localFlag2 ) {
				continue;
			}
			if ( types[j] == TT_LINKTEXTLOCAL ) {
				localFlag1 = 1;
			}
			if ( types[j] == TT_RSSITEMLOCAL  ) {
				localFlag2 = 1;
			}

			// not link title attr to link title attr either
			// fixes http://www.spiritualwoman.net/?cat=191
			if ( types[i] == TT_TITLEATT &&
			     types[j] == TT_TITLEATT )
				continue;

			// get our words
			Words *w2 = cptrs[j];

			// skip if got nuked above
			if ( ! w2 ) continue;
			int32_t   a2 = as   [j];
			int32_t   b2 = bs   [j];

			// how similar is title #i to title #j ?
			float fp = getSimilarity ( w2 , a2 , b2 , w1 , a1 , b1 );

			// error?
			if ( fp == -1.0 ) return false;

			// custom boosting...
			float boost = 1.0;
			if      ( fp >= .95 ) boost = 3.0;
			else if ( fp >= .90 ) boost = 2.0;
			else if ( fp >= .85 ) boost = 1.5;
			else if ( fp >= .80 ) boost = 1.4;
			else if ( fp >= .75 ) boost = 1.3;
			else if ( fp >= .70 ) boost = 1.2;
			else if ( fp >= .60 ) boost = 1.1;
			else if ( fp >= .50 ) boost = 1.08;
			else if ( fp >= .40 ) boost = 1.04;

			// limit total
			total *= boost;
			if ( total > 100.0 ) break;
			// if you are matching the url path, that is pretty 
			// good so give more!
			// actually, that would hurt:
			// http://michellemalkin.com/2008/12/29/gag-worthy/

			// custom boosting!
			if ( fp > 0.0 && g_conf.m_logDebugTitle )
				logf(LOG_DEBUG,"title: i=%" PRId32" j=%" PRId32" fp=%.02f "
				     "b=%.02f", i,j,fp,boost);
			// apply it
			scores[i] *= boost;

			iccb      *= boost;
		}

		inCommonCandBoost[i] = iccb;
	}

	//logf(LOG_DEBUG,"title: took7=%" PRId64,gettimeofdayInMilliseconds()-x);
	//x = gettimeofdayInMilliseconds();


	// loop over all n candidates
	for ( int32_t i = 0 ; i < n ; i++ ) {
		// skip if not in the document body
		if ( cptrs[i] != words ) continue;
		// point to the words
		int32_t       a1    = as   [i];
		int32_t       b1    = bs   [i];

		// . loop through this candidates words
		// . TODO: use memset here?
		for ( int32_t j = a1 ; j <= b1 && j < NW ; j++ ) {
			// flag it
			flags[j] |= 0x01;
		}
	}

	// free our stuff
	if ( flags!=localBuf ) {
		mfree (flags, need, "TITLEflags");
	}

	// now get the highest scoring candidate title
	float max    = -1.0;
	int32_t  winner = -1;
	for ( int32_t i = 0 ; i < n ; i++ ) {
		// skip if got nuked
		if ( ! cptrs[i] ) {
			continue;
		}

		if ( winner != -1 && scores[i] <= max ) {
			continue;
		}

		// url path's cannot be titles in and of themselves
		if ( types[i] == TT_URLPATH ) {
			continue;
		}

		// skip if empty basically, like if title was exact
		// copy of root, then the whole thing got nuked and
		// some empty string added, where a > b
		if ( as[i] >= bs[i] ) {
			continue;
		}

		// got one
		max = scores[i];

		// save it
		winner = i;
	}

	// if we are a root, always pick the title tag as the title
	if ( oldn == -2 && tti >= 0 ) {
		winner = tti;
	}

	// if no winner, all done. no title
	if ( winner == -1 ) {
		// last resort use file name
		if ((contentType == CT_PDF) && (firstUrl->getFilenameLen() != 0)) {
			Words w;
			w.set(firstUrl->getFilename(), firstUrl->getFilenameLen(), true);
			if (!copyTitle(&w, 0, w.getNumWords())) {
				return false;
			}
		}
		return true;
	}

	// point to the words class of the winner
	Words *w = cptrs[winner];
	// skip if got nuked above
	if ( ! w ) { g_process.shutdownAbort(true); }

	// need to make our own Pos class if title not from body
	Pos  tp;
	if ( w != words ) {
		// set "Scores" ptr to NULL. we assume all are positive scores
		if ( ! tp.set ( w ) ) {
			return false;
		}
	}

	// the string ranges from word #a up to and including word #b
	int32_t a = as[winner];
	int32_t b = bs[winner];
	// sanity check
	if ( a < 0 || b > w->getNumWords() ) { g_process.shutdownAbort(true); }

	// save the title
	if ( ! copyTitle(w, a, b) ) {
		return false;
	}

	/*
	// debug logging
	SafeBuf sb;
	SafeBuf *pbuf = &sb;

	log("title: candidates for %s",xd->getFirstUrl()->getUrl() );

	pbuf->safePrintf("<div stype=\"border:1px solid black\">");
	pbuf->safePrintf("<b>***Finding Title***</b><br>\n");

	pbuf->safePrintf("<table cellpadding=5 border=2><tr>"
			 "<td colspan=20><center><b>Title Generation</b>"
			 "</center></td>"
			 "</tr>\n<tr>"
			 "<td>#</td>"
			 "<td>type</td>"
			 "<td>parent</td>"
			 "<td>base score</td>"
			 "<td>format penalty</td>"
			 "<td>query term boost</td>"
			 "<td>candidate intersection boost</td>"
			 "<td>FINAL SCORE</td>"
			 "<td>title</td>"
			 "</tr>\n" );
			 

	// print out all candidates
	for ( int32_t i = 0 ; i < n ; i++ ) {
		char *ts = "unknown";
		if ( types[i] == TT_LINKTEXTLOCAL  ) ts = "local inlink text";
		if ( types[i] == TT_LINKTEXTREMOTE ) ts = "remote inlink text";
		if ( types[i] == TT_RSSITEMLOCAL   ) ts = "local rss title";
		if ( types[i] == TT_RSSITEMREMOTE  ) ts = "remote rss title";
		if ( types[i] == TT_BOLDTAG        ) ts = "bold tag";
		if ( types[i] == TT_HTAG           ) ts = "header tag";
		if ( types[i] == TT_TITLETAG       ) ts = "title tag";
		if ( types[i] == TT_FIRSTLINE      ) ts = "first line in text";
		if ( types[i] == TT_FONTTAG        ) ts = "font tag";
		if ( types[i] == TT_ATAG           ) ts = "anchor tag";
		if ( types[i] == TT_DIVTAG         ) ts = "div tag";
		if ( types[i] == TT_TDTAG          ) ts = "td tag";
		if ( types[i] == TT_PTAG           ) ts = "p tag";
		if ( types[i] == TT_URLPATH        ) ts = "url path";
		if ( types[i] == TT_TITLEATT       ) ts = "title attribute";
		// get the title
		pbuf->safePrintf(
				 "<tr>"
				 "<td>#%" PRId32"</td>"
				 "<td><nobr>%s</nobr></td>"
				 "<td>%" PRId32"</td>"
				 "<td>%0.2f</td>" // baseScore
				 "<td>%0.2f</td>"
				 "<td>%0.2f</td>"
				 "<td>%0.2f</td>"
				 "<td>%0.2f</td>"
				 "<td>",
				 i,
				 ts ,
				 parent[i],
				 baseScore[i],
				 noCapsBoost[i],
				 qtermsBoost[i],
				 inCommonCandBoost[i],
				 scores[i]);
		// ptrs
		Words *w = cptrs[i];
		int32_t   a = as[i];
		int32_t   b = bs[i];
		// skip if no words
		if ( w->getNumWords() <= 0 ) continue;
		// the word ptrs
		char **wptrs = w->getWordPtrs();
		// string ptrs
		char *ptr  = wptrs[a];//w->getWord(a);
		int32_t  size = w->getStringSize(a,b);
		// it is utf8
		pbuf->safeMemcpy ( ptr , size );
		// end the line
		pbuf->safePrintf("</td></tr>\n");
	}

	pbuf->safePrintf("</table>\n<br>\n");

	// log these for now
	log("title: %s",sb.getBufStart());
	*/

	return true;

}