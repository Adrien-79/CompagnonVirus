#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>

#include <SDL2/SDL.h>
//#include <SFML/Graphics.hpp>
#include "MBC.h"

class Z80_Gameboy;
class PPU_Gameboy;
class Timer_Gameboy;

class Bus
{
private:
    Z80_Gameboy& cpu;
    PPU_Gameboy& ppu;
    Timer_Gameboy& tim;

    uint8_t if_reg = 0;
    uint8_t ie = 0;
    uint8_t controller_reg = 0x83;
    enum Controller_Key {Cont_RIGHT,Cont_LEFT,Cont_UP,Cont_DOWN, Cont_A,Cont_B,Cont_SELECT,Cont_START,Cont_KEYNB};
    enum Controller_Signal {Sig_DOWN=0,Sig_UP=1};
    Controller_Signal controller_keys_state[Cont_KEYNB];

    uint8_t sb,sc;
    std::string msg = "";

    bool stopMode = false;
    uint8_t ram[0x10000]; //TODO: allocate less memory as most of it isn't used
    SDL_Renderer *ren;
    SDL_Window *win;
    bool blockMemoryWrite = false;

    MBC * cartridge = nullptr;

public:
    Bus(Z80_Gameboy& c,PPU_Gameboy& p,Timer_Gameboy& t);
    ~Bus();

    void loadCartridge(std::string path);

    void write(uint16_t adr,uint8_t data);
    uint8_t read(uint16_t adr);

    void triggerStopMode(bool stop);

    void run();
    std::string showMemory(uint16_t src,uint16_t dst)
    {
        std::stringstream ss;
        ss << std::showbase << std::hex;
        ss << "Memory Range from "<<src<<" to "<<dst<< "\nAdress: value\n";
        for(uint16_t i = src; i <= dst; i++)
        {
            ss << i << ": " << (int)ram[i]<<"\n";
        }
        return ss.str();
    }

    void disassemble();

    

    SDL_Renderer *getSDLRenderer()
    {
        return ren;
    }
};

#endif // BUS_H
