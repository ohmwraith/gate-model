//Класс машин

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
	// Объявление и инициализация переменных
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
	//Делегат событий въезда машины
	delegate void CarEventHandler();
	//Делегат событий отъезда с парковки
	delegate void CarLeaveHandler();
	//Событие машина у ворот
	static event CarEventHandler^ onGateEvent;
	//Событие машина у ворот на выходе
	static event CarLeaveHandler^ onLeavingGateEvent;
	//Событие машина проехала в ворота
	static event CarEventHandler^ freeGateEvent;
	//Событие машина проехала в ворота на выходе
	static event CarLeaveHandler^ freeLeavingGateEvent;
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
	//Конструктор и деструктор
	Car(Gate^ gt, Parking^ park, EcoGate^ eco, int qu, Time^ tm)
	{	
		neighbours = gcnew List<Car^>(0);
		// Положение по осям
		posX = 740;
		posY = 1024;


		// Размер картинки
		scale = 1;
		width = 50;
		height = 100;


		// Стартовые установки
		speed_y = 15;
		speed_x = 0;
		queue = qu;
		// Ключевые точки
		goToGate_target = 600;
		goThrowGate_target = 450;
		target_Y = goToGate_target + 100 * queue;
		go_to_park_frame = -1;
		go_from_park_frame = 6;
		car_id = rand() % 100;


		// Классы, для привязки событий
		parking = park;
		ecogate = eco;
		gate = gt;
		time_ = tm;
		status = 0;
		last_on_gate_req = time_->tick - 1000;


		// Переданное место для парковки, изначально равно -1
		provided_place = -1;


		// Карта перемещения от начала дороги и до конца
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


		// Присвоение картинки
		random_color_id = rand() % 4;
		if (random_color_id == 0) image = gcnew Bitmap(".\\assets\\car_orange.png");
		else if (random_color_id == 1) image = gcnew Bitmap(".\\assets\\car_white.png");
		else if (random_color_id == 2) image = gcnew Bitmap(".\\assets\\car_blue.png");
		else if (random_color_id == 3) image = gcnew Bitmap(".\\assets\\car_yellow.png");
		//Подписка на события
		gate->openEvent += gcnew Gate::GateEventHandler(this, &Car::go_throw_gate);
		ecogate->openGateForLeaving += gcnew EcoGate::EcoGateEventHandler(this, &Car::go_throw_leaving_gate);
	};
	~Car() {};
	void leave_park() {
		leaving_car = true;
	}
	//Метод указывает машине двигаться через ворота
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
	// Метод, меняющий местами значения ширины и высоты, нужен для разворота картинки
	void swap_resolution() {
		int temp_width = width;
		width = height;
		height = temp_width;
	}
	// Метод, делает машину независимой, ей можно указать целевые координаты и скорость,
	// она будет двигаться согласно введенным данным, и ее никто не потревожит, используется ночью для отъезда
	void inactive() {
		go_from_park_frame = 10;
		go_to_park_frame = 10;
		leaving_car;
		inactive_status = true;
	}
	// Метод смещения в очереди
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
	//Обновление данных объекта
	public: void update()
	{	
		// Если машина отмечена как уезжающая с парковки
		if (leaving_car == true) {
			if (posX != target_X) speed_x = 15;
			if (posY != target_Y) speed_y = 15;
			// Если достигли точки, переключаемся на следующую точку и делаем ее координаты целевыми
			if (posX == target_X && posY == target_Y) {
				if (go_from_park_frame < 9) { go_from_park_frame++; rotate_needed = true; }
			}
			// Машина продолжает следовать по пути к выезду, используя следующие точки поворота.
			if (go_from_park_frame != 10) {
				target_X = road_array_x[go_from_park_frame];
				target_Y = road_array_y[go_from_park_frame];
			}
			//Если нужен поворот картинки, делаем
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
		// Условный оператор пути до парковки 
			// Если достигли точки поворота, переключаемся на следущую
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
			// Если ключевая точка достигнута, переключить на следующую
			if (posX == target_X && posY == target_Y) {
				if (go_to_park_frame < 5) { go_to_park_frame++; rotate_needed = true; }
			}
			// Устанавливаем целевые координаты для текущей точки
			if (go_to_park_frame < 10) {
				target_X = road_array_x[go_to_park_frame];
				target_Y = road_array_y[go_to_park_frame];
			}
			// Даем скорость, если не достигли точки
			if (posX != target_X) speed_x = 15;
			if (posY != target_Y) speed_y = 15;
			// Смотрим, нужно ли нам повернуть машину в направлении движения, в указанных точках выполняется поворот
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
		//Если машина у ворот
		if (posY == 600 && posX == 740) {
			if (!flagOnGate){
				flagOnGate = true;
				speed_y = 0;
			}
			else onGateEvent(); 
			//Передается в parking и вызывает метод send_car_enter_event
		}
		//Если машина проехала через ворота
		if (posY == 450 && posX == 740 && !flagAfterGate) {
			flagAfterGate = true;
			freeGateEvent();
			go_to_park_frame = 0;
			//target_Y = goToPark_target;
		}
		// Если машина проехала шлагбаум на выезде
		if (posY == 600 && posX == 900) {
			target_Y = 1025;
			speed_y = 15;
			freeLeavingGateEvent();
		}
		// Если машина у шлагбаума на выезде
		if (posY == road_array_y[9] && posX == road_array_x[9] && !flagLeaveWaiting) {
			flagLeaveWaiting = true;
			go_from_park_frame = 10;
			onLeavingGateEvent();
		}



		//Перемещение машины ниже
		// Определение знака скорости
		if (target_X - posX < 0) speed_x = abs(speed_x) * -1;
		else speed_x = abs(speed_x);
		if (target_Y - posY < 0) speed_y = abs(speed_y) * -1;
		else speed_y = abs(speed_y);
		//Если в следующий тик с текущей скоростью машина проскочит целевую позицию по оси Y, возвращаем ее на нужные координаты
		if ((posY > target_Y && posY + speed_y < target_Y) || (posY < target_Y && posY + speed_y > target_Y)) {
			posY = target_Y;
		}
		//Если машина не достигла цели по оcи Y, перемещаем ее
		else if (posY != target_Y) {
			posY += speed_y;
		}
		//Если в следующий тик с текущей скоростью машина проскочит целевую позицию по оси X, возвращаем ее на нужные координаты
		if ((posX > target_X && posX + speed_x < target_X) || (posX < target_X && posX + speed_x > target_X)) {
			posX = target_X;
		}
		//Если машина не достигла цели по оcи X, перемещаем ее
		else if (posX != target_X) {
			posX += speed_x;
		}
	}
};
