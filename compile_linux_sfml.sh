 #!/usr/bin/bash
echo "g++ -c test_sfml.cpp"
g++ -c test_sfml.cpp
g++ test_sfml.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
