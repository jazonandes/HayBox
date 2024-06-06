#include "modes/RivalsOfAether.hpp"

RivalsOfAether::RivalsOfAether(socd::SocdType horizontal_socd, socd::SocdType vertical_socd) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,   &InputState::right, socd::SOCD_NEUTRAL         },
 /* Mod X override C-Up input if both are pressed. Without this, neutral SOCD doesn't work
  properly if Down and both Up buttons are pressed, because it first resolves Down + Mod X
  to set both as unpressed, and then it sees C-Up as pressed but not Down, so you get an up
  input instead of neutral. */
        socd::SocdPair{ &InputState::mod_x, &InputState::c_right,  socd::SOCD_DIR1_PRIORITY},
        socd::SocdPair{ &InputState::down,  &InputState::mod_x, socd::SOCD_2IP           },
        socd::SocdPair{ &InputState::down,  &InputState::c_up,  socd::SOCD_2IP           },
    };
}

void RivalsOfAether::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Directions
    outputs.dpadLeft = inputs.left;
    outputs.dpadRight = inputs.right;
    outputs.dpadDown = inputs.down;
    outputs.dpadUp = inputs.mod_x || inputs.c_right;

    // Menu keys
    outputs.start = inputs.start;
    outputs.select = inputs.midshield;
    outputs.home = inputs.mod_y;
    outputs.leftStickClick = inputs.l;
    outputs.rightStickClick = inputs.c_left;

    // Right hand bottom row
    outputs.a = inputs.b;
    outputs.b = inputs.x;
    outputs.triggerRDigital = inputs.up;
    outputs.triggerLDigital = inputs.z;

    // Right hand top row
    outputs.x = inputs.r;
    outputs.y = inputs.y;
    outputs.buttonR = inputs.a;
    outputs.buttonL = inputs.up;
}

void RivalsOfAether::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    outputs.leftStickX = 128;
    outputs.leftStickY = 128;
    outputs.rightStickX = 128;
    outputs.rightStickY = 128;
    outputs.triggerLAnalog = outputs.triggerLDigital ? 255 : 0;
    outputs.triggerRAnalog = outputs.triggerRDigital ? 255 : 0;
}

