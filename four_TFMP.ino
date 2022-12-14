# Four TFmini Plus LiDAR 
# data time --> distance1 strenght1 distance2 strenght2 distance3 strenght3 distance4 strenght4

#include <SoftwareSerial.h>  

//SoftwareSerial port(TX, RX);
SoftwareSerial portOne(2, 2);
SoftwareSerial portTwo(3, 3); 
SoftwareSerial portThree(8, 7);
SoftwareSerial portFour(10, 11); 


void getTFminiData(SoftwareSerial* port, int* distance, int* strength, boolean* complete) {
  static char i = 0;
  char j = 0;
  int checksum = 0; 
  static int rx[9];

  port->listen();
  if(port->available()) {  
    rx[i] = port->read();
    if(rx[0] != 0x59) {
      i = 0;
    } else if(i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if(i == 8) {
      for(j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if(rx[8] == (checksum % 256)) {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;
        *complete = true;
      }
      i = 0;
    } else {
      i++;
    } 
  }  
}

void setup() {
  Serial.begin(115200);
  portOne.begin(115200);
  portTwo.begin(115200);
  portThree.begin(115200);
  portFour.begin(115200);
}

void loop() {
  int distance1 = 0;
  int strength1 = 0;
  boolean receiveComplete1 = false;

  int distance2 = 0;
  int strength2 = 0;
  boolean receiveComplete2 = false;

  int distance3 = 0;
  int strength3 = 0;
  boolean receiveComplete3 = false;

  int distance4 = 0;
  int strength4 = 0;
  boolean receiveComplete4 = false;

  while(!receiveComplete1) {
    getTFminiData(&portOne, &distance1, &strength1, &receiveComplete1);
    if(receiveComplete1) {
      Serial.print(distance1);
      Serial.print("cm\t");
      Serial.print("strength1: ");
      Serial.print(strength1);
      Serial.print("\t");
    }
  }
  receiveComplete1 = false;

  while(!receiveComplete2) {
    getTFminiData(&portTwo, &distance2, &strength2, &receiveComplete2);
    if(receiveComplete2) {
      Serial.print(distance2);
      Serial.print("cm\t");
      Serial.print("strength2: ");
      Serial.print(strength2);
      Serial.print("\t")
    }
  }
  receiveComplete2 = false;

  while(!receiveComplete3) {
    getTFminiData(&portThree, &distance3, &strength3, &receiveComplete3);
    if(receiveComplete3) {
      Serial.print(distance3);
      Serial.print("cm\t");
      Serial.print("strength3: ");
      Serial.print(strength3);
      Serial.print("\t");
    }
  }
  receiveComplete3 = false;

  while(!receiveComplete4) {
    getTFminiData(&portFour, &distance4, &strength4, &receiveComplete4);
    if(receiveComplete4) {
      Serial.print(distance4);
      Serial.print("cm\t");
      Serial.print("strength4: ");
      Serial.println(strength4);
    }
  }
  receiveComplete4 = false; 


}