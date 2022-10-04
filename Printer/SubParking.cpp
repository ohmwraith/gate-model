#include "Parking.cpp"
#include "Car.cpp"
#include "Gate.cpp"

void Parking::subscribe() {
	//������ �������� �������, ������� �������� ������� � ����� �������� send_car_enter_event()
	car->onGateEvent += gcnew Car::CarEventHandler(this, &Parking::send_car_enter_event);
	car->onLeavingGateEvent += gcnew Car::CarLeaveHandler(this, &Parking::send_car_leave_event);
}