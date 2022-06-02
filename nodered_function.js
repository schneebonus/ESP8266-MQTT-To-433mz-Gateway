/** Inputs:
msg.topic -> Name of the device
msg.payload -> Boolean switching state
                true  -> on
                false -> off
**/

// define gateway
gateway_ip = "";     // ToDo

// Device -> house code + device code
let devices = {
    desklamp        : "00111"+"10000",
    fernseher       : "00111"+"01000",
    small_monitor   : "00111"+"00100",
    big_monitor     : "00111"+"00010",
    chromecast      : "00000"+"00000",
    printerlamp     : "00000"+"00000",
    watering        : "00000"+"00000",
    raumstation     : "00000"+"00000",
}

// prepare mqtt publish
msg.payload ? msg.payload = "true" : msg.payload = "false";
msg.topic = "433mhz/"+devices[msg.topic];
return msg;
