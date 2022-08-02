#pragma once

//#include "structures.hpp"

namespace source {

void clear_source_code() {
    system("find -L ../packaged/ -name \"*.cpp\" -delete");
    system("find -L ../packaged/ -name \"*.hpp\" -delete");
    system("find -L ../packaged/ -name \"*.c\" -delete");
    system("find -L ../packaged/ -name \"*.h\" -delete");
    system("find -L ../packaged/ -name \"*.sh\" -delete");
    system("find -L ../packaged/ -name \"*.py\" -delete");
    system("find -L ../packaged/ -name \"*.cs\" -delete");
}

// Windows cleaner is not working at the time :C [as everything windows related XD]

void clear_source_code_win() {
    system("rm ../packaged/game/*.cpp");
    system("rm ../packaged/game/*.hpp");
    system("rm ../packaged/game/*.h");
    system("rm ../packaged/game/*.c");
    system("rm ../packaged/sf_engine/*.cpp");
    system("rm ../packaged/sf_engine/*.hpp");
    system("rm ../packaged/sf_engine/*.h");
    system("rm ../packaged/sf_engine/*.c");
    system("rm ../packaged/sf_engine/*.sh");
}

}