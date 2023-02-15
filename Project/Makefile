CFLAGS = -std=c++20
LDFLAGS = -lglfw -lsfml-graphics -lsfml-window -lsfml-system -lOpenCL -ljsoncpp -fcompare-debug-second -Wnarrowing

VulkanApp: *.cpp ../Engine/*.hpp ../Engine/ThirdParty/SelbaWard/SelbaWard/*hpp ../Engine/ThirdParty/SelbaWard/SelbaWard/*cpp
	g++ $(CFLAGS) -o app *.cpp ../Engine/ThirdParty/SelbaWard/SelbaWard/*cpp $(LDFLAGS)