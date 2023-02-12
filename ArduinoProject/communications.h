#include "includes.h"


class Communications{
  public:
    WiFiClient* client;
    Communications(WiFiClient* client){
      this->client = client;
    }
    
    String recv(){
      String req = "";
    
      while(client->connected()){
        while(client->available()){
          char c = client->read();    
          if('\n' == c) return req;
    
          req += c;
        }
      }
      return req;
    }

    void send(String response){
      client->println(response);
    }
};
