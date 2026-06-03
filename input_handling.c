#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "chip8.h"

// Keypad mapping: Maps modern QWERTY keys to CHIP-8 Hex keys
// 1 2 3 4 -> 1 2 3 C
// Q W E R -> 4 5 6 D
// A S D F -> 7 8 9 E
// Z X C V -> A 0 B F
void process_input(struct chip8* console, SDL_Event* event) {
    if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
        uint8_t state = (event->type == SDL_KEYDOWN) ? 1 : 0;
        switch (event->key.keysym.sym) {
            case SDLK_x: console->keys[0] = state; break;
            case SDLK_1: console->keys[1] = state; break;
            case SDLK_2: console->keys[2] = state; break;
            case SDLK_3: console->keys[3] = state; break;
            case SDLK_q: console->keys[4] = state; break;
            case SDLK_w: console->keys[5] = state; break;
            case SDLK_e: console->keys[6] = state; break;
            case SDLK_a: console->keys[7] = state; break;
            case SDLK_s: console->keys[8] = state; break;
            case SDLK_d: console->keys[9] = state; break;
            case SDLK_z: console->keys[0xA] = state; break;
            case SDLK_c: console->keys[0xB] = state; break;
            case SDLK_4: console->keys[0xC] = state; break;
            case SDLK_r: console->keys[0xD] = state; break;
            case SDLK_f: console->keys[0xE] = state; break;
            case SDLK_v: console->keys[0xF] = state; break;
        }
    }
}
