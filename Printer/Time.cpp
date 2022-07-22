//Класс, отвечающий за течение времени

#pragma once
#include <iostream>

ref class Time 
{
private:
    //Поля
    int hours, minutes, seconds;
    bool night;
public:
    //Делегат для события час, подписан Parking;
    delegate void TimeEventHandler();
    static event TimeEventHandler^ CHAS;
    //Конструктор и деструктор
    Time(int xInput, int yInput, int zInput)
    {
        hours = xInput;
        minutes = yInput;
        seconds = zInput;
        night = false;
    };
    ~Time() {};
    //Свойства
    property int hours_P {
        int get() { return hours; }
        void set(int value) { hours = value; }
    }
    property int minutes_P {
        int get() { return minutes; }
        void set(int value) { minutes = value; }
    }
    property int seconds_P {
        int get() { return seconds; }
        void set(int value) { seconds = value; }
    }
    property bool p_night {
        bool get() { return night; }
        void set(bool value) { night = value; }
    }
    property int tick {
        int get() { return hours * 60 * 60 + minutes * 60 + seconds; }
    }
    //Метод обновления времени
    void Update()
    {
        seconds += 10;
        if (seconds >= 60)
        {
            minutes += 1;
            seconds = seconds - 60;
        }
        if (minutes >= 60)
        {
            hours += 1;
            minutes = minutes - 60;
            if (hours >= 4 && hours < 21)
            {
                CHAS();
            }     
        }
        if (hours >= 24)
        {
            hours = 0;
        }
        if ((hours >= 0 && hours < 4) || (hours >= 21))
        {
            night = true;
        }
        else if (hours >= 4 && hours < 21)
        {
            night = false;
        }
    }
};