            TextBox(Context& mContext, const Vec2f& mSize)
                : Widget{mContext, mSize / 2.f}, tBox(create<Widget>()),
                  lblText(tBox.create<Label>("")), cursor(editStr),
                  cursorShape{float(getStyle().getGlyphHeight())}
            {
                setFillColor(sf::Color::Transparent);

                lblText.onPostDraw += [this]
                {
                    if(editing) render(cursorShape.getShape());
                };

                tBox.setOutlineColor(getStyle().colorOutline);
                tBox.setOutlineThickness(getStyle().outlineThickness);
                tBox.setFillColor(sf::Color::White);
                tBox.setScaling(Scaling::FitToNeighbor);

                lblText.setScaling(Scaling::FitToNeighbor);

                tBox.attach(At::Center, *this, At::Center);
                lblText.attach(At::Center, tBox, At::Center);

                onLeftClick += [this]
                {
                    if(!editing) editStr = str;
                    editing = true;

                    if(isKeyPressed(ssvs::KKey::LShift))
                        cursor.setEnd(getCursorPos());
                    else
                        cursor.setBoth(getCursorPos());
                };
                onLeftClickDown += [this]
                {
                    cursor.setEnd(getCursorPos());
                };
            }