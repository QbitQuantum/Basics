/* ****************************************************************************
*
* getCurrentTime - 
*/
TEST(commonGlobals, getCurrentTime)
{
  int now;

  // 1. No timer
  setTimer(NULL);
  now = getCurrentTime();
  EXPECT_EQ(-1, now);

  utInit();  // timer is set up inside utInit
  now = getCurrentTime();
  EXPECT_TRUE(now != -1);
  utExit();
}