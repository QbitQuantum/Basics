void
cgen(Node *n, Node *nn)
{
	Node *l, *r, *t;
	Prog *p1;
	Node nod, nod1, nod2, nod3, nod4;
	int o, hardleft;
	long v, curs;
	vlong c;

	if(debug['g']) {
		prtree(nn, "cgen lhs");
		prtree(n, "cgen");
	}
	if(n == Z || n->type == T)
		return;
	if(typesu[n->type->etype]) {
		sugen(n, nn, n->type->width);
		return;
	}
	l = n->left;
	r = n->right;
	o = n->op;
	if(n->addable >= INDEXED) {
		if(nn == Z) {
			switch(o) {
			default:
				nullwarn(Z, Z);
				break;
			case OINDEX:
				nullwarn(l, r);
				break;
			}
			return;
		}
		gmove(n, nn);
		return;
	}
	curs = cursafe;

	if(l->complex >= FNX)
	if(r != Z && r->complex >= FNX)
	switch(o) {
	default:
		if(cond(o) && typesu[l->type->etype])
			break;

		regret(&nod, r);
		cgen(r, &nod);

		regsalloc(&nod1, r);
		gmove(&nod, &nod1);

		regfree(&nod);
		nod = *n;
		nod.right = &nod1;

		cgen(&nod, nn);
		return;

	case OFUNC:
	case OCOMMA:
	case OANDAND:
	case OOROR:
	case OCOND:
	case ODOT:
		break;
	}

	hardleft = l->addable < INDEXED || l->complex >= FNX;
	switch(o) {
	default:
		diag(n, "unknown op in cgen: %O", o);
		break;

	case ONEG:
	case OCOM:
		if(nn == Z) {
			nullwarn(l, Z);
			break;
		}
		regalloc(&nod, l, nn);
		cgen(l, &nod);
		gopcode(o, n->type, Z, &nod);
		gmove(&nod, nn);
		regfree(&nod);
		break;

	case OAS:
		if(l->op == OBIT)
			goto bitas;
		if(!hardleft) {
			if(nn != Z || r->addable < INDEXED || hardconst(r)) {
				if(r->complex >= FNX && nn == Z)
					regret(&nod, r);
				else
					regalloc(&nod, r, nn);
				cgen(r, &nod);
				gmove(&nod, l);
				if(nn != Z)
					gmove(&nod, nn);
				regfree(&nod);
			} else
				gmove(r, l);
			break;
		}
		if(l->complex >= r->complex) {
			if(l->op == OINDEX && immconst(r)) {
				gmove(r, l);
				break;
			}
			reglcgen(&nod1, l, Z);
			if(r->addable >= INDEXED && !hardconst(r)) {
				gmove(r, &nod1);
				if(nn != Z)
					gmove(r, nn);
				regfree(&nod1);
				break;
			}
			regalloc(&nod, r, nn);
			cgen(r, &nod);
		} else {
			regalloc(&nod, r, nn);
			cgen(r, &nod);
			reglcgen(&nod1, l, Z);
		}
		gmove(&nod, &nod1);
		regfree(&nod);
		regfree(&nod1);
		break;

	bitas:
		n = l->left;
		regalloc(&nod, r, nn);
		if(l->complex >= r->complex) {
			reglcgen(&nod1, n, Z);
			cgen(r, &nod);
		} else {
			cgen(r, &nod);
			reglcgen(&nod1, n, Z);
		}
		regalloc(&nod2, n, Z);
		gmove(&nod1, &nod2);
		bitstore(l, &nod, &nod1, &nod2, nn);
		break;

	case OBIT:
		if(nn == Z) {
			nullwarn(l, Z);
			break;
		}
		bitload(n, &nod, Z, Z, nn);
		gmove(&nod, nn);
		regfree(&nod);
		break;

	case OLSHR:
	case OASHL:
	case OASHR:
		if(nn == Z) {
			nullwarn(l, r);
			break;
		}
		if(r->op == OCONST) {
			if(r->vconst == 0) {
				cgen(l, nn);
				break;
			}
			regalloc(&nod, l, nn);
			cgen(l, &nod);
			if(o == OASHL && r->vconst == 1)
				gopcode(OADD, n->type, &nod, &nod);
			else
				gopcode(o, n->type, r, &nod);
			gmove(&nod, nn);
			regfree(&nod);
			break;
		}

		/*
		 * get nod to be D_CX
		 */
		if(nodreg(&nod, nn, D_CX)) {
			regsalloc(&nod1, n);
			gmove(&nod, &nod1);
			cgen(n, &nod);		/* probably a bug */
			gmove(&nod, nn);
			gmove(&nod1, &nod);
			break;
		}
		reg[D_CX]++;
		if(nn->op == OREGISTER && nn->reg == D_CX)
			regalloc(&nod1, l, Z);
		else
			regalloc(&nod1, l, nn);
		if(r->complex >= l->complex) {
			cgen(r, &nod);
			cgen(l, &nod1);
		} else {
			cgen(l, &nod1);
			cgen(r, &nod);
		}
		gopcode(o, n->type, &nod, &nod1);
		gmove(&nod1, nn);
		regfree(&nod);
		regfree(&nod1);
		break;

	case OADD:
	case OSUB:
	case OOR:
	case OXOR:
	case OAND:
		if(nn == Z) {
			nullwarn(l, r);
			break;
		}
		if(typefd[n->type->etype])
			goto fop;
		if(r->op == OCONST) {
			if(r->vconst == 0 && o != OAND) {
				cgen(l, nn);
				break;
			}
		}
		if(n->op == OADD && l->op == OASHL && l->right->op == OCONST
		&& (r->op != OCONST || r->vconst < -128 || r->vconst > 127)) {
			c = l->right->vconst;
			if(c > 0 && c <= 3) {
				if(l->left->complex >= r->complex) {
					regalloc(&nod, l->left, nn);
					cgen(l->left, &nod);
					if(r->addable < INDEXED) {
						regalloc(&nod1, r, Z);
						cgen(r, &nod1);
						genmuladd(&nod, &nod, 1 << c, &nod1);
						regfree(&nod1);
					}
					else
						genmuladd(&nod, &nod, 1 << c, r);
				}
				else {
					regalloc(&nod, r, nn);
					cgen(r, &nod);
					regalloc(&nod1, l->left, Z);
					cgen(l->left, &nod1);
					genmuladd(&nod, &nod1, 1 << c, &nod);
					regfree(&nod1);
				}
				gmove(&nod, nn);
				regfree(&nod);
				break;
			}
		}
		if(r->addable >= INDEXED && !hardconst(r)) {
			regalloc(&nod, l, nn);
			cgen(l, &nod);
			gopcode(o, n->type, r, &nod);
			gmove(&nod, nn);
			regfree(&nod);
			break;
		}
		if(l->complex >= r->complex) {
			regalloc(&nod, l, nn);
			cgen(l, &nod);
			regalloc(&nod1, r, Z);
			cgen(r, &nod1);
			gopcode(o, n->type, &nod1, &nod);
		} else {
			regalloc(&nod1, r, nn);
			cgen(r, &nod1);
			regalloc(&nod, l, Z);
			cgen(l, &nod);
			gopcode(o, n->type, &nod1, &nod);
		}
		gmove(&nod, nn);
		regfree(&nod);
		regfree(&nod1);
		break;

	case OLMOD:
	case OMOD:
	case OLMUL:
	case OLDIV:
	case OMUL:
	case ODIV:
		if(nn == Z) {
			nullwarn(l, r);
			break;
		}
		if(typefd[n->type->etype])
			goto fop;
		if(r->op == OCONST && typechl[n->type->etype]) {	/* TO DO */
			SET(v);
			switch(o) {
			case ODIV:
			case OMOD:
				c = r->vconst;
				if(c < 0)
					c = -c;
				v = log2(c);
				if(v < 0)
					break;
				/* fall thru */
			case OMUL:
			case OLMUL:
				regalloc(&nod, l, nn);
				cgen(l, &nod);
				switch(o) {
				case OMUL:
				case OLMUL:
					mulgen(n->type, r, &nod);
					break;
				case ODIV:
					sdiv2(r->vconst, v, l, &nod);
					break;
				case OMOD:
					smod2(r->vconst, v, l, &nod);
					break;
				}
				gmove(&nod, nn);
				regfree(&nod);
				goto done;
			case OLDIV:
				c = r->vconst;
				if((c & 0x80000000) == 0)
					break;
				regalloc(&nod1, l, Z);
				cgen(l, &nod1);
				regalloc(&nod, l, nn);
				zeroregm(&nod);
				gins(ACMPL, &nod1, nodconst(c));
				gins(ASBBL, nodconst(-1), &nod);
				regfree(&nod1);
				gmove(&nod, nn);
				regfree(&nod);
				goto done;
			}
		}

		if(o == OMUL) {
			if(l->addable >= INDEXED) {
				t = l;
				l = r;
				r = t;
			}
			/* should favour AX */
			regalloc(&nod, l, nn);
			cgen(l, &nod);
			if(r->addable < INDEXED || hardconst(r)) {
				regalloc(&nod1, r, Z);
				cgen(r, &nod1);
				gopcode(OMUL, n->type, &nod1, &nod);
				regfree(&nod1);
			}else
				gopcode(OMUL, n->type, r, &nod);	/* addressible */
			gmove(&nod, nn);
			regfree(&nod);
			break;
		}

		/*
		 * get nod to be D_AX
		 * get nod1 to be D_DX
		 */
		if(nodreg(&nod, nn, D_AX)) {
			regsalloc(&nod2, n);
			gmove(&nod, &nod2);
			v = reg[D_AX];
			reg[D_AX] = 0;

			if(isreg(l, D_AX)) {
				nod3 = *n;
				nod3.left = &nod2;
				cgen(&nod3, nn);
			} else
			if(isreg(r, D_AX)) {
				nod3 = *n;
				nod3.right = &nod2;
				cgen(&nod3, nn);
			} else
				cgen(n, nn);

			gmove(&nod2, &nod);
			reg[D_AX] = v;
			break;
		}
		if(nodreg(&nod1, nn, D_DX)) {
			regsalloc(&nod2, n);
			gmove(&nod1, &nod2);
			v = reg[D_DX];
			reg[D_DX] = 0;

			if(isreg(l, D_DX)) {
				nod3 = *n;
				nod3.left = &nod2;
				cgen(&nod3, nn);
			} else
			if(isreg(r, D_DX)) {
				nod3 = *n;
				nod3.right = &nod2;
				cgen(&nod3, nn);
			} else
				cgen(n, nn);

			gmove(&nod2, &nod1);
			reg[D_DX] = v;
			break;
		}
		reg[D_AX]++;

		if(r->op == OCONST && (o == ODIV || o == OLDIV) && immconst(r) && typechl[r->type->etype]) {
			reg[D_DX]++;
			if(l->addable < INDEXED) {
				regalloc(&nod2, l, Z);
				cgen(l, &nod2);
				l = &nod2;
			}
			if(o == ODIV)
				sdivgen(l, r, &nod, &nod1);
			else
				udivgen(l, r, &nod, &nod1);
			gmove(&nod1, nn);
			if(l == &nod2)
				regfree(l);
			goto freeaxdx;
		}

		if(l->complex >= r->complex) {
			cgen(l, &nod);
			reg[D_DX]++;
			if(o == ODIV || o == OMOD)
				gins(typechl[l->type->etype]? ACDQ: ACQO, Z, Z);
			if(o == OLDIV || o == OLMOD)
				zeroregm(&nod1);
			if(r->addable < INDEXED || r->op == OCONST) {
				regalloc(&nod3, r, Z);
				cgen(r, &nod3);
				gopcode(o, n->type, &nod3, Z);
				regfree(&nod3);
			} else
				gopcode(o, n->type, r, Z);
		} else {
			regsalloc(&nod3, r);
			cgen(r, &nod3);
			cgen(l, &nod);
			reg[D_DX]++;
			if(o == ODIV || o == OMOD)
				gins(typechl[l->type->etype]? ACDQ: ACQO, Z, Z);
			if(o == OLDIV || o == OLMOD)
				zeroregm(&nod1);
			gopcode(o, n->type, &nod3, Z);
		}
		if(o == OMOD || o == OLMOD)
			gmove(&nod1, nn);
		else
			gmove(&nod, nn);
	freeaxdx:
		regfree(&nod);
		regfree(&nod1);
		break;

	case OASLSHR:
	case OASASHL:
	case OASASHR:
		if(r->op == OCONST)
			goto asand;
		if(l->op == OBIT)
			goto asbitop;
		if(typefd[n->type->etype])
			goto asand;	/* can this happen? */

		/*
		 * get nod to be D_CX
		 */
		if(nodreg(&nod, nn, D_CX)) {
			regsalloc(&nod1, n);
			gmove(&nod, &nod1);
			cgen(n, &nod);
			if(nn != Z)
				gmove(&nod, nn);
			gmove(&nod1, &nod);
			break;
		}
		reg[D_CX]++;

		if(r->complex >= l->complex) {
			cgen(r, &nod);
			if(hardleft)
				reglcgen(&nod1, l, Z);
			else
				nod1 = *l;
		} else {
			if(hardleft)
				reglcgen(&nod1, l, Z);
			else
				nod1 = *l;
			cgen(r, &nod);
		}

		gopcode(o, l->type, &nod, &nod1);
		regfree(&nod);
		if(nn != Z)
			gmove(&nod1, nn);
		if(hardleft)
			regfree(&nod1);
		break;

	case OASAND:
	case OASADD:
	case OASSUB:
	case OASXOR:
	case OASOR:
	asand:
		if(l->op == OBIT)
			goto asbitop;
		if(typefd[l->type->etype] || typefd[r->type->etype])
			goto asfop;
		if(l->complex >= r->complex) {
			if(hardleft)
				reglcgen(&nod, l, Z);
			else
				nod = *l;
			if(!immconst(r)) {
				regalloc(&nod1, r, nn);
				cgen(r, &nod1);
				gopcode(o, l->type, &nod1, &nod);
				regfree(&nod1);
			} else
				gopcode(o, l->type, r, &nod);
		} else {
			regalloc(&nod1, r, nn);
			cgen(r, &nod1);
			if(hardleft)
				reglcgen(&nod, l, Z);
			else
				nod = *l;
			gopcode(o, l->type, &nod1, &nod);
			regfree(&nod1);
		}
		if(nn != Z)
			gmove(&nod, nn);
		if(hardleft)
			regfree(&nod);
		break;

	asfop:
		if(l->complex >= r->complex) {
			if(hardleft)
				reglcgen(&nod, l, Z);
			else
				nod = *l;
			if(r->addable < INDEXED){
				regalloc(&nod1, r, nn);
				cgen(r, &nod1);
			}else
				nod1 = *r;
			regalloc(&nod2, r, Z);
			gmove(&nod, &nod2);
			gopcode(o, r->type, &nod1, &nod2);
			gmove(&nod2, &nod);
			regfree(&nod2);
			if(r->addable < INDEXED)
				regfree(&nod1);
		} else {
			regalloc(&nod1, r, nn);
			cgen(r, &nod1);
			if(hardleft)
				reglcgen(&nod, l, Z);
			else
				nod = *l;
			if(o != OASMUL && o != OASADD) {
				regalloc(&nod2, r, Z);
				gmove(&nod, &nod2);
				gopcode(o, r->type, &nod1, &nod2);
				regfree(&nod1);
				gmove(&nod2, &nod);
				regfree(&nod2);
			} else {
				gopcode(o, r->type, &nod, &nod1);
				gmove(&nod1, &nod);
				regfree(&nod1);
			}
		}
		if(nn != Z)
			gmove(&nod, nn);
		if(hardleft)
			regfree(&nod);
		break;

	case OASLMUL:
	case OASLDIV:
	case OASLMOD:
	case OASMUL:
	case OASDIV:
	case OASMOD:
		if(l->op == OBIT)
			goto asbitop;
		if(typefd[n->type->etype] || typefd[r->type->etype])
			goto asfop;
		if(r->op == OCONST && typechl[n->type->etype]) {
			SET(v);
			switch(o) {
			case OASDIV:
			case OASMOD:
				c = r->vconst;
				if(c < 0)
					c = -c;
				v = log2(c);
				if(v < 0)
					break;
				/* fall thru */
			case OASMUL:
			case OASLMUL:
				if(hardleft)
					reglcgen(&nod2, l, Z);
				else
					nod2 = *l;
				regalloc(&nod, l, nn);
				cgen(&nod2, &nod);
				switch(o) {
				case OASMUL:
				case OASLMUL:
					mulgen(n->type, r, &nod);
					break;
				case OASDIV:
					sdiv2(r->vconst, v, l, &nod);
					break;
				case OASMOD:
					smod2(r->vconst, v, l, &nod);
					break;
				}
			havev:
				gmove(&nod, &nod2);
				if(nn != Z)
					gmove(&nod, nn);
				if(hardleft)
					regfree(&nod2);
				regfree(&nod);
				goto done;
			case OASLDIV:
				c = r->vconst;
				if((c & 0x80000000) == 0)
					break;
				if(hardleft)
					reglcgen(&nod2, l, Z);
				else
					nod2 = *l;
				regalloc(&nod1, l, nn);
				cgen(&nod2, &nod1);
				regalloc(&nod, l, nn);
				zeroregm(&nod);
				gins(ACMPL, &nod1, nodconst(c));
				gins(ASBBL, nodconst(-1), &nod);
				regfree(&nod1);
				goto havev;
			}
		}

		if(o == OASMUL) {
			/* should favour AX */
			regalloc(&nod, l, nn);
			if(r->complex >= FNX) {
				regalloc(&nod1, r, Z);
				cgen(r, &nod1);
				r = &nod1;
			}
			if(hardleft)
				reglcgen(&nod2, l, Z);
			else
				nod2 = *l;
			cgen(&nod2, &nod);
			if(r->addable < INDEXED || hardconst(r)) {
				if(r->complex < FNX) {
					regalloc(&nod1, r, Z);
					cgen(r, &nod1);
				}
				gopcode(OASMUL, n->type, &nod1, &nod);
				regfree(&nod1);
			}
			else
				gopcode(OASMUL, n->type, r, &nod);
			if(r == &nod1)
				regfree(r);
			gmove(&nod, &nod2);
			if(nn != Z)
				gmove(&nod, nn);
			regfree(&nod);
			if(hardleft)
				regfree(&nod2);
			break;
		}

		/*
		 * get nod to be D_AX
		 * get nod1 to be D_DX
		 */
		if(nodreg(&nod, nn, D_AX)) {
			regsalloc(&nod2, n);
			gmove(&nod, &nod2);
			v = reg[D_AX];
			reg[D_AX] = 0;

			if(isreg(l, D_AX)) {
				nod3 = *n;
				nod3.left = &nod2;
				cgen(&nod3, nn);
			} else
			if(isreg(r, D_AX)) {
				nod3 = *n;
				nod3.right = &nod2;
				cgen(&nod3, nn);
			} else
				cgen(n, nn);

			gmove(&nod2, &nod);
			reg[D_AX] = v;
			break;
		}
		if(nodreg(&nod1, nn, D_DX)) {
			regsalloc(&nod2, n);
			gmove(&nod1, &nod2);
			v = reg[D_DX];
			reg[D_DX] = 0;

			if(isreg(l, D_DX)) {
				nod3 = *n;
				nod3.left = &nod2;
				cgen(&nod3, nn);
			} else
			if(isreg(r, D_DX)) {
				nod3 = *n;
				nod3.right = &nod2;
				cgen(&nod3, nn);
			} else
				cgen(n, nn);

			gmove(&nod2, &nod1);
			reg[D_DX] = v;
			break;
		}
		reg[D_AX]++;
		reg[D_DX]++;

		if(l->complex >= r->complex) {
			if(hardleft)
				reglcgen(&nod2, l, Z);
			else
				nod2 = *l;
			cgen(&nod2, &nod);
			if(r->op == OCONST && typechl[r->type->etype]) {
				switch(o) {
				case OASDIV:
					sdivgen(&nod2, r, &nod, &nod1);
					goto divdone;
				case OASLDIV:
					udivgen(&nod2, r, &nod, &nod1);
				divdone:
					gmove(&nod1, &nod2);
					if(nn != Z)
						gmove(&nod1, nn);
					goto freelxaxdx;
				}
			}
			if(o == OASDIV || o == OASMOD)
				gins(typechl[l->type->etype]? ACDQ: ACQO, Z, Z);
			if(o == OASLDIV || o == OASLMOD)
				zeroregm(&nod1);
			if(r->addable < INDEXED || r->op == OCONST ||
			   !typeil[r->type->etype]) {
				regalloc(&nod3, r, Z);
				cgen(r, &nod3);
				gopcode(o, l->type, &nod3, Z);
				regfree(&nod3);
			} else
				gopcode(o, n->type, r, Z);
		} else {
			regalloc(&nod3, r, Z);
			cgen(r, &nod3);
			if(hardleft)
				reglcgen(&nod2, l, Z);
			else
				nod2 = *l;
			cgen(&nod2, &nod);
			if(o == OASDIV || o == OASMOD)
				gins(typechl[l->type->etype]? ACDQ: ACQO, Z, Z);
			if(o == OASLDIV || o == OASLMOD)
				zeroregm(&nod1);
			gopcode(o, l->type, &nod3, Z);
			regfree(&nod3);
		}
		if(o == OASMOD || o == OASLMOD) {
			gmove(&nod1, &nod2);
			if(nn != Z)
				gmove(&nod1, nn);
		} else {
			gmove(&nod, &nod2);
			if(nn != Z)
				gmove(&nod, nn);
		}
	freelxaxdx:
		if(hardleft)
			regfree(&nod2);
		regfree(&nod);
		regfree(&nod1);
		break;

	fop:
		if(l->complex >= r->complex) {
			regalloc(&nod, l, nn);
			cgen(l, &nod);
			if(r->addable < INDEXED) {
				regalloc(&nod1, r, Z);
				cgen(r, &nod1);
				gopcode(o, n->type, &nod1, &nod);
				regfree(&nod1);
			} else
				gopcode(o, n->type, r, &nod);
		} else {
			/* TO DO: could do better with r->addable >= INDEXED */
			regalloc(&nod1, r, Z);
			cgen(r, &nod1);
			regalloc(&nod, l, nn);
			cgen(l, &nod);
			gopcode(o, n->type, &nod1, &nod);
			regfree(&nod1);
		}
		gmove(&nod, nn);
		regfree(&nod);
		break;

	asbitop:
		regalloc(&nod4, n, nn);
		if(l->complex >= r->complex) {
			bitload(l, &nod, &nod1, &nod2, &nod4);
			regalloc(&nod3, r, Z);
			cgen(r, &nod3);
		} else {
			regalloc(&nod3, r, Z);
			cgen(r, &nod3);
			bitload(l, &nod, &nod1, &nod2, &nod4);
		}
		gmove(&nod, &nod4);

		{	/* TO DO: check floating point source */
			Node onod;

			/* incredible grot ... */
			onod = nod3;
			onod.op = o;
			onod.complex = 2;
			onod.addable = 0;
			onod.type = tfield;
			onod.left = &nod4;
			onod.right = &nod3;
			cgen(&onod, Z);
		}
		regfree(&nod3);
		gmove(&nod4, &nod);
		regfree(&nod4);
		bitstore(l, &nod, &nod1, &nod2, nn);
		break;

	case OADDR:
		if(nn == Z) {
			nullwarn(l, Z);
			break;
		}
		lcgen(l, nn);
		break;

	case OFUNC:
		if(l->complex >= FNX) {
			if(l->op != OIND)
				diag(n, "bad function call");

			regret(&nod, l->left);
			cgen(l->left, &nod);
			regsalloc(&nod1, l->left);
			gmove(&nod, &nod1);
			regfree(&nod);

			nod = *n;
			nod.left = &nod2;
			nod2 = *l;
			nod2.left = &nod1;
			nod2.complex = 1;
			cgen(&nod, nn);

			return;
		}
		o = reg[REGARG];
		gargs(r, &nod, &nod1);
		if(l->addable < INDEXED) {
			reglcgen(&nod, l, nn);
			nod.op = OREGISTER;
			gopcode(OFUNC, n->type, Z, &nod);
			regfree(&nod);
		} else
			gopcode(OFUNC, n->type, Z, l);
		if(REGARG)
			if(o != reg[REGARG])
				reg[REGARG]--;
		if(nn != Z) {
			regret(&nod, n);
			gmove(&nod, nn);
			regfree(&nod);
		}
		break;

	case OIND:
		if(nn == Z) {
			nullwarn(l, Z);
			break;
		}
		regialloc(&nod, n, nn);
		r = l;
		while(r->op == OADD)
			r = r->right;
		if(sconst(r)) {
			v = r->vconst;
			r->vconst = 0;
			cgen(l, &nod);
			nod.xoffset += v;
			r->vconst = v;
		} else
			cgen(l, &nod);
		regind(&nod, n);
		gmove(&nod, nn);
		regfree(&nod);
		break;

	case OEQ:
	case ONE:
	case OLE:
	case OLT:
	case OGE:
	case OGT:
	case OLO:
	case OLS:
	case OHI:
	case OHS:
		if(nn == Z) {
			nullwarn(l, r);
			break;
		}
		boolgen(n, 1, nn);
		break;

	case OANDAND:
	case OOROR:
		boolgen(n, 1, nn);
		if(nn == Z)
			patch(p, pc);
		break;

	case ONOT:
		if(nn == Z) {
			nullwarn(l, Z);
			break;
		}
		boolgen(n, 1, nn);
		break;

	case OCOMMA:
		cgen(l, Z);
		cgen(r, nn);
		break;

	case OCAST:
		if(nn == Z) {
			nullwarn(l, Z);
			break;
		}
		/*
		 * convert from types l->n->nn
		 */
		if(nocast(l->type, n->type) && nocast(n->type, nn->type)) {
			/* both null, gen l->nn */
			cgen(l, nn);
			break;
		}
		if(ewidth[n->type->etype] < ewidth[l->type->etype]){
			if(l->type->etype == TIND && typechlp[n->type->etype])
				warn(n, "conversion of pointer to shorter integer");
		}else if(0){
			if(nocast(n->type, nn->type) || castup(n->type, nn->type)){
				if(typefd[l->type->etype] != typefd[nn->type->etype])
					regalloc(&nod, l, nn);
				else
					regalloc(&nod, nn, nn);
				cgen(l, &nod);
				gmove(&nod, nn);
				regfree(&nod);
				break;
			}
		}
		regalloc(&nod, l, nn);
		cgen(l, &nod);
		regalloc(&nod1, n, &nod);
		gmove(&nod, &nod1);
		gmove(&nod1, nn);
		regfree(&nod1);
		regfree(&nod);
		break;

	case ODOT:
		sugen(l, nodrat, l->type->width);
		if(nn == Z)
			break;
		warn(n, "non-interruptable temporary");
		nod = *nodrat;
		if(!r || r->op != OCONST) {
			diag(n, "DOT and no offset");
			break;
		}
		nod.xoffset += (long)r->vconst;
		nod.type = n->type;
		cgen(&nod, nn);
		break;

	case OCOND:
		bcgen(l, 1);
		p1 = p;
		cgen(r->left, nn);
		gbranch(OGOTO);
		patch(p1, pc);
		p1 = p;
		cgen(r->right, nn);
		patch(p1, pc);
		break;

	case OPOSTINC:
	case OPOSTDEC:
		v = 1;
		if(l->type->etype == TIND)
			v = l->type->link->width;
		if(o == OPOSTDEC)
			v = -v;
		if(l->op == OBIT)
			goto bitinc;
		if(nn == Z)
			goto pre;

		if(hardleft)
			reglcgen(&nod, l, Z);
		else
			nod = *l;

		gmove(&nod, nn);
		if(typefd[n->type->etype]) {
			regalloc(&nod1, l, Z);
			gmove(&nod, &nod1);
			if(v < 0)
				gopcode(OSUB, n->type, nodfconst(-v), &nod1);
			else
				gopcode(OADD, n->type, nodfconst(v), &nod1);
			gmove(&nod1, &nod);
			regfree(&nod1);
		} else
			gopcode(OADD, n->type, nodconst(v), &nod);
		if(hardleft)
			regfree(&nod);
		break;

	case OPREINC:
	case OPREDEC:
		v = 1;
		if(l->type->etype == TIND)
			v = l->type->link->width;
		if(o == OPREDEC)
			v = -v;
		if(l->op == OBIT)
			goto bitinc;

	pre:
		if(hardleft)
			reglcgen(&nod, l, Z);
		else
			nod = *l;
		if(typefd[n->type->etype]) {
			regalloc(&nod1, l, Z);
			gmove(&nod, &nod1);
			if(v < 0)
				gopcode(OSUB, n->type, nodfconst(-v), &nod1);
			else
				gopcode(OADD, n->type, nodfconst(v), &nod1);
			gmove(&nod1, &nod);
			regfree(&nod1);
		} else
			gopcode(OADD, n->type, nodconst(v), &nod);
		if(nn != Z)
			gmove(&nod, nn);
		if(hardleft)
			regfree(&nod);
		break;

	bitinc:
		if(nn != Z && (o == OPOSTINC || o == OPOSTDEC)) {
			bitload(l, &nod, &nod1, &nod2, Z);
			gmove(&nod, nn);
			gopcode(OADD, tfield, nodconst(v), &nod);
			bitstore(l, &nod, &nod1, &nod2, Z);
			break;
		}
		bitload(l, &nod, &nod1, &nod2, nn);
		gopcode(OADD, tfield, nodconst(v), &nod);
		bitstore(l, &nod, &nod1, &nod2, nn);
		break;
	}
done:
	cursafe = curs;
}