#include "chip8.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("Usage: ./chip8_emu <ROM_FILE>\n");
        return 1;
    }
    
    struct chip8 console;
    console_init(&console);
    
    
    uint8_t fontset[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    for (int i = 0; i < 80; i++) {
        console.RAM[0x050 + i] = fontset[i];
    }

    
    console_load(argv[1], &console);

    // 2. Initialize the OS and Graphics (SDL2)
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    
    SDL_Window* window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);

    
    bool running = true;
    SDL_Event event;
    uint32_t video_buffer[64 * 32]; 

    while (running) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            process_input(&console, &event);
        }

        for (int i = 0; i < 10; i++) {
            uint16_t opcode = console_fetch(&console);
            console_decode(&console, opcode);
        }

        
        if (console.delay_timer > 0) console.delay_timer--;
        if (console.sound_timer > 0) console.sound_timer--;

        
        for (int i = 0; i < (64 * 32); i++) {
            video_buffer[i] = (console.monitor[i] == 1) ? 0xFFFFFFFF : 0x000000FF; 
        }

    
        SDL_UpdateTexture(texture, NULL, video_buffer, 64 * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        
        SDL_Delay(16);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}