#include <IRremote.hpp>

const uint8_t DPIN_HEARTBIT_LED = 6;
const uint8_t DPIN_IR_IN = 7;
const uint8_t DPIN_RELAY_OUT = 8;
const uint8_t DPIN_RELAY_LED = 9;
const uint8_t DPIN_YAMAHA_ON_IN = 10;
const uint8_t DPIN_YAMAHA_LED = 11;

uint32_t ms = 0;

void setup() {
  Serial.println("Starting up....");
  ms = millis();
  Serial.begin(115200);

  setupHeartbit();
  setupYamaha();
  setupRelay();
  setupIR();
  switchRelayOff();
  Serial.println("Running!");
}

void loop() {
  ms = millis();

  loopHeartbit();
  loopIR();
  loopYamaha();
}


// #################### Heartbit ####################
uint32_t lastHeartUpdate = 0;
uint8_t heartValue = 0;
const uint8_t HEART_UPDATE_MS = 10;
boolean heartUp = true;

void setupHeartbit() {
  lastHeartUpdate = ms;
  pinMode(DPIN_HEARTBIT_LED, OUTPUT);
}

void loopHeartbit() {
  if (ms - lastHeartUpdate > HEART_UPDATE_MS) {

    if (heartUp) {
      heartValue++;
      if (heartValue == 255) {
        heartUp = false;
      }
    } else {
      heartValue--;
      if (heartValue == 0) {
        heartUp = true;
      }
    }

    lastHeartUpdate = ms;

    analogWrite(DPIN_HEARTBIT_LED, heartValue);
  }
}

// #################### Yamaha On/Off ####################
uint16_t yamahaOnCnt = 0;
const uint16_t YAMAHA_ON_CNT = 2000;

void setupYamaha() {
  pinMode(DPIN_YAMAHA_ON_IN, INPUT);
  pinMode(DPIN_YAMAHA_LED, OUTPUT);
  digitalWrite(DPIN_YAMAHA_LED, LOW);
}

void loopYamaha() {
  boolean yamahaNowOn = digitalRead(DPIN_YAMAHA_ON_IN) == LOW;
  if (yamahaNowOn && yamahaOnCnt < YAMAHA_ON_CNT) {
    yamahaOnCnt++;
    // switch relay after yamaha powers on
    if (yamahaOnCnt == YAMAHA_ON_CNT) {
      switchRelayOn();
    }
  } else if (!yamahaNowOn && yamahaOnCnt > 0) {
    yamahaOnCnt--;
      if (yamahaOnCnt == 0) {
      switchRelayOff();
    }
  }
}

// #################### Rrelay ####################
boolean relayOn = true;
void setupRelay() {
  pinMode(DPIN_RELAY_OUT, OUTPUT);
  pinMode(DPIN_RELAY_LED, OUTPUT);
  digitalWrite(DPIN_RELAY_OUT, HIGH);
  digitalWrite(DPIN_RELAY_LED, LOW);
}

void switchRelayOn() {
  relayOn = true;
  Serial.println("Relay ON");
  digitalWrite(DPIN_RELAY_OUT, LOW);
  digitalWrite(DPIN_RELAY_LED, HIGH);
}

void switchRelayOff() {
  relayOn = false;
  Serial.println("Relay Off");
  digitalWrite(DPIN_RELAY_OUT, HIGH);
  digitalWrite(DPIN_RELAY_LED, LOW);
}

// #################### IR/Rrelay ####################
const uint16_t IR_READ_DEBAUNCE_MS = 300;
const uint32_t IR_READ_KEY_1 = 5689;
const uint32_t IR_READ_KEY_2 = 7737;
uint32_t irReadTime = 0;

void setupIR() {
  irReadTime = ms;
  IrReceiver.begin(DPIN_IR_IN, ENABLE_LED_FEEDBACK);
}

void loopIR() {

  if (!IrReceiver.decode()) {
    return;
  }
  Serial.print("IR: ");
  Serial.println(IrReceiver.decodedIRData.decodedRawData);
  // IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
  // IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
  uint32_t irin = IrReceiver.decodedIRData.decodedRawData;
  if (ms - irReadTime > IR_READ_DEBAUNCE_MS && (irin == IR_READ_KEY_1 || irin == IR_READ_KEY_2)) {
    irReadTime = ms;
    if (relayOn) {
      switchRelayOff();
    } else {
      switchRelayOn();
    }
  }
  IrReceiver.resume();
}
