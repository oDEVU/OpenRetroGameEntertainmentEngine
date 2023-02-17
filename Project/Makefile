CFLAGS = -std=c++20
LDFLAGS = -lglfw -lsfml-graphics -lsfml-window -lsfml-system -lOpenCL -ljsoncpp -fcompare-debug-second -Wnarrowing -w
HPP_FILES = ../Engine/*.hpp ../Engine/ThirdParty/SelbaWard/SelbaWard/*hpp
CPP_FILES = *.cpp ../Engine/ThirdParty/SelbaWard/SelbaWard/*cpp

VulkanApp: $(HPP_FILES) $(CPP_FILES)
	g++ $(CFLAGS) -o app $(CPP_FILES) $(LDFLAGS)