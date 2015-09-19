# Algorithm : CJDCHAT
######

1. Get the list of peers using cjdadmin libraries
2. Update model based on peers
3. Listen for incoming message at port : 5556
4. if *join* message is received 
```
model_update(IPV6,nick,chan)
# call view_bufferMsg(nick,chan,JOIN_MSG) internally
```
5. if *chat* message is received
```
view_bufferMsg(nick,chan,msg_txt)  
```
6. if */join #chan* 
```
model_update(SELF_IP,SELF_NICK,chan)
# call view_bufferMsg(SELF_NICK,chan,JOIN_MSG) internally
broadcast(JOIN,SELF_NICK,SELF_IP,chan)
```
7. if *text message*
```
view_bufferMsg(SELF_NICK,chan,msg_txt)
broadcast(MSG,SELF_NICK,chan)
```
######
