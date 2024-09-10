/* Never was great formulating =P */
bool CWordFilter::apply(CPlayer *pPlayer, CBuffer &pBuffer, int pCheck)
{
	bool logsave = false, rctell = false;
	CBuffer start;
	CStringList found;
	int pos = 0, wc = 0;

	for (int i = 0; i < WordList.count(); i++)
	{
		WordMatch *word = (WordMatch *)WordList[i];
		if (!word->check[pCheck])
			continue;

		for (int j = 0; j < pBuffer.length(); j++)
		{
			for (int k = 0; k < word->match.length(); k++)
			{
				char c1 = pBuffer[j + k];
				char c2 = word->match[k];
				if (c2 != '?' && (isUpper(c2) && c2 != c1) || (isLower(c2) && toLower(c2) != toLower(c1)))
				{
					if (wc >= word->precision)
					{
						found.add(start);

						for (int l = 0; l < (int)sizeof(word->action); l++)
						{
							if (!word->action[l])
								continue;

							switch (l)
							{
								case FILTERA_LOG:
									if (logsave)
										break;

									logsave = true;
									if (pPlayer != NULL)
										errorOut("wordfilter.txt", CBuffer() << pPlayer->accountName << " has used rude words while chatting: " << start);
								break;

								case FILTERA_REPLACE:
									pos = pBuffer.find(' ', j);
									pos = (pos == -1 ? start.length() : pos-j+1);
									for (int m = 0; m < pos; m++)
										pBuffer.replace(j + m, '*');
								break;

								case FILTERA_TELLRC:
									if (rctell)
										break;

									rctell = true;
									if (pPlayer != NULL)
										sendRCPacket(CPacket() << (char)DRCLOG << pPlayer->accountName << " has used rude words while chatting: " << start);
								break;

								case FILTERA_WARN:
									pBuffer = (word->warnmessage.length() > 0 ? word->warnmessage : warnmessage);
								break;

								case FILTERA_JAIL: // kinda useless...?
								break;

								case FILTERA_BAN:
									if (pPlayer != NULL)
									{
										CBuffer pLog = CBuffer() << "\n" << getTimeStr(0) << "\n" << pPlayer->accountName << " has used rude words while chatting: " << start;
										pPlayer->setBan(pLog, true);
									}
								break;
							}
						}
					}

					start.clear();
					wc = 0;
					break;
				}

				start.writeChar(c1);
				wc++;
			}
		}
	}

	return (found.count() > 0);
}