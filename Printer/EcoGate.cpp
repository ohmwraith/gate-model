#include "Gate.cpp"
#include "Parking.cpp"
#include "Car.cpp"

ref class EcoGate : public Gate 
{
private:
public:
	bool eco_opened;
	delegate void EcoGateEventHandler();
	static event EcoGateEventHandler^ openGateForLeaving;
	EcoGate()
	{
		posX = 850;
		posY = 450;
		eco_opened = false;
		gate_closed_image = gcnew Bitmap(".\\assets\\eco_gate_closed.png");
		gate_opened_image = gcnew Bitmap(".\\assets\\eco_gate_opened.png");
		image = gate_closed_image;
		parking->letCarLeave += gcnew Parking::ParkingEventHandler(this, &EcoGate::open);
		parking->letCarIn -= gcnew Parking::ParkingEventHandler(this, &EcoGate::open);
		car->freeLeavingGateEvent += gcnew Car::CarLeaveHandler(this, &EcoGate::close);
	};
	~EcoGate() {};
	void open() {
		eco_opened = true;
		openGateForLeaving();
	}
	void close() {
		eco_opened = false;
	}
	void update()
	{
		if (eco_opened) image = gate_opened_image;
		else image = gate_closed_image;
	}

};

