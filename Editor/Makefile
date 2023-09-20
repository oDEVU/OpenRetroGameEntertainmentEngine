# compilatin
CFLAGS = -std=c++20
LDFLAGS = -lglfw -lGLU -lGL -lsfml-graphics -lsfml-window -lsfml-system -lOpenCL -ljsoncpp -fcompare-debug-second -Wnarrowing -w -gdwarf-3 -O3 -shared-libgcc #dependencies

# Engine specific
ENGINE_PATH = ../Engine
ENGINE_HPP_FILES = $(ENGINE_PATH)/*.hpp $(ENGINE_PATH)/ThirdParty/SelbaWard/SelbaWard/*hpp
ENGINE_CPP_FILES = $(ENGINE_PATH)/*.cpp $(ENGINE_PATH)/ThirdParty/SelbaWard/SelbaWard/*cpp

#Project specific
#EDITOR_HPP_FILES = *.hpp 
EDITOR_CPP_FILES = *.cpp 
BUILD_PATH = ./Build

Build: $(ENGINE_HPP_FILES) $(ENGINE_CPP_FILES) $(EDITOR_HPP_FILES) $(EDITOR_CPP_FILES)
	mkdir -p $(BUILD_PATH)/logs
	touch $(BUILD_PATH)/logs/logfile.txt
	cp -r $(ENGINE_PATH)/EngineAssets $(BUILD_PATH)/EngineAssets
	g++ $(CFLAGS) -o $(BUILD_PATH)/editor $(EDITOR_CPP_FILES) $(ENGINE_CPP_FILES) $(LDFLAGS)