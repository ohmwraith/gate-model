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
	int total;
public:
	//Делегат события парковки
	delegate void ParkingEventHandler(int parking_number);
	//Событие машине разрешен въезд
	static event ParkingEventHandler^ letCarIn;
	static event ParkingEventHandler^ letCarLeave;
	//Свойства
	property bool p_avaliable {
		bool get() {
			for (int i = 0; i < places_array->Length; i++) {
				if (places_array[i] == true) return places_array[i] * !time->p_night;
			}
			return false; 
		}
	}
	property int p_total {
		int get() { return total; }
		void set(int value) { total = value; }
	}
	property int p_free {
		int get() { 
			int count = 0;
			for (int i = 1; i < places_array->Length; i++) {
				if (places_array[i] == true) count++;
			} return count;
		}
	}
	property int p_occupied {
		int get() { return total - p_free; }
	}
	property bool p_first {
		bool get() {
			return places_array[1];
		}
	}
	//Конструктор и деструктор
	Parking(int tot, Time^ t, Gate^ gt)
	{
		total = tot;
		time = t;
		gate = gt;
		places_array = gcnew array<bool>(total);
		for (int i = 0; i < places_array->Length; i++) places_array[i] = true;
		places_array[0] = false;
		subscribe();
	};
	~Parking() {
		this->letCarIn -= gcnew Parking::ParkingEventHandler(gate, &Gate::open);
	};
	void subscribe();
	//Метод, вызывающий событие, разрешающее машине проехать
	void send_car_enter_event() {
		if (this->p_avaliable) {
			int i = 0;
			while (places_array[i] != true) i++;
			letCarIn(i);
			places_array[i] = false;
		}
	}
	void send_car_leave_event(int provided_place) {
		letCarLeave(provided_place);
		//places_array[provided_place] = true;

	}
	void release_places(int provided_place) {
		
	}
};
