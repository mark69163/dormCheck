#include "relay.h"
#include "settings.h"

// Relay state
static bool relayState = true;  // Initial state of the relay is OFF

// Initialize the relay
void init_relay() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);  // Ensure relay is off initially
}

// Toggle the relay based on the state (ACCEPT, TEST, DECLINE)
void toggle_relay(States state) {
    if (is_relay_disabled()) {
      return;
    }

    switch (state) {
        case ACCEPT:
            relayState = false;  // Relay ON for ACCEPT
            break;
        case TEST:
            relayState = !relayState;  // Toggle for TEST
            break;
        default:
            relayState = true;  // Relay OFF for DECLINE
        break;
    }

    digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);  // Set the relay state
}