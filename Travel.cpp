#include "Travel.h"
#include <fstream>
#include <sstream>
#include <cassert>

string GetType(const Travel &tr)
{
	switch(tr.type)
	{
		case TravelType::Rest: return "Rest"; break;
		case TravelType::ExcursionTour: return "Excursion"; break;
		case TravelType::Treatment: return "Treatment"; break;
		case TravelType::Shoping: return "Shopping"; break;
		case TravelType::Cruise: return "Cruise"; break;
		default: assert(false); break;
	}
}

string GetTransferVehicle(const Travel &tr)
{
	switch(tr.vehicle)
	{
		case TransferVehicle::Auto: return "Auto"; break;
		case TransferVehicle::Bus: return "Bus"; break;
		case TransferVehicle::Airplane: return "Airplane"; break;
		case TransferVehicle::Ship: return "Ship"; break;
		default: assert(false); break;
	}
}

string GetNurture(const Travel &tr)
{
	switch(tr.nurture)
	{
		case NurtureType::None: return "None"; break;
		case NurtureType::Breakfasts: return "Only breakfasts"; break;
		case NurtureType::AllIncluded: return "All included"; break;
		default: assert(false); break;
	}

}

string GetDays(const Travel &tr)
{
	ostringstream ostr;
	ostr<<tr.days;
	return ostr.str();
}

string GetCost(const Travel &tr)
{
	ostringstream ostr;
	ostr<<tr.cost;
	return ostr.str();
}

pair<vector<Travel>, string> ReadAllTravels(const string &path)
{
	ifstream ifs(path);
	if(!ifs.is_open())
		return {{}, "istream open error!"};

	vector<Travel> out_vec;
	int type, veh, nurt;
	while(true)
	{
		Travel tr;
		ifs>>type>>tr.country>>veh>>nurt>>tr.days>>tr.cost;
		if(ifs.eof())
			break;

		tr.type = static_cast<TravelType>(type);
		tr.vehicle = static_cast<TransferVehicle>(veh);
		tr.nurture = static_cast<NurtureType>(nurt);
		out_vec.push_back(tr);
	}

	ifs.close();
	return {out_vec, {}};
}


void WriteAllTravels(const string &path, const vector<Travel> &travels)
{
	ofstream ofs(path);
	if(!ofs.is_open())
		return;

	for(size_t i = 0; i < travels.size(); i++)
		ofs<<travels[i].type<<" "<<travels[i].country<<" "<<travels[i].vehicle<<" "<<travels[i].nurture<<" "<<travels[i].days<<" "<<travels[i].cost<<"\n";

	ofs.close();
}
