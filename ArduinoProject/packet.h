class SimplePacket{
  public:
    SimplePacket(){}
    SimplePacket(String data){
      param = -1; //Set default value
      data += data.endsWith(" ") ? "" : " "; //Add a space at the end if there is none, this way the loop to get the params/vars will be correct
      String current = "";
      for(char c : data){
        if(c != ' ') {
          current += c;
          continue;
        }
         
        if(actionType.length() == 0){
          actionType = current;
        }else if(message.length() == 0){
          message = current;
        }else if(param == -1){
          param = current.toInt();
        }
        current = "";
      }
    }
    
    String actionType;
    String message;
    int param;
    
    bool isEmpty(){
      return actionType.length() == 0;
    }
    
    virtual void printInfo(){
      Serial.println("------------");
      Serial.print("Packet: ");
      Serial.println(actionType);
      Serial.print("Message: ");
      Serial.println(message);
      Serial.print("Param: ");
      Serial.println(param);
    }
};
