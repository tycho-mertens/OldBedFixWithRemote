#include "includes.h"


//This class will probably be used later as a remote console for debugging and maybe running commands
class TelnetConsole{
  public:
    String prefix;
    Communications* coms;
    
    TelnetConsole(Communications* coms){
      prefix = "CONSOLE: ";
      this->coms = coms;
    }

    void println(String msg){
      msg = prefix + msg;
      coms->send(msg);
      Serial.println(msg);
    }

};
