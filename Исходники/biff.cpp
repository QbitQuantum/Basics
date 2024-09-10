void mailbox::paint_mailbox(void)
{
    bitBlt(this, 0, (height()/2)-(envelope.height()/2), &envelope);
}