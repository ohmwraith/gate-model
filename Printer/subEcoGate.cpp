#include "Car.cpp"

void EcoGate::subscribe() {
	car->freeLeavingGateEvent += gcnew Car::CarLeaveHandler(this, &EcoGate::close);
}