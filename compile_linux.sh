 #!/usr/bin/bash
echo "g++ -Wall -std=c++11 -lpthread board.cpp core_simulation.cpp mydevices.cpp sketch_ino.cpp -o arduino"
g++ -Wall -std=c++11 -pthread ./src/board.cpp ./src/core_simulation.cpp ./src/mydevices.cpp ./src/sketch_ino.cpp -o arduino -lsfml-audio -lsfml-window -lsfml-system -lopenal
g++ -Wall -std=c++11 ./script_test_instrument.cpp -o scrip_instrument
