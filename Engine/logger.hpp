#pragma once

#include <iostream>
#include <fstream>

#include "pathhandler.hpp"

std::string global_path = orgee::getExecutablePath().substr(0, orgee::getExecutablePath().find_last_of("\\/")+1);

void consoleLog(std::string text, bool printToTerminal){

    std::ofstream logfile( global_path + "logs/logfile.txt", std::ios::app);

    logfile << text + "\n";

    if(printToTerminal){
        std::cout << text << std::endl;
    }
}