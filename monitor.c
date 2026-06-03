#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "chip8.h"


void CLS(struct chip8* console){
    for(int i=0;i<64*32;i++){
        console->monitor[i] = 0;
    }
}


void display(struct chip8* console, uint8_t N2, uint8_t N3, uint8_t N4){
    // Reset collision flag
    uint8_t F_redirect = 0;
    
    // Wrap starting coordinates
    uint8_t x_cord = (console->V)[N2] % 64;
    uint8_t y_cord = (console->V)[N3] % 32;
    uint8_t elevation = N4;
    uint16_t sprite_address = console->I; // Fixed 'comsole' typo

    // Lookup table for bit extraction
    uint8_t bit_ray[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

    int c = 0;
    
    for (int i = 0; i < elevation; i++) {
        // Vertical Clipping Wall: Stop drawing if we hit the floor
        if (y_cord + i >= 32) {
            break;  
        }

        for (int j = 0; j < 8; j++) {
            // Horizontal Clipping Wall: Stop drawing if we hit the right edge
            if (x_cord + j >= 64) {
                break; 
            }

            uint8_t active_bit = bit_ray[j];

            // Step 1: Extract and normalize the bit to exactly 1 or 0
            uint8_t sprite_pixel = !!(console->RAM[sprite_address + c] & active_bit);

            // Step 2: The Efficiency Gate (Only work if pixel is ON)
            if (sprite_pixel == 1) {
                
                // Calculate flat array index
                int screen_index = ((y_cord + i) * 64) + x_cord + j;

                // Step 3: Collision Check (Is the screen already 1?)
                if (console->monitor[screen_index] == 1) {
                    F_redirect = 1; 
                }

                // Step 4: Toggle the screen pixel using XOR
                console->monitor[screen_index] ^= 1;
            }
        }
        
        c++;
    }
    
    // Update the VF hardware register AFTER drawing finishes
    console->V[0xF] = F_redirect;
}
