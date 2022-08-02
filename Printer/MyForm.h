#pragma once
#include <iostream>
#include <ctime> 
#include <cstdlib>
#include "Car.cpp"
#include "Gate.cpp"
//#include "EcoGate.cpp"
#include "Parking.cpp"
//#include "CarReverse.cpp"
#include <windows.h>
#pragma comment (lib, "Advapi32.lib")
#pragma comment (lib, "user32.lib")

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

namespace Printer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		//Объявляем все классы и листы
		Time^ time_;
		Car^ car;
		Parking^ parking;
		Gate^ gate;
		EcoGate^ ecogate;
		Graphics^ gf;
		Bitmap^ background_image;
		Bitmap^ Noch;
		List <Car^>^ carList;
		List <Car^>^ gateQueueList;
		int lastCarMinutes = 0, ecogate_timing = 0, last_gate_opening = 0;
	//	SignalConst^ signAvt;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;





	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ total_textbox;
	private: System::Windows::Forms::TextBox^ free_textbox;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label7;











	public:
		MyForm(void)
		{
			//car_image = gcnew Bitmap(".\\assets\\car_white.png");
			carList = gcnew List<Car^>(0);
			gateQueueList = gcnew List<Car^>(0);
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	protected:
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->total_textbox = (gcnew System::Windows::Forms::TextBox());
			this->free_textbox = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1024, 1024);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// trackBar1
			// 
			this->trackBar1->BackColor = System::Drawing::Color::DarkSlateGray;
			this->trackBar1->LargeChange = 1;
			this->trackBar1->Location = System::Drawing::Point(25, 119);
			this->trackBar1->Margin = System::Windows::Forms::Padding(2);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(204, 45);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::LightGreen;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(217, 84);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(22, 24);
			this->label1->TabIndex = 2;
			this->label1->Text = L"+";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::LightGreen;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(21, 84);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(17, 24);
			this->label2->TabIndex = 3;
			this->label2->Text = L"-";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(566, 9);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(128, 31);
			this->label3->TabIndex = 4;
			this->label3->Text = L"16:00:00";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::LightGreen;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(33, 14);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(69, 25);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Всего";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::LightGreen;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(33, 44);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(110, 25);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Свободно";
			// 
			// total_textbox
			// 
			this->total_textbox->BackColor = System::Drawing::Color::LightGreen;
			this->total_textbox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->total_textbox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->total_textbox->Location = System::Drawing::Point(169, 14);
			this->total_textbox->Name = L"total_textbox";
			this->total_textbox->ReadOnly = true;
			this->total_textbox->Size = System::Drawing::Size(60, 24);
			this->total_textbox->TabIndex = 10;
			// 
			// free_textbox
			// 
			this->free_textbox->BackColor = System::Drawing::Color::LightGreen;
			this->free_textbox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->free_textbox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->free_textbox->Location = System::Drawing::Point(169, 45);
			this->free_textbox->Name = L"free_textbox";
			this->free_textbox->ReadOnly = true;
			this->free_textbox->Size = System::Drawing::Size(60, 24);
			this->free_textbox->TabIndex = 11;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(169, 191);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(70, 25);
			this->label6->TabIndex = 12;
			this->label6->Text = L"label6";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(169, 225);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(70, 25);
			this->label7->TabIndex = 13;
			this->label7->Text = L"label7";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::LightGreen;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(78, 84);
			this->label8->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(104, 24);
			this->label8->TabIndex = 14;
			this->label8->Text = L"Скорость";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(169, 260);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(70, 25);
			this->label9->TabIndex = 15;
			this->label9->Text = L"label9";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(157, 298);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(82, 25);
			this->label10->TabIndex = 16;
			this->label10->Text = L"label10";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(157, 333);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(82, 25);
			this->label11->TabIndex = 17;
			this->label11->Text = L"label11";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(157, 368);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(82, 25);
			this->label12->TabIndex = 18;
			this->label12->Text = L"label12";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(157, 404);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(82, 25);
			this->label13->TabIndex = 19;
			this->label13->Text = L"label13";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(1024, 1024);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->free_textbox);
			this->Controls->Add(this->total_textbox);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->pictureBox1);
			this->Margin = System::Windows::Forms::Padding(0);
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"Модель шлагбаума";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		srand(time(0));
		rand();
		//Инициализация и запуск
		time_ = gcnew Time(19, 00, 00);
		gate = gcnew Gate();
		ecogate = gcnew EcoGate();
		parking = gcnew Parking(5, 5, time_, gate);
		last_gate_opening = time_->tick - 1000;
		//car = gcnew Car(gate, parking);
		rand();
		timer1 -> Interval = 500;
		timer1 -> Start();
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		time_->Update();
		if (time_->hours_P == 0 && time_->minutes_P == 0 && time_->seconds_P == 0) lastCarMinutes = 0;
		if (getRandomNumber(1, 100) > 1)
		{	
			if (gateQueueList->Count < 4 && carList->Count < 8 && !time_->p_night && (time_->hours_P * 60) % 24 * 60 + time_->minutes_P - lastCarMinutes > 5)
			{
				lastCarMinutes = (time_->hours_P * 60) % 24 * 60 + time_->minutes_P;
				Car^ cr = gcnew Car(gate, parking, ecogate, gateQueueList->Count);
				carList->Add(cr);
				gateQueueList->Add(cr);
			}
		}
		if (getRandomNumber(1, 100) > 98)
		{
			if (carList->Count > 0 && carList[0]->p_parked) {
				carList[0]->leave_park();
			}
		}
		for each (Car ^ cr in carList)
		{
			cr->update();
			cr->p_neighbours = carList;
			label10->Text = (cr->p_width).ToString();
		}
		if (time_->p_night && gateQueueList->Count > 0) {
			for each (Car ^ qcar in gateQueueList) {
				qcar->inactive();
				qcar->p_target_Y = 1500;
				qcar->p_speed_y = 15;
			}

		}

		for (int i = 0; i < carList -> Count; i++)
		{
			if (carList[i]->p_posY < -400 || carList[i]->p_posY > 1024)
			{
				delete carList[i];
				carList -> RemoveAt(i);
			}
		}
		/*if (ecogate->p_open) {
			if (ecogate_timing == 0) ecogate_timing = time_->hours_P * 60 + time_->minutes_P;
			else if ((time_->hours_P * 60 + time_->minutes_P) - ecogate_timing > 5) { ecogate->close(); ecogate_timing = 0; }
		}*/
		total_textbox->Text = (parking->p_total).ToString();
		free_textbox->Text = (parking->p_free).ToString();
		label9->Text = (gateQueueList->Count).ToString();
		gate->update();
		if (gateQueueList->Count >= 1) {
			label10->Text = (gateQueueList[0]->p_queue).ToString();
			label10->Location = System::Drawing::Point(gateQueueList[0]->p_posX, gateQueueList[0]->p_posY);
		}
		if (gateQueueList->Count >= 2) {
			label11->Text = (gateQueueList[1]->p_queue).ToString();
			label11->Location = System::Drawing::Point(gateQueueList[1]->p_posX, gateQueueList[1]->p_posY);
		}
		if (gateQueueList->Count >= 3) {
			label12->Text = (gateQueueList[2]->p_queue).ToString();
			label12->Location = System::Drawing::Point(gateQueueList[2]->p_posX, gateQueueList[2]->p_posY);
		}
		if (gateQueueList->Count >= 4) {
			label13->Text = (gateQueueList[3]->p_queue).ToString();
			label13->Location = System::Drawing::Point(gateQueueList[3]->p_posX, gateQueueList[3]->p_posY);
		}
		//time_->tick - last_gate_opening > 0.3
		for each (Car ^ ctr in carList) {
			if (ctr->p_posX == 740 && ctr->p_posY == 450) {
				last_gate_opening = time_->tick;
				if (gateQueueList->Count > 0) {
					//delete gateQueueList[0];
					//gateQueueList->RemoveAt(0);
					ctr->p_queue = -1;
					gateQueueList->Remove(ctr);
					for (int i = 0; i < gateQueueList->Count; i++) {
						gateQueueList[i]->p_queue = i;
						gateQueueList[i]->queue_step();
					}
				}
			}
		} 
		ecogate->update();
		graphics();
	}
	private: void graphics()
	{
		//Обновляем визуальную составляющюю
		background_image = gcnew Bitmap(".\\assets\\bg_new.png");
		gf = gf->FromImage(background_image);
		for each (Car ^ cr in carList)
		{	
			 gf->DrawImageUnscaledAndClipped(cr->p_image, System::Drawing::Rectangle(cr->p_posX, cr->p_posY, cr->p_width, cr->p_height));
			 label6->Text = (cr->p_target_Y).ToString();
			 label7->Text = (cr->p_posY).ToString();
		}
		if (time_ -> p_night == true)
		{
			Noch = gcnew Bitmap(".\\assets\\FonNight.png");
		}
		else
		{
			Noch = gcnew Bitmap(".\\assets\\Pusto.png");
		}
		gf->DrawImageUnscaledAndClipped(gate->p_image, System::Drawing::Rectangle(gate->p_posX, gate->p_posY, 160, 139));
		gf->DrawImageUnscaledAndClipped(ecogate->p_image, System::Drawing::Rectangle(ecogate->p_posX, ecogate->p_posY, 160, 139));
		gf->DrawImageUnscaledAndClipped(Noch, System::Drawing::Rectangle(0, 0, 1024, 1024));
		pictureBox1->Image = background_image;
		//Обновление таймера на форме
		char str[] = "00:00:00";
		str[0] = (time_->hours_P) / 10;
		str[1] = (time_->hours_P) % 10;
		str[3] = (time_->minutes_P) / 10;
		str[4] = (time_->minutes_P) % 10;
		str[5] = (time_->seconds_P) / 10;
		str[6] = (time_->seconds_P) % 10;
		label3->Text = System::Convert::ToString(str[0]) + System::Convert::ToString(str[1]) +
			":" + System::Convert::ToString(str[3]) + System::Convert::ToString(str[4]) +
			":" + System::Convert::ToString(str[5]) + System::Convert::ToString(str[6]);
	}
	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
		timer1->Interval = 500 - trackBar1->Value * 50 + 10;
	}

};
}
