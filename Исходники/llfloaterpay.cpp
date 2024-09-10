// static
void LLFloaterPay::processPayPriceReply(LLMessageSystem* msg, void **userdata)
{
	LLFloaterPay* self = (LLFloaterPay*)userdata;
	if (self)
	{
		S32 price;
		LLUUID target;

		msg->getUUIDFast(_PREHASH_ObjectData,_PREHASH_ObjectID,target);
		if (target != self->mTargetUUID)
		{
			// This is a message for a different object's pay info
			return;
		}

		msg->getS32Fast(_PREHASH_ObjectData,_PREHASH_DefaultPayPrice,price);
		
		if (PAY_PRICE_HIDE == price)
		{
			self->getChildView("amount")->setVisible(FALSE);
			self->getChildView("pay btn")->setVisible(FALSE);
			self->getChildView("amount text")->setVisible(FALSE);
		}
		else if (PAY_PRICE_DEFAULT == price)
		{			
			self->getChildView("amount")->setVisible(TRUE);
			self->getChildView("pay btn")->setVisible(TRUE);
			self->getChildView("amount text")->setVisible(TRUE);
		}
		else
		{
			// PAY_PRICE_HIDE and PAY_PRICE_DEFAULT are negative values
			// So we take the absolute value here after we have checked for those cases
			
			self->getChildView("amount")->setVisible(TRUE);
			self->getChildView("pay btn")->setVisible(TRUE);
			self->getChildView("pay btn")->setEnabled(TRUE);
			self->getChildView("amount text")->setVisible(TRUE);

			self->getChild<LLUICtrl>("amount")->setValue(llformat("%d", llabs(price)));
		}

		S32 num_blocks = msg->getNumberOfBlocksFast(_PREHASH_ButtonData);
		S32 i = 0;
		if (num_blocks > MAX_PAY_BUTTONS) num_blocks = MAX_PAY_BUTTONS;

		S32 max_pay_amount = 0;
		S32 padding_required = 0;

		for (i=0;i<num_blocks;++i)
		{
			S32 pay_button;
			msg->getS32Fast(_PREHASH_ButtonData,_PREHASH_PayButton,pay_button,i);
			if (pay_button > 0)
			{
				std::string button_str = "L$";
				button_str += LLResMgr::getInstance()->getMonetaryString( pay_button );

				self->mQuickPayButton[i]->setLabelSelected(button_str);
				self->mQuickPayButton[i]->setLabelUnselected(button_str);
				self->mQuickPayButton[i]->setVisible(TRUE);
				self->mQuickPayInfo[i]->mAmount = pay_button;
				self->getChildView("fastpay text")->setVisible(TRUE);

				if ( pay_button > max_pay_amount )
				{
					max_pay_amount = pay_button;
				}
			}
			else
			{
				self->mQuickPayButton[i]->setVisible(FALSE);
			}
		}

		// build a string containing the maximum value and calc nerw button width from it.
		std::string balance_str = "L$";
		balance_str += LLResMgr::getInstance()->getMonetaryString( max_pay_amount );
		const LLFontGL* font = LLFontGL::getFontSansSerif();
		S32 new_button_width = font->getWidth( std::string(balance_str));
		new_button_width += ( 12 + 12 );	// padding

		// dialong is sized for 2 digit pay amounts - larger pay values need to be scaled
		const S32 threshold = 100000;
		if ( max_pay_amount >= threshold )
		{
			S32 num_digits_threshold = (S32)log10((double)threshold) + 1;
			S32 num_digits_max = (S32)log10((double)max_pay_amount) + 1;
				
			// calculate the extra width required by 2 buttons with max amount and some commas
			padding_required = ( num_digits_max - num_digits_threshold + ( num_digits_max / 3 ) ) * font->getWidth( std::string("0") );
		};

		// change in button width
		S32 button_delta = new_button_width - FASTPAY_BUTTON_WIDTH;
		if ( button_delta < 0 ) 
			button_delta = 0;

		// now we know the maximum amount, we can resize all the buttons to be 
		for (i=0;i<num_blocks;++i)
		{
			LLRect r;
			r = self->mQuickPayButton[i]->getRect();

			// RHS button colum needs to move further because LHS changed too
			if ( i % 2 )
			{
				r.setCenterAndSize( r.getCenterX() + ( button_delta * 3 ) / 2 , 
					r.getCenterY(), 
						r.getWidth() + button_delta, 
							r.getHeight() ); 
			}
			else
			{
				r.setCenterAndSize( r.getCenterX() + button_delta / 2, 
					r.getCenterY(), 
						r.getWidth() + button_delta, 
						r.getHeight() ); 
			}
			self->mQuickPayButton[i]->setRect( r );
		}

		for (i=num_blocks;i<MAX_PAY_BUTTONS;++i)
		{
			self->mQuickPayButton[i]->setVisible(FALSE);
		}

		self->reshape( self->getRect().getWidth() + padding_required, self->getRect().getHeight(), FALSE );
	}
	msg->setHandlerFunc("PayPriceReply",NULL,NULL);
}