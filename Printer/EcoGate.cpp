#include "Gate.cpp"
#include "Parking.cpp"

ref class EcoGate : public Gate 
{
private:
public:
	delegate void EcoGateEventHandler();
	static event EcoGateEventHandler^ openGateForLeaving;
	EcoGate()
	{
		posX = 850;
		posY = 450;
		opened = false;
		gate_closed_image = gcnew Bitmap(".\\assets\\eco_gate_closed.png");
		gate_opened_image = gcnew Bitmap(".\\assets\\eco_gate_opened.png");
		image = gate_closed_image;
		parking->letCarLeave += gcnew Parking::ParkingEventHandler(this, &EcoGate::open);
		parking->letCarIn -= gcnew Parking::ParkingEventHandler(this, &EcoGate::open);
	};
	~EcoGate() {};


};
