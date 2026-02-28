CXX = g++
CXXFLAGS = -Wall -std=c++11 -g -I. -IEventos
TARGET = particle_sim.exe

# Archivos fuente
SRCS = main.cpp particle.cpp electron.cpp hit.cpp Eventos/event_generator.cpp
OBJS = main.o particle.o electron.o hit.o event_generator.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar archivos de la raíz
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla específica para event_generator.cpp
event_generator.o: Eventos/event_generator.cpp
	$(CXX) $(CXXFLAGS) -c Eventos/event_generator.cpp -o event_generator.o

# NO necesitas reglas de dependencia explícitas con -I.

clean:
	del /Q $(OBJS) $(TARGET) 2>nul || echo Ignorando error de clean

run: all
	$(TARGET)

.PHONY: all clean run