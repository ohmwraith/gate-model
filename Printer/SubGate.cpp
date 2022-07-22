#include "Gate.cpp"
#include "Car.cpp"

void Gate::subscribe() {
	car->freeGateEvent += gcnew Car::CarEventHandler(this, &Gate::close);
	parking->letCarIn += gcnew Parking::ParkingEventHandler(this, &Gate::open);
}