/*Function: void EditStuProfileControl::updateProfile
 * Purpose: if editing, update profile settings in db
 *          if creating, add new profile to db
 */
void EditStuProfileControl::updateProfile()
{
    if(_action == 1) editProfile();
    else createProfile();
}