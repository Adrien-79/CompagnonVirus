#include <iostream>
#include "Bus.h"
#include "Z80_Gameboy.h"
#include "PPU_Gameboy.h"
#include "Timer_Gameboy.h"

#include <time.h>

int main(int argc, char **argv)
{
    if(argc <= 1)
    {
        std::cout<<"Syntax error, please use : "<<argv[0]<<" RomName.gb"<<std::endl;
        return -1;
    }
    
    std::string romPath = "";        
    for(int i = 1; i < argc; i++){
        if(i != 1)
            romPath += " ";
        romPath+=argv[i];
    }
        

    //srand(time(NULL));
    Z80_Gameboy cpu;
    PPU_Gameboy ppu;
    Timer_Gameboy tim;
    //cpu.disassemble = true;
    Bus gb(cpu,ppu,tim);
    
    gb.loadCartridge(romPath);


    //gb.disassemble();
    std::cout << std::hex;

    gb.run();
    //std::cout << cpu.assembled;

    return 0;
}
