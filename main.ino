#define BYTES 7

void setup() {
  Serial.begin(19200);
  for (byte cnt=50;cnt!=1;pinMode(cnt--, INPUT_PULLUP));
}

byte oldOutput[BYTES];
void loop() {
  byte output[BYTES] = {0};
  for (size_t b = 0; b != BYTES; ++b) {
    for (size_t i = 0; i != 8; ++i) {
      size_t index = (b*8) + i;
      if (index > 50) break;
      int sensorVal = 1 - digitalRead(index+2);
      output[b] ^= (-sensorVal ^ output[b]) & (1 << i);
    }
  }
  
  bool hasChanged = memcmp(oldOutput, output, BYTES) != 0;
  memcpy(oldOutput, output, BYTES);

  if (hasChanged) {
    Serial.write(output, BYTES);
    Serial.flush();
  }
  //delay(25);
}
