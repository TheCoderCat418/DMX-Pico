#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"

#include "dmx.pio.h"

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

    while (true) {
        printf("%d", pio_sm_get_tx_fifo_level(pio, 0));
        sleep_ms(1000);
    }
}
