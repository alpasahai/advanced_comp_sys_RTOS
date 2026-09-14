#include "inc/rtos.h"

// Remember that these tasks can not be allowed to complete!
//          Use an infinite loop so that the function never exits. 
const uint8_t sev_seg[18] = {
    0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, // 0-9
    0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47,
    0x80, //DP 
    0x00 //OFF
};

/* ===========================================================================
 * Blinky - flashes the onboard LED 'count' times (ON 2s / OFF 2s per
 * flash), then leaves it off.
 * ===========================================================================
 */
void blink(int numflash)
{
    //Turning on DIN (PIN 25) and setting output
    gpio_init(25); 
    gpio_set_dir(25, GPIO_OUT);

    //Alpie Notes: Double check if the delay messes with the scheduler LATEr
    for (int i = 0; i < numflash; i++) {
        gpio_put(25, 1); 
        delay(500);    
        gpio_put(25, 0); 
        delay(500); 
    }
    gpio_put(25, 0);

    while (1) {
        //making sure task is idle afterwards
    }
}

/* ===========================================================================
 * Counter - continuously counts 00..99, updating every 0.5 s. Tens digit
 * at 'pos', units digit at 'pos + 1'.
 * ===========================================================================
 */
void count(int pos)
{
   int value = 0;
   while(1){
    display_buffer[pos] = sev_seg[value/10]; //tens
    display_buffer[pos + 1] = sev_seg[value%10]; //units

    delay(500);
    value = (value + 1) % 100;
   }
}

/* ===========================================================================
 * Flasher - flashes the decimal point at 'pos' at 2 Hz (0.25 s on,
 * 0.25 s off).
 * ===========================================================================
 */
void flash( int pos)
{
   
}

/* ===========================================================================
 * Hexer - displays a ping-pong hex count at 'pos': F,E,...,0,1,...,F,
 * repeating indefinitely, changing once per second.
 * ===========================================================================
 */
void hexer( int pos )
{
   
}

/* ===========================================================================
 * Splat - "chases" the segments of digit 'pos' on one at a time
 * (A, A+B, A+B+C, ... , all 8 including DP), then removes them one at a
 * time in reverse (A..G, A..F, ... , OFF), repeating continuously. Each
 * step is held for 0.25 s.
 * ===========================================================================
 */
void splat(int pos)
{
    
}

