#include <Arduino.h>
#include <IRremote.h>

#define LED_PIN 13
#define ALEXA_ON_PIN 12
#define PROJECTOR_ON_PIN 11
#define BUTTON_PIN 8
#define IR_RECV_PIN 9

unsigned long FLIP_BUTTON_CODE = 0xFFB847;


int last_button_state = 0;
bool is_on = false;

IRrecv irrecv(IR_RECV_PIN);
decode_results results;



void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(ALEXA_ON_PIN, OUTPUT);
    pinMode(PROJECTOR_ON_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    Serial.begin(9600);
    Serial.println("Hello Arduino");
    irrecv.enableIRIn(); // Start the receiver
}


void loop() {
    /*
    int button_state = digitalRead(BUTTON_PIN);
    if (button_state != last_button_state) {
        is_on = !is_on;
    }
    last_button_state = button_state;
    */

    if (irrecv.decode(&results)) {
        if (results.value == FLIP_BUTTON_CODE && results.decode_type == NEC) {
            Serial.println("Flipping!");
            is_on = !is_on;
        }
        irrecv.resume(); // Receive the next value
    }

    if (is_on) {
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(ALEXA_ON_PIN, HIGH);
        digitalWrite(PROJECTOR_ON_PIN, LOW);
    }
    else {
        digitalWrite(LED_PIN, LOW);
        digitalWrite(ALEXA_ON_PIN, LOW);
        digitalWrite(PROJECTOR_ON_PIN, HIGH);
    }
}
