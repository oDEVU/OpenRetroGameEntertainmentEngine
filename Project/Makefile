CFLAGS = -std=c++20
LDFLAGS = -lglfw -lsfml-graphics -lsfml-window -lsfml-system

VulkanApp: *.cpp ../Engine/*.hpp ../Engine/SelbaWard/*hpp ../Engine/SelbaWard/*cpp
	g++ $(CFLAGS) -o app *.cpp ../Engine/SelbaWard/*cpp $(LDFLAGS)