// Gateway definieren
gateway_ip = "";  // ToDo

// Gerät -> Hauscode + Gerätecode
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

// mqtt publish vorbereiten
msg.payload ? msg.payload = "true" : msg.payload = "false";
msg.topic = "433mhz/"+devices[msg.topic];
return msg;
