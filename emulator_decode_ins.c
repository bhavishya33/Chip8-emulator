#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "chip8.h"


void console_decode(struct chip8* console, uint16_t opcode){
    uint8_t N1 = opcode >> 12;
    uint8_t N2 = opcode >> 8 & 0x0F;
    uint8_t N3 = opcode >> 4 & 0x0F;
    uint8_t N4 = opcode & 0x0F;
    uint8_t NN = opcode & 0x00FF;
    uint16_t NNN = opcode & 0x0FFF;

    switch(N1){
        case 0x0:
            switch(NNN){
                case 0x00E0:
                    // Clear screen;
                    CLS(console);
                    break;

                case 0x00EE:
                    console->SP -= 1;
                    console->PC = (console->stack)[console->SP];
                    break;

                default:
                    // other cases;
                    break;
            }
        break;


        case 0x1:
            console->PC = NNN;
            break;

        case 0x2:
            (console->stack)[console->SP] = console->PC;
            console->SP ++;
            console->PC = NNN;
            break;

        case 0x3:
            if(console->V[N2] == NN){
                console->PC += 2;
            }
            break;


        case 0x4:
            if(console->V[N2] != NN){
                console->PC += 2;
            }
            break;

        case 0x5:
            if(console->V[N2] == console->V[N3]){
                console->PC += 2;
            }
            break;
        

        case 0x6:
            (console->V)[N2] = NN;
            break;


        case 0x7:
            (console->V)[N2] += NN;
            break;

        
        case 0x8:
            switch(N4){
                case 0x0:
                    // set vx = vy;
                    (console->V)[N2] = (console->V)[N3];
                    break;

                case 0x1:
                    // set vx = vx or vy;
                    (console->V)[N2] = (console->V)[N2] | (console->V)[N3];
                    break;

                case 0x2:
                    // set vx = vx and vy;
                    (console->V)[N2] = (console->V)[N2] & (console->V)[N3];
                    break;

                case 0x3:
                    // set vx = vx xor vy;
                    (console->V)[N2] = (console->V)[N2] ^ (console->V)[N3];
                    break;

                case 0x4:{
                    // set vx = vx + vy , vf = carry;
                    uint16_t temp_byte = (console->V)[N2] + (console->V)[N3];
                    (console->V)[N2] =  temp_byte & 0xFF ;
                    (console->V)[0xF] = temp_byte >>  8 ;                                                       
                    break;
                }


                case 0x5:{
                    // set vx = vx - vy , vf = not borrow;
                    uint8_t F_redirect = ((console->V)[N2] >= (console->V)[N3]) ? 1:0 ;
                    (console->V)[N2] = (console->V)[N2] - (console->V)[N3];
                    (console->V)[0xF] = F_redirect;
                    break;
                }

                case 0x6:
                    // set vx = vx >> 1 , vf = LSB;
                    (console->V)[0xF] = (console->V)[N2] & 0x01;
                    (console->V)[N2] = (console->V)[N2] >> 1;
                    break;

                case 0x7:{
                    // set vx = vy - vx , vf = not borrow;
                    uint8_t F_redirect = ((console->V)[N3] >= (console->V)[N2]) ? 1:0 ;
                    (console->V)[N2] = (console->V)[N3] - (console->V)[N2];
                    (console->V)[0xF] = F_redirect;
                    break;
                }

                case 0xE:
                    // set vx = vx << 1 , vf = MSB;
                    (console->V)[0xF] = ((console->V)[N2] & 0x80) >> 7;
                    (console->V)[N2] = (console->V)[N2] << 1 ;
                    break;

                default:
                    break;

            }
            break;

        
        case 0x9:
            if(console->V[N2] != console->V[N3]){
                console->PC += 2;
            }
            break;


        case 0xA:
            console->I = NNN;
            break;


        case 0xB:
            console->PC = NNN + (console->V)[0];
            break;

        case 0xC:{
            uint8_t random_number = rand() % 256;
            console->V[N2] = random_number & NN;
            break;
        }


        case 0xD:
            display(console,N2,N3,N4);
            break;

        case 0xE:{
            switch(NN){

                case 0x9E:{
                    uint8_t temp_key = console->V[N2];
                    if(temp_key <= 0xF){
                        if(console->keys[temp_key] == 1){
                            console->PC += 2;
                        }
                    }
                    break;
                }
                case 0xA1:{
                uint8_t temp_key = console->V[N2];
                    if(temp_key <= 0xF){
                        if(console->keys[temp_key] == 0){
                            console->PC += 2;
                        }
                    }
                    break;
                }
                default:
                    break;
            }
            break;
            
        }
        case 0xF:{
    switch(NN){

        case 0x07:
        console->V[N2] = console->delay_timer;
            break;

        case 0x15:
            console->delay_timer = console->V[N2];
            break;

        case 0x18:
            console->sound_timer = console->V[N2];
            break;

        case 0x1E:
            console->I += console->V[N2];
            break;

        case 0x65:
            for(int i=0;i<=N2;i++){
                console->V[i] = console->RAM[console->I + i];
            }
            break;

        case 0x55:
            for(int i=0;i<=N2;i++){
                console->RAM[console->I + i] = console->V[i];
            }
            break;

        case 0x33: {
             uint8_t num = console->V[N2];
             console->RAM[console->I]     = num / 100;           // Hundreds
             console->RAM[console->I + 1] = (num / 10) % 10;     // Tens
             console->RAM[console->I + 2] = num % 10;            // Ones
            break;
}
        case 0x29:
            console->I = 0x050 + (console->V[N2] * 5);
            break;

        case 0x0A:{
            bool key_pressed = false;
            for(int i=0;i<16;i++){
                if(console->keys[i] == 1){
                    console->V[N2] = i;
                    key_pressed = true;
                    break;
                }
            }
            if(!key_pressed){
                console->PC -= 2;}
        
            break;
            }

            default:
                break;

    }
}
break;

        default:
            printf("Unknown Instruction\n");
            exit(1);
            
    }
}