#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <Arduino.h>
#include <vector>
#include <FS.h>

class WiFiAP {
public:
    bool    active;
    String  password;
};

class Beacon {
public:
    String  callsign;
    String  symbol;
    String  overlay;
    String  comment;
    bool    smartBeaconActive;
    byte    smartBeaconSetting;
    String  micE;
    bool    gpsEcoMode;
};

class Display {
public:
    bool    showSymbol;
    bool    ecoMode;
    int     timeout;
    bool    turn180;
};

class Winlink {
public:
    String  password;
};

class BME {
public:
    bool    active;
    float   temperatureCorrection;
    bool    sendTelemetry;
};

class Notification {
public:
    bool    ledTx;
    int     ledTxPin;
    bool    ledMessage;
    int     ledMessagePin;
    bool    ledFlashlight;
    int     ledFlashlightPin;
    bool    buzzerActive;
    int     buzzerPinTone;
    int     buzzerPinVcc;
    bool    bootUpBeep;
    bool    txBeep;
    bool    messageRxBeep;
    bool    stationBeep;
    bool    lowBatteryBeep;
    bool    shutDownBeep;
};

class LoraType {
public:
    long  frequency;
    int   spreadingFactor;
    long  signalBandwidth;
    int   codingRate4;
    int   power;
};

class Ptt {
public:
    bool  active;
    int   io_pin;
    int   preDelay;
    int   postDelay;
    bool  reverse;
};

class Configuration {
public:

    WiFiAP                  wifiAP;
    std::vector<Beacon>     beacons;  
    Display                 display;
    Winlink                 winlink;
    BME                     bme;
    Notification            notification;
    std::vector<LoraType>   loraTypes;
    Ptt                     ptt;
    
    bool    simplifiedTrackerMode;
    int     sendCommentAfterXBeacons;
    String  path;
    int     nonSmartBeaconRate;
    int     rememberStationTime;
    int     maxDistanceToTracker;
    int     standingUpdateTime;
    bool    sendAltitude;
    bool    sendBatteryInfo;
    int     bluetoothType;
    bool    bluetoothActive;
    bool    disableGPS;


    void init();
    void writeFile();
    Configuration();
    bool validateConfigFile(const String& currentBeaconCallsign);
    bool validateMicE(const String& currentBeaconMicE);

private:
    bool readFile();
};

#endif