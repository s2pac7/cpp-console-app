#pragma once

#include "Travel.h"

//значения таблицы поездок, которые находятся в заголовке таблицы
static const string TRAVEL_TABLE_TYPE_STR = "Тип";
static const string TRAVEL_TABLE_COUNTRY_STR = "Страна";
static const string TRAVEL_TABLE_VEHICLE_STR = "Транспорт";
static const string TRAVEL_TABLE_NURTURE_STR = "Питание";
static const string TRAVEL_TABLE_DAYS_STR = "Кол-во дней";
static const string TRAVEL_TABLE_COST_STR = "Цена";
static const size_t TRAVEL_TABLE_IND_COUNT_BASE = 3;

//хранит максимальные значения полей таблицы поездок
struct TableOutputSizesTravel
{
	size_t type_count;
	size_t country_count;
	size_t vehicle_count;
	size_t nurture_count;
	size_t days_count;
	size_t cost_count;
};

//считают размеры для таблицы поездок
TableOutputSizesTravel CalculateSizesTravel(const vector<Travel> &travels);
TableOutputSizesTravel CalculateSizesTravel(const Travel &travel);

//для вывода таблицы поездок
void ShowFooterTravel(TableOutputSizesTravel sizes, bool show_ind = false);
void ShowHeaderTravel(TableOutputSizesTravel sizes, bool show_ind = false);
void CreateTableStringTravel(TableOutputSizesTravel sizes, const Travel &tr, bool show_ind = false, size_t ind = 0);
void ShowTravel(const Travel &tr, bool show_header = true);
void ShowTravels(const vector<Travel> &travels);
