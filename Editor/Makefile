# This file will be auto genrated by the editor for linux build

# compilatin
CFLAGS = -std=c++20
LDFLAGS = -lglfw -lGLU -lGL -lsfml-graphics -lsfml-window -lsfml-system -lOpenCL -ljsoncpp -fcompare-debug-second -Wnarrowing -w -gdwarf-4 -fvar-tracking-assignments -O3 -shared-libgcc #dependencies

# Engine specific
ENGINE_PATH = ../Engine
ENGINE_HPP_FILES = $(ENGINE_PATH)/*.hpp $(ENGINE_PATH)/ThirdParty/SelbaWard/SelbaWard/*hpp
ENGINE_CPP_FILES = $(ENGINE_PATH)/*.cpp $(ENGINE_PATH)/ThirdParty/SelbaWard/SelbaWard/*cpp

#Project specific
PROJECT_HPP_FILES = Scripts/*.hpp 
PROJECT_CPP_FILES = Scripts/*.cpp 
PROJECT_NAME = Editor # orgy test project
BUILD_PATH = ./Build

Build: $(ENGINE_HPP_FILES) $(ENGINE_CPP_FILES) $(PROJECT_HPP_FILES) $(PROJECT_CPP_FILES)
	rm -r $(BUILD_PATH) 
	mkdir -p $(BUILD_PATH)
	mkdir -p $(BUILD_PATH)/logs
	touch $(BUILD_PATH)/logs/logfile.txt
	g++ $(CFLAGS) -o $(BUILD_PATH)/$(PROJECT_NAME) $(PROJECT_CPP_FILES) $(ENGINE_CPP_FILES) $(LDFLAGS)
	cp -r $(ENGINE_PATH)/EngineAssets $(BUILD_PATH)/EngineAssets
	cp -r ./GameAssets $(BUILD_PATH)/GameAssets