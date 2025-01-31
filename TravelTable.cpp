#include "TravelTable.h"
#include <iostream>
#include <iomanip>

TableOutputSizesTravel CalculateSizesTravel(const vector<Travel> &travels)
{
	TableOutputSizesTravel tbl;
	tbl.type_count = TRAVEL_TABLE_TYPE_STR.size();
	tbl.country_count = TRAVEL_TABLE_COUNTRY_STR.size();
	tbl.nurture_count = TRAVEL_TABLE_NURTURE_STR.size();
	tbl.days_count = TRAVEL_TABLE_DAYS_STR.size();
	tbl.cost_count = TRAVEL_TABLE_COST_STR.size();
	tbl.vehicle_count = TRAVEL_TABLE_VEHICLE_STR.size();

	for(size_t i = 0; i < travels.size(); i++)
	{
		if(size_t type_size = GetType(travels[i]).size(); type_size > tbl.type_count)
			tbl.type_count = type_size;
		if(size_t country_size = travels[i].country.size(); country_size > tbl.country_count)
			tbl.country_count = country_size;
		if(size_t nurture_size = GetNurture(travels[i]).size(); nurture_size > tbl.nurture_count)
			tbl.nurture_count = nurture_size;
		if(size_t days_size = GetDays(travels[i]).size(); days_size > tbl.days_count)
			tbl.days_count = days_size;
		if(size_t cost_size = GetCost(travels[i]).size(); cost_size > tbl.cost_count)
			tbl.cost_count = cost_size;
		if(size_t veh_size = GetTransferVehicle(travels[i]).size(); veh_size > tbl.vehicle_count)
			tbl.vehicle_count = veh_size;
	}

	return tbl;
}

TableOutputSizesTravel CalculateSizesTravel(const Travel &travel)
{
	TableOutputSizesTravel tbl;
	tbl.type_count = TRAVEL_TABLE_TYPE_STR.size();
	tbl.country_count = TRAVEL_TABLE_COUNTRY_STR.size();
	tbl.nurture_count = TRAVEL_TABLE_NURTURE_STR.size();
	tbl.days_count = TRAVEL_TABLE_DAYS_STR.size();
	tbl.cost_count = TRAVEL_TABLE_COST_STR.size();
	tbl.vehicle_count = TRAVEL_TABLE_VEHICLE_STR.size();

	if(size_t type_size = GetType(travel).size(); type_size > tbl.type_count)
		tbl.type_count = type_size;
	if(size_t country_size = travel.country.size(); country_size > tbl.country_count)
		tbl.country_count = country_size;
	if(size_t nurture_size = GetNurture(travel).size(); nurture_size > tbl.nurture_count)
		tbl.nurture_count = nurture_size;
	if(size_t days_size = GetDays(travel).size(); days_size > tbl.days_count)
		tbl.days_count = days_size;
	if(size_t cost_size = GetCost(travel).size(); cost_size > tbl.cost_count)
		tbl.cost_count = cost_size;
	if(size_t veh_size = GetTransferVehicle(travel).size(); veh_size > tbl.vehicle_count)
		tbl.vehicle_count = veh_size;

	return tbl;
}

void ShowFooterTravel(TableOutputSizesTravel sizes, bool show_ind)
{
	if(show_ind)
	{
		cout<<"+";
		for(size_t i = 0; i < TRAVEL_TABLE_IND_COUNT_BASE; i++)
			cout<<"-";
	}

	cout<<"+";

	for(size_t i = 0; i < sizes.type_count; i++)
		cout<<"-";
	cout<<"+";

	for(size_t i = 0; i < sizes.country_count; i++)
		cout<<"-";
	cout<<"+";

	for(size_t i = 0; i < sizes.vehicle_count; i++)
		cout<<"-";
	cout<<"+";

	for(size_t i = 0; i < sizes.nurture_count; i++)
		cout<<"-";
	cout<<"+";

	for(size_t i = 0; i < sizes.days_count; i++)
		cout<<"-";
	cout<<"+";

	for(size_t i = 0; i < sizes.cost_count; i++)
		cout<<"-";
	cout<<"+\n";
}

