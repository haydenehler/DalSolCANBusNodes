// Dal Solar Car CAN-Bus Node
// Hayden Ehler, February 2024

// *********************
//       NODE A
// *********************


// Communication Parameters
// CAN Bitrate: 125 kbps

#include <SPI.h>
#include <mcp2515.h>


struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(2);


void setup() {
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);

  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);

  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 8;

  canMsg2.can_id  = 0x036;
  canMsg2.can_dlc = 8;

  
  while (!Serial);
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {
  int A1_conf = digitalRead(9);
  int A2_conf = digitalRead(8);
  int A3_conf = digitalRead(7);
  int A4_conf = digitalRead(6);
  int A5_conf = digitalRead(5);
  int A6_conf = digitalRead(4);

  canMsg1.data[0] = A1_conf;
  canMsg1.data[1] = A2_conf;
  canMsg1.data[2] = A3_conf;
  canMsg1.data[3] = A4_conf;
  canMsg1.data[4] = A5_conf;
  canMsg1.data[5] = A6_conf;
  canMsg1.data[6] = 0xBE;
  canMsg1.data[7] = 0x86;

  int A1_data = analogRead(A2);
  int A2_data = analogRead(A3);
  int A3_data = analogRead(A4);
  int A4_data = analogRead(A5);
  int A5_data = analogRead(A6);
  int A6_data = analogRead(A7);

  canMsg2.data[0] = A1_data;
  canMsg2.data[1] = A2_data;
  canMsg2.data[2] = A3_data;
  canMsg2.data[3] = A4_data;
  canMsg2.data[4] = A5_data;
  canMsg2.data[5] = A6_data;
  canMsg2.data[6] = 0x00;
  canMsg2.data[7] = 0xA0;

  mcp2515.sendMessage(&canMsg1);
  mcp2515.sendMessage(&canMsg2);

  Serial.println("Messages sent");
  
  delay(100);
}
