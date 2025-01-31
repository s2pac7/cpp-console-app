#pragma once

#include <string>
#include <vector>

using namespace std;

enum TravelType
{
	Rest = 0,
	ExcursionTour = 1,
	Treatment = 2,
	Shoping = 3,
	Cruise = 4
};

enum TransferVehicle
{
	Auto = 0,
	Bus = 1,
	Airplane = 2,
	Ship = 3
};

enum NurtureType
{
	None = 0,
	Breakfasts = 1,
	AllIncluded = 2

};

//структура путешествия
struct Travel
{
	TravelType type;
	string country;
	TransferVehicle vehicle;
	NurtureType nurture;
	size_t days;
	size_t cost;
};

//переводит тип поездки в строку
string GetType(const Travel &tr);

//переводит тип транспорта в строку
string GetTransferVehicle(const Travel &tr);

//переводит тип питания в строку
string GetNurture(const Travel &tr);

//переводит дни в строку
string GetDays(const Travel &tr);

//переводит цену в строку
string GetCost(const Travel &tr);

//читает все поездки из файла и возвращает пару из вектора поездок и строи(если возникла ошибка)
pair<vector<Travel>, string> ReadAllTravels(const string &path);

//записывает все поездки в файл
void WriteAllTravels(const string &path, const vector<Travel> &travels);
