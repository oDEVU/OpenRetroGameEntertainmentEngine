CFLAGS = -std=c++20
LDFLAGS = -lglfw -lsfml-graphics -lsfml-window -lsfml-system -lOpenCL -ljsoncpp -fcompare-debug-second -Wnarrowing -w -O3
HPP_FILES = Scripts/*.hpp ../Engine/*.hpp ../Engine/ThirdParty/SelbaWard/SelbaWard/*hpp
CPP_FILES = Scripts/*.cpp ../Engine/*.cpp ../Engine/ThirdParty/SelbaWard/SelbaWard/*cpp
PROJECT_NAME = game_name
BUILD_PATH = ./Build

VulkanApp: $(HPP_FILES) $(CPP_FILES)
	rm -r $(BUILD_PATH) 
	mkdir -p $(BUILD_PATH)
	mkdir -p $(BUILD_PATH)/logs
	touch $(BUILD_PATH)/logs/logfile.txt
	g++ $(CFLAGS) -o $(BUILD_PATH)/$(PROJECT_NAME) $(CPP_FILES) $(LDFLAGS)
	cp -r ./EngineAssets $(BUILD_PATH)/EngineAssets
	cp -r ./GameAssets $(BUILD_PATH)/GameAssets