void ShowHeaderTravel(TableOutputSizesTravel sizes, bool show_ind)
{
	ShowFooterTravel(sizes, show_ind);

	if(show_ind)
	{
		cout<<"|";
		int dt = TRAVEL_TABLE_IND_COUNT_BASE / 2;
		for(size_t i = 0; i < dt; i++)
			cout<<" ";

		cout<<"#";
		for(size_t i = 0; i < TRAVEL_TABLE_IND_COUNT_BASE - dt - 1; i++)
			cout<<" ";
	}

	cout<<"|";

	string tmp_str = TRAVEL_TABLE_TYPE_STR;
	tmp_str.resize(sizes.type_count, ' ');
	for(size_t i = 0; i < tmp_str.size(); i++)
		cout<<tmp_str[i];
	cout<<"|";

	tmp_str = TRAVEL_TABLE_COUNTRY_STR;
	tmp_str.resize(sizes.country_count, ' ');
	for(size_t i = 0; i < tmp_str.size(); i++)
		cout<<tmp_str[i];
	cout<<"|";

	tmp_str = TRAVEL_TABLE_VEHICLE_STR;
	tmp_str.resize(sizes.vehicle_count, ' ');
	for(size_t i = 0; i < tmp_str.size(); i++)
		cout<<tmp_str[i];
	cout<<"|";

	tmp_str = TRAVEL_TABLE_NURTURE_STR;
	tmp_str.resize(sizes.nurture_count, ' ');
	for(size_t i = 0; i < tmp_str.size(); i++)
		cout<<tmp_str[i];
	cout<<"|";

	tmp_str = TRAVEL_TABLE_DAYS_STR;
	tmp_str.resize(sizes.days_count, ' ');
	for(size_t i = 0; i < tmp_str.size(); i++)
		cout<<tmp_str[i];
	cout<<"|";

	tmp_str = TRAVEL_TABLE_COST_STR;
	tmp_str.resize(sizes.cost_count, ' ');
	for(size_t i = 0; i < tmp_str.size(); i++)
		cout<<tmp_str[i];
	cout<<"|\n";

	ShowFooterTravel(sizes, show_ind);
}

void CreateTableStringTravel(TableOutputSizesTravel sizes, const Travel &tr, bool show_ind, size_t ind)
{
	if(show_ind)
		cout<<"|"<<setw(TRAVEL_TABLE_IND_COUNT_BASE)<<ind;
	cout<<"|";

	string tmp_str(GetType(tr));
	tmp_str.resize(sizes.type_count, ' ');
	cout<<tmp_str;
	cout<<"|";

	tmp_str = string(tr.country);
	tmp_str.resize(sizes.country_count, ' ');
	cout<<tmp_str;
	cout<<"|";

	tmp_str = string(GetTransferVehicle(tr));
	tmp_str.resize(sizes.vehicle_count, ' ');
	cout<<tmp_str;
	cout<<"|";

	tmp_str = string(GetNurture(tr));
	tmp_str.resize(sizes.nurture_count, ' ');
	cout<<tmp_str;
	cout<<"|";

	tmp_str = string(GetDays(tr));
	tmp_str.resize(sizes.days_count, ' ');
	cout<<tmp_str;
	cout<<"|";

	tmp_str = string(GetCost(tr));
	tmp_str.resize(sizes.cost_count, ' ');
	cout<<tmp_str;
	cout<<"|\n";
}

void ShowTravel(const Travel &tr, bool show_header)
{
	auto sizes = CalculateSizesTravel(tr);
	if(show_header)
		ShowHeaderTravel(sizes, false);

	CreateTableStringTravel(sizes, tr, false);
	ShowFooterTravel(sizes, false);
}


void ShowTravels(const vector<Travel> &travels)
{
	auto sizes = CalculateSizesTravel(travels);
	ShowHeaderTravel(sizes, true);

	for(size_t i = 0; i < travels.size(); i++)
		CreateTableStringTravel(sizes, travels[i], true, i);
	ShowFooterTravel(sizes, true);
}
