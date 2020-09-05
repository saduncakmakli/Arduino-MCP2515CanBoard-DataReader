#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>

const int spiCSPin = 10;

MCP_CAN CAN(spiCSPin);

void setup()
{
    Serial.begin(9600);

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN BUS Init Failed");
        delay(100);
    }
    Serial.println("CAN BUS  Init OK!");
}

void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())
    {
        CAN.readMsgBuf(&len, buf);

        unsigned long canId = CAN.getCanId();

        Serial.println("-----------------------------");
        Serial.print("Data from ID: 0x");
        Serial.println(canId, HEX);

        Serial.print(canId);
        Serial.print(",");

        for(int i = 0; i<len; i++)
        {
            Serial.print(buf[i]);
            Serial.print(" | ");
        }

        Serial.println();
    }
}