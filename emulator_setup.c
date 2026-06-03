#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "chip8.h"


void console_init(struct chip8* console){
        for(int i=0;i<4096;i++){
            (console->RAM)[i] = 0;
        }
        for(int i=0;i<16;i++){
            (console->V)[i] = 0;
            (console->stack)[i] = 0;
        }
        for(int i=0;i<64*32;i++){
            (console->monitor)[i] = 0;
        }
        console->PC = 0x200;
        console->SP = 0; 
        console->I = 0;
        console->sound_timer = 0;
        console->delay_timer = 0;
}


void console_load(char* cartridge_title, struct chip8* console){
    FILE* cartridge = fopen(cartridge_title,"rb");
    fseek(cartridge,0,SEEK_END);
    unsigned long cartridge_size = ftell(cartridge);
    rewind(cartridge);

    if (cartridge_size > (4096 - 512)) {
        printf("ROM is too large to fit in memory!\n");
        fclose(cartridge);
        exit(1);
    }

    size_t bytes_read = fread(console->RAM + 0x200,1,cartridge_size,cartridge);
    fclose(cartridge);
    }


uint16_t console_fetch(struct chip8* console){
    uint16_t opcode = (console->RAM[console->PC]) << 8  | (console->RAM)[console->PC +1];
    console->PC += 2;
    
    return opcode;
}