//����� �����

#pragma once
#include <iostream>
#include "Gate.cpp"
#include "EcoGate.cpp"
#include "Parking.cpp"

using namespace System::Drawing;
using namespace System::Collections::Generic;
int getRandomNumber(int min, int max);

ref class Car
{
protected:
	// ���������� � ������������� ����������
	bool flagOnGate = false, flagAfterGate = false, rotate_needed = true, inactive_status = false, provided_place_received = false, leaving_car = false, parked = false, flagLeaveWaiting = false;
	int posX, posY, scale, width, height, speed_y, speed_x, random_color_id;
	int goToGate_target, goThrowGate_target, goToPark_target, status, target_X, target_Y, go_to_park_frame, go_from_park_frame, provided_place, last_on_gate_req;
	array<int>^ road_array_x;
	array<int>^ road_array_y;
	Bitmap^ image;
	Gate^ gate;
	EcoGate^ ecogate;
	Parking^ parking;
	List <Car^>^ neighbours;
	Time^ time_;
	int car_id,queue;
public:
	//������� ������� ������ ������
	delegate void CarEventHandler();
	//������� ������� ������� � ��������
	delegate void CarLeaveHandler();
	//������� ������ � �����
	static event CarEventHandler^ onGateEvent;
	//������� ������ � ����� �� ������
	static event CarLeaveHandler^ onLeavingGateEvent;
	//������� ������ �������� � ������
	static event CarEventHandler^ freeGateEvent;
	//������� ������ �������� � ������ �� ������
	static event CarLeaveHandler^ freeLeavingGateEvent;
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
	property int p_scale {
		int get() { return scale; }
		void set(int value) { scale = value; }
	}
	property int p_width {
		int get() { return width; }
		void set(int value) { width = value; }
	}
	property int p_height {
		int get() { return height; }
		void set(int value) { height = value; }
	}
	property int p_target_Y {
		int get() { return target_Y; }
		void set(int value) { target_Y = value; }
	}
	property int p_target_X {
		int get() { return target_X; }
		void set(int value) { target_X = value; }
	}
	property int p_speed_x {
		int get() { return speed_x; }
		void set(int value) { speed_x = value; }
	}
	property int p_speed_y {
		int get() { return speed_y; }
		void set(int value) { speed_y = value; }
	}
	property bool p_parked {
		bool get() { return parked; }
	}
	property int p_queue {
		int get() { return queue; }
		void set(int q) { queue = q; }
	}
	property int p_car_id {
		int get() { return car_id; }
	}
	property List <Car^>^ p_neighbours {
		List <Car^>^ get() { return neighbours; }
		void set(List <Car^>^ crs) { neighbours = crs; }
	}
	//����������� � ����������
	Car(Gate^ gt, Parking^ park, EcoGate^ eco, int qu, Time^ tm)
	{	
		neighbours = gcnew List<Car^>(0);
		// ��������� �� ����
		posX = 740;
		posY = 1024;


		// ������ ��������
		scale = 1;
		width = 50;
		height = 100;


		// ��������� ���������
		speed_y = 15;
		speed_x = 0;
		queue = qu;
		// �������� �����
		goToGate_target = 600;
		goThrowGate_target = 450;
		target_Y = goToGate_target + 100 * queue;
		go_to_park_frame = -1;
		go_from_park_frame = 6;
		car_id = rand() % 100;


		// ������, ��� �������� �������
		parking = park;
		ecogate = eco;
		gate = gt;
		time_ = tm;
		status = 0;
		last_on_gate_req = time_->tick - 1000;


		// ���������� ����� ��� ��������, ���������� ����� -1
		provided_place = -1;


		// ����� ����������� �� ������ ������ � �� �����
		road_array_x = gcnew array<int>(10);
		road_array_y = gcnew array<int>(10);
		road_array_x[0] = 740;
		road_array_y[0] = 300;
		road_array_x[1] = 512;
		road_array_y[1] = 300;
		road_array_x[2] = 512;
		road_array_y[2] = 930;
		road_array_x[3] = 230;
		road_array_y[3] = 930;
		road_array_x[4] = 230;
		road_array_y[4] = 800;
		road_array_x[5] = 300;
		road_array_y[5] = 800;
		road_array_x[6] = 230;
		road_array_y[6] = 800;
		road_array_x[7] = 230;
		road_array_y[7] = 60;
		road_array_x[8] = 900;
		road_array_y[8] = 60;
		road_array_x[9] = 900;
		road_array_y[9] = 400;


		// ���������� ��������
		random_color_id = rand() % 4;
		if (random_color_id == 0) image = gcnew Bitmap(".\\assets\\car_orange.png");
		else if (random_color_id == 1) image = gcnew Bitmap(".\\assets\\car_white.png");
		else if (random_color_id == 2) image = gcnew Bitmap(".\\assets\\car_blue.png");
		else if (random_color_id == 3) image = gcnew Bitmap(".\\assets\\car_yellow.png");
		//�������� �� �������
		gate->openEvent += gcnew Gate::GateEventHandler(this, &Car::go_throw_gate);
		ecogate->openGateForLeaving += gcnew EcoGate::EcoGateEventHandler(this, &Car::go_throw_leaving_gate);
	};
	~Car() {};
	void leave_park() {
		leaving_car = true;
	}
	//����� ��������� ������ ��������� ����� ������
	void go_throw_gate() {

		if (queue != -1) {
			speed_y = 15;
			posY -= speed_y;
			
		}
		if (queue == 0 && !inactive_status) {
			target_Y = goThrowGate_target;
		}
		if (leaving_car) {
			target_Y = 600;
			speed_y = 15;
		}
	}
	void go_throw_leaving_gate() {
		if (leaving_car) {
			target_Y = 600;
			speed_y = 15;
		}
	}
	// �����, �������� ������� �������� ������ � ������, ����� ��� ��������� ��������
	void swap_resolution() {
		int temp_width = width;
		width = height;
		height = temp_width;
	}
	// �����, ������ ������ �����������, �� ����� ������� ������� ���������� � ��������,
	// ��� ����� ��������� �������� ��������� ������, � �� ����� �� ����������, ������������ ����� ��� �������
	void inactive() {
		go_from_park_frame = 10;
		go_to_park_frame = 10;
		leaving_car;
		inactive_status = true;
	}
	// ����� �������� � �������
	void queue_step() {
		if (queue >= 0) {
			target_Y = goToGate_target + 100 * queue;
			speed_y = 15;
		}
	}
	void park_this_car() {
		road_array_y[go_to_park_frame + 1] = posY;
		road_array_y[go_to_park_frame + 2] = posY;
	}
	//���������� ������ �������
	public: void update()
	{	
		// ���� ������ �������� ��� ��������� � ��������
		if (leaving_car == true) {
			if (posX != target_X) speed_x = 15;
			if (posY != target_Y) speed_y = 15;
			// ���� �������� �����, ������������� �� ��������� ����� � ������ �� ���������� ��������
			if (posX == target_X && posY == target_Y) {
				if (go_from_park_frame < 9) { go_from_park_frame++; rotate_needed = true; }
			}
			// ������ ���������� ��������� �� ���� � ������, ��������� ��������� ����� ��������.
			if (go_from_park_frame != 10) {
				target_X = road_array_x[go_from_park_frame];
				target_Y = road_array_y[go_from_park_frame];
			}
			//���� ����� ������� ��������, ������
			if (rotate_needed) {
				if (go_from_park_frame == 6)
				{
					image->RotateFlip(RotateFlipType::Rotate180FlipNone);
					rotate_needed = false;
				}
				else if (go_from_park_frame == 7) {
					image->RotateFlip(RotateFlipType::Rotate270FlipNone);
					swap_resolution();
					rotate_needed = false;
				}
				else if (go_from_park_frame == 8) {
					image->RotateFlip(RotateFlipType::Rotate90FlipNone);
					swap_resolution();
					rotate_needed = false;
				}
				else if (go_from_park_frame == 9) {
					image->RotateFlip(RotateFlipType::Rotate90FlipNone);
					swap_resolution();
					rotate_needed = false;
				}
			}
		} else if (!parked && go_to_park_frame >= 0){
		// �������� �������� ���� �� �������� 
			// ���� �������� ����� ��������, ������������� �� ��������
			if (posX == 230){
				if (posY % 100 == 0) {
					bool echelon_busy = false;
					for each (Car ^ cr in neighbours) {
						if (cr->p_car_id != car_id) {
							if (cr->p_posY == posY && abs(cr->p_posX - posX) < 150) {
								echelon_busy = true;
							}
						}
					}
					if (echelon_busy) {
						road_array_y[go_to_park_frame] -= 100;
						target_Y = road_array_y[go_to_park_frame];
					}
					else {
						park_this_car();
					}
				}
			}
			// ���� �������� ����� ����������, ����������� �� ���������
			if (posX == target_X && posY == target_Y) {
				if (go_to_park_frame < 5) { go_to_park_frame++; rotate_needed = true; }
			}
			// ������������� ������� ���������� ��� ������� �����
			if (go_to_park_frame < 10) {
				target_X = road_array_x[go_to_park_frame];
				target_Y = road_array_y[go_to_park_frame];
			}
			// ���� ��������, ���� �� �������� �����
			if (posX != target_X) speed_x = 15;
			if (posY != target_Y) speed_y = 15;
			// �������, ����� �� ��� ��������� ������ � ����������� ��������, � ��������� ������ ����������� �������
			if (rotate_needed) {
				if (go_to_park_frame == 1)
				{
					image->RotateFlip(RotateFlipType::Rotate270FlipNone);
					swap_resolution();
					rotate_needed = false;
				}
				else if (go_to_park_frame == 2) {
					image->RotateFlip(RotateFlipType::Rotate270FlipNone);
					swap_resolution();
					rotate_needed = false;
				}
				else if (go_to_park_frame == 3) {
					image->RotateFlip(RotateFlipType::Rotate90FlipNone);
					swap_resolution();
					rotate_needed = false;
				}
				else if (go_to_park_frame == 4) {
					image->RotateFlip(RotateFlipType::Rotate90FlipNone);
					swap_resolution();
					rotate_needed = false;
				}
				else if (go_to_park_frame == 5) {
					image->RotateFlip(RotateFlipType::Rotate90FlipNone);
					swap_resolution();
					parked = true;
					go_to_park_frame = 10;
					rotate_needed = true;
				}
			}
		}
		//���� ������ � �����
		if (posY == 600 && posX == 740) {
			if (!flagOnGate){
				flagOnGate = true;
				speed_y = 0;
			}
			else onGateEvent(); 
			//���������� � parking � �������� ����� send_car_enter_event
		}
		//���� ������ �������� ����� ������
		if (posY == 450 && posX == 740 && !flagAfterGate) {
			flagAfterGate = true;
			freeGateEvent();
			go_to_park_frame = 0;
			//target_Y = goToPark_target;
		}
		// ���� ������ �������� �������� �� ������
		if (posY == 600 && posX == 900) {
			target_Y = 1025;
			speed_y = 15;
			freeLeavingGateEvent();
		}
		// ���� ������ � ��������� �� ������
		if (posY == road_array_y[9] && posX == road_array_x[9] && !flagLeaveWaiting) {
			flagLeaveWaiting = true;
			go_from_park_frame = 10;
			onLeavingGateEvent();
		}



		//����������� ������ ����
		// ����������� ����� ��������
		if (target_X - posX < 0) speed_x = abs(speed_x) * -1;
		else speed_x = abs(speed_x);
		if (target_Y - posY < 0) speed_y = abs(speed_y) * -1;
		else speed_y = abs(speed_y);
		//���� � ��������� ��� � ������� ��������� ������ ��������� ������� ������� �� ��� Y, ���������� �� �� ������ ����������
		if ((posY > target_Y && posY + speed_y < target_Y) || (posY < target_Y && posY + speed_y > target_Y)) {
			posY = target_Y;
		}
		//���� ������ �� �������� ���� �� �c� Y, ���������� ��
		else if (posY != target_Y) {
			posY += speed_y;
		}
		//���� � ��������� ��� � ������� ��������� ������ ��������� ������� ������� �� ��� X, ���������� �� �� ������ ����������
		if ((posX > target_X && posX + speed_x < target_X) || (posX < target_X && posX + speed_x > target_X)) {
			posX = target_X;
		}
		//���� ������ �� �������� ���� �� �c� X, ���������� ��
		else if (posX != target_X) {
			posX += speed_x;
		}
	}
};
