/****************************************************************************
**
** Author: Tim Sjoberg
**
** Populates a packet with the information required to register a new account
**
****************************************************************************/
void Register::buildPacket(MXit::Network::Packet *packet, VariableHash &variables)
{
  /*
  == PACKET FORMAT
  ***************************************************************************
  **
  **  id=loginname[\1sesid]\0
  **  cm=11\0
  **  ms=password \1 version \1 maxReplyLen [ \1 name ] \1 dateOfBirth \1 
  **  gender \1 location \1 capabilities \1 dc \1 features \1 dialingCode \1
  **  locale
  **
  ***************************************************************************
  
  == DEFINITIONS
  ***************************************************************************
  **
  **  password            is the 7 to 10 digit pin (ONLY numeric characters 
  **                      allowed)
  **  version             the version number (see 1. Login)
  **  maxReplyLen         the maximum length a single reply may be
  **  name                the user's name/nickname
  **  dateOfBirth         an ISO 8601 date of the user's birth (format 
  **                      YYYY-MM-DD)
  **  gender              the user's gender:
  **                        0 - female
  **                        1 - male
  **  location            a string describing the user's location (max 64 
  **                      characters)
  **  capabilities        see Login command
  **  dc                  distribution code that identifies the 
  **                      loginname/installation combination
  **                      uniquely
  **  features            a bitset describing client features (see 1. Login)
  **  dialingCode         the international dialing code for the user's country 
  **                      (see Appendix A)
  **  locale              the user's locale (see Appendix A)
  **
  ***************************************************************************
  */
  
  /* first - password encryption (Appendix B) */
  QString key = QString("6170383452343567").replace(0, 8, variables["pid"].right(8));
  QString pass = "******" + variables["_password"];
  MXit::Protocol::AES encryptor;
  variables["encryptedpassword"] = encryptor.encrypt(key.toLatin1(), pass.toLatin1()).toBase64();
    
  /* next - get distributor code from pid */
  variables.remove("dc");
  QByteArray dc = variables["pid"];
  dc.replace(0, 2, "");
  dc = dc.left(dc.length() - 8);
  variables["dc"] = dc;
  
  (*packet) << variables["encryptedpassword"]
            << "E-5.8.2-Y-LPM"                    // version
            << "150000"                       /* maxReplyLen, sniffed from a Nokia E51 */
            << variables["name"]
            << variables["dateOfBirth"]
            << variables["gender"]
            << variables["location"]
            << "utf8=false;ctyp=8129"         /* capabilities */
            << variables["dc"]
            << "524287"                       /* features */
            << variables["defaultDialingCode"]
            << variables["locale"]
  ;
}