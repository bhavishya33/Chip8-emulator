# Chip8 Emulator

This is a C project which emulates the 1970s Chip8 computer.

# libraries Utilised
  #include <stdio.h>  
  #include <stdint.h>   
  #include <stdlib.h>    
  #include <SDL2/SDL.h>    
  #include <stdbool.h>    

# Functions

1.chip8.h  --
struct chip8 {
    uint8_t  RAM[4096];      //RAM of 512 bytes or 4096 individual bits    
    uint8_t  V[16];          // register   
    uint16_t I;              // Index register  
    uint16_t PC;              // program counter  
    uint8_t  keys[16];        // keyboard inputs  
    uint16_t stack[16];       // stack   
    uint8_t  SP;               // stack pointer   
    uint8_t  monitor[64*32];    // 64 pixels wide and 32 pixels tall        
    uint8_t  delay_timer;           
    uint8_t  sound_timer;       
    };

2. emulator_setup -- the *console_init()* function initiaizes the console (a C structure which encapsulates all the hardware componenets as virtual variables) and                      sets it to zero.     
                     the *console_load()* function loads the ROM file of the desired game into the RAM of the console.    
                     the *console_fetch()* functions reads the RAM, creates opcode (combining two instructions from RAM), and returns it.    
   
3. emulator_decode_ins -- it takes opcode as a parameter, breaking it into 4 nibbles. thus, by analyzing each nibble via a series of switch statments, decodes the actual instructions.    

4. monitor -- this reads the sprite address and cordinates of sprites and loads it into the monitor array. it also deects collsions by ussing bitwise xor oprator.   

5. input_handling -- it handles and records the input from external device.   

6. main -- it it just an infinite loop which reads the RAM, performing instructions and displaying the game_screen 60 FPS.  


 # How to Run 

 simply run the makefile in the terminal   
 _________________________________________________________________
 | make                                                           |   
 |                                                                |   
 |________________________________________________________________|   


 now Run the game
 _________________________________________________________________
 | ./chip8 <file_name>                                            |   
 |                                                                |   
 |________________________________________________________________|   

 Fin....
 
