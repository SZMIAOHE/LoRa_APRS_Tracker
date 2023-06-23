#include <LoRa.h>
#include <logger.h>
#include "configuration.h"
#include "display.h"
#include "msg_utils.h"

extern logging::Logger logger;
extern Configuration Config;

namespace LoRa_Utils {

void setup() {
  logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, "LoRa", "Set SPI pins!");
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, "LoRa", "Set LoRa pins!");
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);

  long freq = Config.loramodule.frequency;
  logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, "LoRa", "frequency: %d", freq);
  if (!LoRa.begin(freq)) {
    logger.log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, "LoRa", "Starting LoRa failed!");
    show_display("ERROR", "Starting LoRa failed!");
    //displayUtils::show("ERROR", "Starting LoRa failed!");
    while (true) {
      delay(1000);
    }
  }
  LoRa.setSpreadingFactor(Config.loramodule.spreadingFactor);
  LoRa.setSignalBandwidth(Config.loramodule.signalBandwidth);
  LoRa.setCodingRate4(Config.loramodule.codingRate4);
  LoRa.enableCrc();

  LoRa.setTxPower(Config.loramodule.power);
  logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, "LoRa", "LoRa init done!");
}

void sendNewPacket(const String &newPacket) {
  LoRa.beginPacket();
  LoRa.write('<');
  LoRa.write(0xFF);
  LoRa.write(0x01);
  LoRa.write((const uint8_t *)newPacket.c_str(), newPacket.length());
  LoRa.endPacket();
}

String receivePacket() {
  String loraPacket = "";
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      int inChar = LoRa.read();
      loraPacket += (char)inChar;
    }
    //rssi      = LoRa.packetRssi();
    //snr       = LoRa.packetSnr();
    //freqError = LoRa.packetFrequencyError();
  }
  return loraPacket;
}

}