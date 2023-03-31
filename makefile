build: 
	g++ -std=c++20 AirportSimulation/*.cpp -o dist/AirportSimulation.o
build-web:
	emcc -lembind AirportSimulation/Aircraft.cpp AirportSimulation/Runway.cpp AirportSimulation/Statistics.cpp AirportSimulation/Master.cpp -o dist/AirportSimulation.wasm -s ALLOW_MEMORY_GROWTH -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap']