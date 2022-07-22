// Класс шлагбаума
#pragma once
#include <iostream>
using namespace System::Drawing;
ref class Car;
ref class Parking;
ref class Gate
{
protected:
	bool opened;
	int posX, posY;
	Bitmap^ image,^ gate_closed_image,^ gate_opened_image;
	Car^ car;
	Parking^ parking;
public:
	//Делегат событий шлагбаума
	delegate void GateEventHandler();
	delegate void GateOpenHandler(int provided_place);
	//Событие шлагбаум открыт
	static event GateOpenHandler^ openEvent;
	//Событие шлагбаум закрыт
	static event GateEventHandler^ closeEvent;
	//Свойства
	property Bitmap^ p_image {
		Bitmap^ get() { return image; }
		void set(Bitmap^ value) { image = value; }
	}
	property int p_posX {
		int get() { return posX; }
		void set(int value) { posX = value; }
	}
	property int p_posY {
		int get() { return posY; }
		void set(int value) { posY = value; }
	}
	property bool p_open {
		bool get() { return opened; }
		void set(bool value) { opened = value; }
	}
	void subscribe();
	//Конструктор и деструктор
	Gate()
	{
		posX = 650;
		posY = 450;
		opened = false;
		gate_closed_image = gcnew Bitmap(".\\assets\\gate_closed.png");
		gate_opened_image = gcnew Bitmap(".\\assets\\gate_opened.png");
		subscribe();
	};
	~Gate() {};
	//Метод открытия ворот
	void open(int provide_place) {
		opened = true;
		openEvent(provide_place);
	}
	//Метод закрытия ворот
	void close() {
		opened = false;
	}
	//Метод изменения состояния ворот
	void toggle() {
		opened ? opened = false : opened = true;
	}
	//Метод обновления состояния объекта
	public: void update()
	{
		if (opened) image = gate_opened_image;
		else image = gate_closed_image;
	}
};