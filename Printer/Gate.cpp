// ����� ���������
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
	//������� ������� ���������
	delegate void GateEventHandler();
	delegate void GateOpenHandler(int provided_place);
	//������� �������� ������
	static event GateOpenHandler^ openEvent;
	//������� �������� ������
	static event GateEventHandler^ closeEvent;
	//��������
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
	//����������� � ����������
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
	//����� �������� �����
	void open(int provide_place) {
		opened = true;
		openEvent(provide_place);
	}
	//����� �������� �����
	void close() {
		opened = false;
	}
	//����� ��������� ��������� �����
	void toggle() {
		opened ? opened = false : opened = true;
	}
	//����� ���������� ��������� �������
	public: void update()
	{
		if (opened) image = gate_opened_image;
		else image = gate_closed_image;
	}
};