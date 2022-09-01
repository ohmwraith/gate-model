#include "Car.cpp"

void EcoGate::subscribe() {
	car->freeLeavingGateEvent += gcnew Car::CarEventHandler(this, &EcoGate::close);
}