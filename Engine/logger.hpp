#pragma once

#include <iostream>
#include <fstream>

#include "pathhandler.hpp"

std::string global_path = orgy::getExecutablePath().substr(0, orgy::getExecutablePath().find_last_of("\\/")+1);

void stringLog(std::string text, bool printToTerminal){

    std::ofstream logfile( global_path + "logs/logfile.txt", std::ios::app);

    logfile << text + "\n";

    if(printToTerminal){
        std::cout << text << std::endl;
    }
}