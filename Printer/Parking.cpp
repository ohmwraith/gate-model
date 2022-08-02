//Класс, отвечающий за парковку

#pragma once
#include <iostream>
#include "Time.cpp"
#include "Gate.cpp"

using namespace System::Drawing;
ref class Gate;
ref class Car;
ref class Parking
{
protected:
	array<bool>^ places_array;
	Time^ time;
	Gate^ gate;
	Car^ car;
	bool close;
	int total, free;
public:
	//Делегат события парковки
	delegate void ParkingEventHandler();
	//Событие машине разрешен въезд
	static event ParkingEventHandler^ letCarIn;
	static event ParkingEventHandler^ letCarLeave;
	//Свойства
	property bool p_avaliable {
		bool get() {
			bool answ;
			free > 0 ? answ = true : answ = false;
			return answ;
		}
	}
	property int p_total {
		int get() { return total; }
		void set(int value) { total = value; }
	}
	property int p_free {
		int get() { return free; }
		void set(int value) { free = value; }
	}
	property int p_occupied {
		int get() { return total - p_free; }
	}
	//Конструктор и деструктор
	Parking(int tot, int fr, Time^ t, Gate^ gt)
	{
		total = tot;
		time = t;
		gate = gt;
		free = fr;
		subscribe();
	};
	~Parking() {
		this->letCarIn -= gcnew Parking::ParkingEventHandler(gate, &Gate::open);
	};
	void subscribe();
	//Метод, вызывающий событие, разрешающее машине проехать
	void send_car_enter_event() {
		if (this->p_avaliable) {
			free--;
			letCarIn();
		}
	}
	void send_car_leave_event() {
		letCarLeave();
	}
};
