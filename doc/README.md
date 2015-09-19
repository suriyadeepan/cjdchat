# Algorithm : CJDCHAT
######

* Get the list of peers using cjdadmin libraries
* Update model based on peers
* Listen for incoming message at port : 5556
* if *join* message is received 
``` cpp
model_update(IPV6,nick,chan)
# call view_bufferMsg(nick,chan,JOIN_MSG) internally
```
* if *chat* message is received
``` cpp
view_bufferMsg(nick,chan,msg_txt)  
```
* if */join #chan* 
```
model_update(SELF_IP,SELF_NICK,chan)
# call view_bufferMsg(SELF_NICK,chan,JOIN_MSG) internally
broadcast(JOIN,SELF_NICK,SELF_IP,chan)
``` cpp
* if *text message*
``` cpp
view_bufferMsg(SELF_NICK,chan,msg_txt)
broadcast(MSG,SELF_NICK,chan)
```

