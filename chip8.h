#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

struct chip8 {
    uint8_t  RAM[4096];      //RAM of 512 bytes
    uint8_t  V[16];              
    uint16_t I;                 
    uint16_t PC;      
    uint8_t  keys[16];      
    uint16_t stack[16];     
    uint8_t  SP;         
    uint8_t  monitor[64*32];    // 64 pixels wide and 32 pixels tall    
    uint8_t  delay_timer;    
    uint8_t  sound_timer;    
};

void process_input(struct chip8* console, SDL_Event* event);
void display(struct chip8* console, uint8_t N2, uint8_t N3, uint8_t N4);
void console_decode(struct chip8* console, uint16_t opcode);
uint16_t console_fetch(struct chip8* console);
void console_load(char* cartridge_title, struct chip8* console);
void CLS(struct chip8* console);
void console_init(struct chip8* console);
void process_input(struct chip8* console, SDL_Event* event);
