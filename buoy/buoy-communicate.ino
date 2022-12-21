#include "buoy-mcu.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const byte slaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char dataToSend[10] = "Message 0";
char txNum = '0';

void init_TX()
{
    MCU_serialPrint("setup transmit");

    radio.begin();
    radio.setDataRate(RF24_250KBPS);
    radio.setRetries(3, 5); // delay, count
    radio.openWritingPipe(slaveAddress);
}

// --------------------------------------------------------------------------------------------------------------------
void rf_transmit()
{
    bool rslt;
    rslt = radio.write(&dataToSend, sizeof(dataToSend));
    // Always use sizeof() as it gives the size as the number of bytes.
    // For example if dataToSend was an int sizeof() would correctly return 2

    Serial.print("Data Sent ");
    Serial.print(dataToSend);
    if (rslt) {
        MCU_serialPrint("  Acknowledge received");
        updateMessage();

    } else {
        MCU_serialPrint("  Tx failed");
    }
}

// --------------------------------------------------------------------------------------------------------------------
void updateMessage()
{
    // so you can see that new data is being sent
    txNum += 1;
    if (txNum > '9') txNum = '0';
    dataToSend[8] = txNum;
}
