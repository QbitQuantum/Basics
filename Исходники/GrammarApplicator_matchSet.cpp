/**
 * Tests whether a given reading matches a given tag.
 *
 * In the https://visl.sdu.dk/cg3_performance.html test data, this function is executed 1058428 times,
 * of which 827259 are treated as raw tags.
 *
 * @param[in] reading The reading to test
 * @param[in] tag The tag to test against
 * @param[in] unif_mode Used to signal that a parent set was a $$unified set
 */
uint32_t GrammarApplicator::doesTagMatchReading(const Reading& reading, const Tag& tag, bool unif_mode, bool bypass_index) {
	uint32_t retval = 0;
	uint32_t match = 0;

	if (!(tag.type & T_SPECIAL) || tag.type & T_FAILFAST) {
		uint32SortedVector::const_iterator itf, ite = reading.tags_plain.end();
		bool raw_in = reading.tags_plain_bloom.matches(tag.hash);
		if (tag.type & T_FAILFAST) {
			itf = reading.tags_plain.find(tag.plain_hash);
			raw_in = (itf != ite);
		}
		else if (raw_in) {
			itf = reading.tags_plain.find(tag.hash);
			raw_in = (itf != ite);
		}
		if (raw_in) {
			match = tag.hash;
		}
	}
	else if (tag.type & T_SET) {
		uint32_t sh = hash_value(tag.tag);
		sh = grammar->sets_by_name.find(sh)->second;
		match = doesSetMatchReading(reading, sh, bypass_index, unif_mode);
	}
	else if (tag.type & T_VARSTRING) {
		const Tag* nt = generateVarstringTag(&tag);
		match = doesTagMatchReading(reading, *nt, unif_mode, bypass_index);
	}
	else if (tag.type & T_META) {
		if (tag.regexp && !reading.parent->text.empty()) {
			UErrorCode status = U_ZERO_ERROR;
			uregex_setText(tag.regexp, reading.parent->text.c_str(), static_cast<int32_t>(reading.parent->text.size()), &status);
			if (status != U_ZERO_ERROR) {
				u_fprintf(ux_stderr, "Error: uregex_setText(MatchSet) returned %s for tag %S before input line %u - cannot continue!\n", u_errorName(status), tag.tag.c_str(), numLines);
				CG3Quit(1);
			}
			status = U_ZERO_ERROR;
			if (uregex_find(tag.regexp, -1, &status)) {
				match = tag.hash;
			}
			if (status != U_ZERO_ERROR) {
				u_fprintf(ux_stderr, "Error: uregex_find(MatchSet) returned %s for tag %S before input line %u - cannot continue!\n", u_errorName(status), tag.tag.c_str(), numLines);
				CG3Quit(1);
			}
			if (match) {
				int32_t gc = uregex_groupCount(tag.regexp, &status);
				if (gc > 0 && regexgrps.second != 0) {
					UChar tmp[1024];
					for (int i = 1; i <= gc; ++i) {
						tmp[0] = 0;
						int32_t len = uregex_group(tag.regexp, i, tmp, 1024, &status);
						regexgrps.second->resize(std::max(static_cast<size_t>(regexgrps.first) + 1, regexgrps.second->size()));
						UnicodeString& ucstr = (*regexgrps.second)[regexgrps.first];
						ucstr.remove();
						ucstr.append(tmp, len);
						++regexgrps.first;
					}
				}
			}
		}
	}
	else if (tag.regexp) {
		match = doesRegexpMatchReading(reading, tag, bypass_index);
	}
	else if (tag.type & T_CASE_INSENSITIVE) {
		for (auto mter : reading.tags_textual) {
			match = doesTagMatchIcase(mter, tag, bypass_index);
			if (match) {
				break;
			}
		}
	}
	else if (tag.type & T_REGEXP_ANY) {
		if (tag.type & T_BASEFORM) {
			match = reading.baseform;
			if (unif_mode) {
				if (unif_last_baseform) {
					if (unif_last_baseform != reading.baseform) {
						match = 0;
					}
				}
				else {
					unif_last_baseform = reading.baseform;
				}
			}
		}
		else if (tag.type & T_WORDFORM) {
			match = reading.parent->wordform->hash;
			if (unif_mode) {
				if (unif_last_wordform) {
					if (unif_last_wordform != reading.parent->wordform->hash) {
						match = 0;
					}
				}
				else {
					unif_last_wordform = reading.parent->wordform->hash;
				}
			}
		}
		else {
			for (auto mter : reading.tags_textual) {
				const Tag& itag = *(single_tags.find(mter)->second);
				if (!(itag.type & (T_BASEFORM | T_WORDFORM))) {
					match = itag.hash;
					if (unif_mode) {
						if (unif_last_textual) {
							if (unif_last_textual != mter) {
								match = 0;
							}
						}
						else {
							unif_last_textual = mter;
						}
					}
				}
				if (match) {
					break;
				}
			}
		}
	}
	else if (tag.type & T_NUMERICAL) {
		for (auto mter : reading.tags_numerical) {
			const Tag& itag = *(mter.second);
			double compval = tag.comparison_val;
			if (compval <= NUMERIC_MIN) {
				compval = reading.parent->getMin(tag.comparison_hash);
			}
			else if (compval >= NUMERIC_MAX) {
				compval = reading.parent->getMax(tag.comparison_hash);
			}
			if (tag.comparison_hash == itag.comparison_hash) {
				if (tag.comparison_op == OP_EQUALS && itag.comparison_op == OP_EQUALS && compval == itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_NOTEQUALS && itag.comparison_op == OP_EQUALS && compval != itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_EQUALS && itag.comparison_op == OP_NOTEQUALS && compval != itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_NOTEQUALS && itag.comparison_op == OP_NOTEQUALS && compval == itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_EQUALS && itag.comparison_op == OP_LESSTHAN && compval < itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_EQUALS && itag.comparison_op == OP_LESSEQUALS && compval <= itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_EQUALS && itag.comparison_op == OP_GREATERTHAN && compval > itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_EQUALS && itag.comparison_op == OP_GREATEREQUALS && compval >= itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_NOTEQUALS && itag.comparison_op == OP_LESSTHAN) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_NOTEQUALS && itag.comparison_op == OP_LESSEQUALS) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_NOTEQUALS && itag.comparison_op == OP_GREATERTHAN) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_NOTEQUALS && itag.comparison_op == OP_GREATEREQUALS) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSTHAN && itag.comparison_op == OP_NOTEQUALS) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSEQUALS && itag.comparison_op == OP_NOTEQUALS) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATERTHAN && itag.comparison_op == OP_NOTEQUALS) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATEREQUALS && itag.comparison_op == OP_NOTEQUALS) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSTHAN && itag.comparison_op == OP_EQUALS && compval > itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSEQUALS && itag.comparison_op == OP_EQUALS && compval >= itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSTHAN && itag.comparison_op == OP_LESSTHAN) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSEQUALS && itag.comparison_op == OP_LESSEQUALS) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSEQUALS && itag.comparison_op == OP_LESSTHAN) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSTHAN && itag.comparison_op == OP_LESSEQUALS) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSTHAN && itag.comparison_op == OP_GREATERTHAN && compval > itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSTHAN && itag.comparison_op == OP_GREATEREQUALS && compval > itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSEQUALS && itag.comparison_op == OP_GREATERTHAN && compval > itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_LESSEQUALS && itag.comparison_op == OP_GREATEREQUALS && compval >= itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATERTHAN && itag.comparison_op == OP_EQUALS && compval < itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATEREQUALS && itag.comparison_op == OP_EQUALS && compval <= itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATERTHAN && itag.comparison_op == OP_GREATERTHAN) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATEREQUALS && itag.comparison_op == OP_GREATEREQUALS) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATEREQUALS && itag.comparison_op == OP_GREATERTHAN) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATERTHAN && itag.comparison_op == OP_GREATEREQUALS) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATERTHAN && itag.comparison_op == OP_LESSTHAN && compval < itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATERTHAN && itag.comparison_op == OP_LESSEQUALS && compval < itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATEREQUALS && itag.comparison_op == OP_LESSTHAN && compval < itag.comparison_val) {
					match = itag.hash;
				}
				else if (tag.comparison_op == OP_GREATEREQUALS && itag.comparison_op == OP_LESSEQUALS && compval <= itag.comparison_val) {
					match = itag.hash;
				}
				if (match) {
					break;
				}
			}
		}
	}
	else if (tag.type & T_VARIABLE) {
		if (variables.find(tag.comparison_hash) == variables.end()) {
			//u_fprintf(ux_stderr, "Info: %S failed.\n", tag.tag.c_str());
			match = 0;
		}
		else {
			//u_fprintf(ux_stderr, "Info: %S matched.\n", tag.tag.c_str());
			match = tag.hash;
		}
	}
	else if (tag.type & T_PAR_LEFT) {
		if (par_left_tag && reading.parent->local_number == par_left_pos && reading.tags.find(par_left_tag) != reading.tags.end()) {
			match = grammar->tag_any;
		}
	}
	else if (tag.type & T_PAR_RIGHT) {
		if (par_right_tag && reading.parent->local_number == par_right_pos && reading.tags.find(par_right_tag) != reading.tags.end()) {
			match = grammar->tag_any;
		}
	}
	else if (tag.type & T_ENCL) {
		if (!reading.parent->enclosed.empty()) {
			match = true;
		}
	}
	else if (tag.type & T_TARGET) {
		if (target && reading.parent == target) {
			match = grammar->tag_any;
		}
	}
	else if (tag.type & T_MARK) {
		if (mark && reading.parent == mark) {
			match = grammar->tag_any;
		}
	}
	else if (tag.type & T_ATTACHTO) {
		if (attach_to && reading.parent == attach_to) {
			match = grammar->tag_any;
		}
	}
	else if (tag.type & T_SAME_BASIC) {
		if (reading.hash_plain == same_basic) {
			match = grammar->tag_any;
		}
	}

	if (match) {
		++match_single;
		retval = match;
	}

	return retval;
}