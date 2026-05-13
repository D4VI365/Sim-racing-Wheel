#include <Joystick.h>

// Definiamo i pin utilizzati come appaiono sul tuo schema J3
// I pin corrispondono ai nomi serigrafati sull'Arduino Pro Micro
const int buttonPins[] = {
  1,  // TX
  0,  // RX
  2,  // D2
  3,  // D3
  4,  // D4
  5,  // D5
  6,  // D6
  7,  // D7
  8,  // D8
  9,  // D9
  10, // D10
  16, // D11 (MOSI)
  14, // D12 (MISO)
  15  // D13 (SCK)
};

const int numButtons = 14;

// Inizializziamo il Joystick con 14 bottoni
// Tipo Joystick, numero bottoni, numero switch cappello, X, Y, Z, Rx, Ry, Rz, Rudder, Throttle, Accelerator, Brake, Steering
Joystick_ Joystick(0x03, JOYSTICK_TYPE_JOYSTICK, 
  numButtons, 0, // 14 bottoni, 0 hat switches
  false, false, false, // No assi X, Y, Z
  false, false, false, // No assi rotazione
  false, false,        // No rudder o throttle
  false, false, false  // No acceleratore, freno o sterzo
);

void setup() {
  // Configurazione dei pin come INPUT
  // Avendo le resistenze di pull-up da 10k esterne (R1-R14 nello schema),
  // il segnale sarà HIGH a riposo e LOW quando premi il tasto.
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT);
  }

  Joystick.begin();
}

void loop() {
  for (int i = 0; i < numButtons; i++) {
    // Leggiamo lo stato del pin
    int currentState = digitalRead(buttonPins[i]);
    
    // Poiché hai pull-up esterne: 
    // HIGH (1) = Tasto rilasciato
    // LOW (0) = Tasto premuto
    // setButton vuole 1 per premuto, quindi invertiamo con '!'
    Joystick.setButton(i, !currentState);
  }
  
  // Piccolo delay per stabilità e per evitare di saturare il buffer USB
  delay(10);
}