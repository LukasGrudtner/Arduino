#include "AESLib.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
}

void loop() {
  uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  uint8_t iv[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  char data[] = "0123456789012345";
  const uint16_t data_len = 16;
  aes192_cbc_enc(key, iv, data, data_len);
  Serial.print("encrypted:");
  Serial.println(data);

//  int i;
//  for (i = 0; i < 16; i++) {
//    Serial.print("%02hhX", data[i]);
//  }
//  Serial.print("\n");
/******************************************/
    char str[12];

    unsigned char * pin = data;
    const char * hex = "0123456789ABCDEF";
    char * pout = str;
    int i = 0;

    Serial.println(sizeof(data));
    for(; i < sizeof(data)-1; ++i){
        *pout++ = hex[(*pin>>4)&0xF];
        *pout++ = hex[(*pin++)&0xF];
        *pout++ = ':';
    }
    *pout++ = hex[(*pin>>4)&0xF];
    *pout++ = hex[(*pin)&0xF];
    *pout = 0;

    Serial.println(str);
    Serial.println();
    
/******************************************/

  aes192_cbc_dec(key, iv, data, data_len);
  Serial.print("decrypted:");
  Serial.println(data);
  delay(2000);
}

