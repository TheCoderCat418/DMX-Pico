#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

// USB register definitions from pico-sdk
#include "hardware/regs/usb.h"
// USB hardware struct definitions from pico-sdk
#include "hardware/structs/usb.h"
// For interrupt enable and numbers
#include "hardware/irq.h"
// For resetting the USB controller
#include "hardware/resets.h"

#include "dmx.pio.h"

// START USB TESTING
void usb_main(){
    // Reset the USB Controller
    reset_unreset_block_num_wait_blocking(RESET_USBCTRL);




}

// END USB TESTING
















void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq) {
    dmx_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);
}

int main()
{
    stdio_init_all();
    sleep_ms(4000);

    PIO pio = pio0;
    uint offset = pio_add_program(pio, &dmx_program);
    printf("VER:0.0 Loaded program at %d\n", offset);
    
    blink_pin_forever(pio, 0, offset, 14, 3);
    pio_sm_put(pio, 0, 0b10000001010000100010010000011000);

    for(int i = 0; i< 128; i++) {
        pio_sm_put_blocking(pio, 0, 0b10000001010000100010010000011000);
    }
}
