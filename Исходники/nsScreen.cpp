bool
nsScreen::MozLockOrientation(const Sequence<nsString>& aOrientations,
                             ErrorResult& aRv)
{
  if (ShouldResistFingerprinting()) {
    return false;
  }
  hal::ScreenOrientation orientation = hal::eScreenOrientation_None;

  for (uint32_t i = 0; i < aOrientations.Length(); ++i) {
    const nsString& item = aOrientations[i];

    if (item.EqualsLiteral("portrait")) {
      orientation |= hal::eScreenOrientation_PortraitPrimary |
                     hal::eScreenOrientation_PortraitSecondary;
    } else if (item.EqualsLiteral("portrait-primary")) {
      orientation |= hal::eScreenOrientation_PortraitPrimary;
    } else if (item.EqualsLiteral("portrait-secondary")) {
      orientation |= hal::eScreenOrientation_PortraitSecondary;
    } else if (item.EqualsLiteral("landscape")) {
      orientation |= hal::eScreenOrientation_LandscapePrimary |
                     hal::eScreenOrientation_LandscapeSecondary;
    } else if (item.EqualsLiteral("landscape-primary")) {
      orientation |= hal::eScreenOrientation_LandscapePrimary;
    } else if (item.EqualsLiteral("landscape-secondary")) {
      orientation |= hal::eScreenOrientation_LandscapeSecondary;
    } else if (item.EqualsLiteral("default")) {
      orientation |= hal::eScreenOrientation_Default;
    } else {
      // If we don't recognize the token, we should just return 'false'
      // without throwing.
      return false;
    }
  }

  switch (mScreenOrientation->GetLockOrientationPermission(false)) {
    case ScreenOrientation::LOCK_DENIED:
      return false;
    case ScreenOrientation::LOCK_ALLOWED:
      UpdateDocShellOrientationLock(GetOwner(), orientation);
      return mScreenOrientation->LockDeviceOrientation(orientation, false, aRv);
    case ScreenOrientation::FULLSCREEN_LOCK_ALLOWED:
      UpdateDocShellOrientationLock(GetOwner(), orientation);
      return mScreenOrientation->LockDeviceOrientation(orientation, true, aRv);
  }

  // This is only for compilers that don't understand that the previous switch
  // will always return.
  MOZ_CRASH("unexpected lock orientation permission value");
}