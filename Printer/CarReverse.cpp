//Ќаследуемый класс машины едущей с парковки
#include "Car.cpp"
#include "Parking.cpp"

ref class CarReverse : public Car
{
protected:

public:
	//ƒелегат событий машины едущей с парковки
	delegate void RevCarEventHandler();
	//—обытие машина создана
	static event RevCarEventHandler^ CREATED;
	CarReverse(Gate^ gt, Parking^ park, EcoGate^ ec, int qu) : Car(gt, park, ec, qu) {
		speed_y = -20;
		posY = -400;
		posX = 630;
		image->RotateFlip(RotateFlipType::Rotate180FlipX);
		target_Y = 1500;
		CREATED();
	}
	~CarReverse() {};
	//ѕереопределение метода движени€ через несуществующие ворота на полосе выезда
	public: void go_throw_gate() {

	}
	public: void update()
	{
		target_Y = 1500;
		speed_y = -20;
		posY -= speed_y;
	}

};