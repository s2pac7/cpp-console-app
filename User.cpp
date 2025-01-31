#include "User.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Common.hpp"
#include "Auth.h"
#include "TravelTable.h"
#include "UserTable.h"

string GetRole(const User &usr)
{
	switch(usr.role)
	{
		case UserRole::Admin: return "Administrator"; break;
		case UserRole::Traveler: return "Traveler"; break;
		default: assert(false); break;
	}
}

string GetAccess(const User &usr)
{
	switch(usr.access)
	{
		case UserAccess::Open: return "Active"; break;
		case UserAccess::Blocked: return "Blocked"; break;
		case UserAccess::OnRequest: return "On access request";break;
		default: assert(false); break;
	}
}

//common
pair<vector<User>, string> ReadAllUsers(const string &path)
{
	ifstream ifs(path);
	if(!ifs.is_open())
		return {{}, "ifstream open error!"};

	vector<User> out_vec;
	int tmp_role, tmp_acc;
	while(true)
	{
		User usr;
		ifs>>usr.login>>usr.hashed_pwd>>tmp_role>>tmp_acc;
		if(ifs.eof())
			break;

		usr.role = static_cast<UserRole>(tmp_role);
		usr.access = static_cast<UserAccess>(tmp_acc);
		out_vec.push_back(usr);
	}

	ifs.close();
	return {out_vec, {}};
}


void WriteAllUsers(const string &path, const vector<User> &users)
{
	ofstream ofs(path);
	if(!ofs.is_open())
		return;

	for(size_t i = 0; i < users.size(); i++)
		ofs<<users[i].login<<" "<<users[i].hashed_pwd<<" "<<users[i].role<<" "<<users[i].access<<"\n";

	ofs.close();
}

//traveler
void UserPanel(vector<Travel> &travels)
{
	bool is_run = true;

	vector<Travel> tmp_travels;
	while(is_run)
	{
		cout<<"Выберите действие:"<<endl;
		cout<<"1. Поиск путевок"<<endl;
		cout<<"2. Сортировка путевок"<<endl;
		cout<<"3. Поиск путевок одного типа с ограничением по цене по убыванию стоимости (идн. задание)"<<endl;
		cout<<"4. Покупка путевки"<<endl;
		cout<<"5. Вывод всех путевок"<<endl;
		cout<<"6. Выход"<<endl;

		int res = InputArithmetic<int>(1, 6);

		switch(res)
		{
			case 1:
				tmp_travels = FindTravels(travels);
				if(tmp_travels.empty())
					cout<<"Ничего не найдено!"<<endl;
				else
					ShowTravels(tmp_travels);
				break;
			case 2:
				tmp_travels = SortTravels(travels);
				if(tmp_travels.empty())
					cout<<"Ничего не найдено!"<<endl;
				else
					ShowTravels(tmp_travels);
				break;
			case 3:
				tmp_travels = FindByTypeMaxCostDesc(travels);
				if(tmp_travels.empty())
					cout<<"Ничего не найдено!"<<endl;
				else
					ShowTravels(tmp_travels);
				break;
			case 4:
				if(travels.empty())
					cout<<"Путевок нет!"<<endl;
				else
					BuyTravel(travels);
				break;
			case 5:
				if(travels.empty())
					cout<<"Путевок нет!"<<endl;
				else
					ShowTravels(travels);
				break;
			case 6:
				is_run = false;
				break;
		}
	}
}

vector<Travel> FindTravels(const vector<Travel> &travels)
{
	if(travels.empty())
		return {};

	system("cls");
	vector<Travel> tmp_travels;
	cout<<"Выберите тип поиска:"<<endl;
	cout<<"1. Поиск по типу"<<endl;
	cout<<"2. Поиск по стране"<<endl;
	cout<<"3. Поиск по типу транспорта"<<endl;
	cout<<"4. Поиск по типу питания"<<endl;
	cout<<"5. Поиск по кол-ву дней"<<endl;
	cout<<"6. Поиск по цене"<<endl;

	int res = InputArithmetic<int>(1, 6);

	switch(res)
	{
		case 1:
			{
				TravelType type;
				cout<<"Выберите тип:"<<endl;
				cout<<"1. Отдых"<<endl;
				cout<<"2. Экскурсионный тур"<<endl;
				cout<<"3. Лечение"<<endl;
				cout<<"4. Шоппинг"<<endl;
				cout<<"5. Круиз"<<endl;

				res = InputArithmetic<int>(1, 5);
				switch(res)
				{
					case 1: type = TravelType::Rest; break;
					case 2: type = TravelType::ExcursionTour; break;
					case 3: type = TravelType::Treatment; break;
					case 4: type = TravelType::Shoping; break;
					case 5: type = TravelType::Cruise; break;
				}

				for(size_t i = 0; i < travels.size(); i++)
				{
					if(travels[i].type == type)
						tmp_travels.push_back(travels[i]);
				}
			}
			break;
		case 2:
			{
				string tmp_str;
				cout<<"Введите страну: ";
				getline(cin, tmp_str);
				for(size_t i = 0; i < travels.size(); i++)
				{
					if(travels[i].country == tmp_str)
						tmp_travels.push_back(travels[i]);
				}
			}
			break;
		case 3:
			{
				TransferVehicle type;
				cout<<"Выберите тип:"<<endl;
				cout<<"1. Автомобиль"<<endl;
				cout<<"2. Автобус"<<endl;
				cout<<"3. Самолет"<<endl;
				cout<<"4. Корабль"<<endl;

				res = InputArithmetic<int>(1, 4);
				switch(res)
				{
					case 1: type = TransferVehicle::Auto; break;
					case 2: type = TransferVehicle::Bus; break;
					case 3: type = TransferVehicle::Airplane; break;
					case 4: type = TransferVehicle::Ship; break;
				}

				for(size_t i = 0; i < travels.size(); i++)
				{
					if(travels[i].vehicle == type)
						tmp_travels.push_back(travels[i]);
				}
			}
			break;
		case 4:
			{
				NurtureType type;
				cout<<"Выберите тип:"<<endl;
				cout<<"1. Без питания"<<endl;
				cout<<"2. Только завтраки"<<endl;
				cout<<"3. Все включено"<<endl;

				res = InputArithmetic<int>(1, 3);
				switch(res)
				{
					case 1: type = NurtureType::None; break;
					case 2: type = NurtureType::Breakfasts; break;
					case 3: type = NurtureType::AllIncluded; break;
				}

				for(size_t i = 0; i < travels.size(); i++)
				{
					if(travels[i].nurture == type)
						tmp_travels.push_back(travels[i]);
				}
			}
			break;
		case 5:
			{
				size_t min_days, max_days;
				cout<<"Введите минимальное кол-во дней:";
				min_days = InputArithmetic<size_t>();
				cout<<"Введите максимальное кол-во дней:";
				max_days = InputArithmetic<size_t>(min_days);

				for(size_t i = 0; i < travels.size(); i++)
				{
					if(travels[i].days >= min_days && travels[i].days <= max_days)
						tmp_travels.push_back(travels[i]);
				}
			}
			break;
		case 6:
			{
				size_t min_cost, max_cost;
				cout<<"Введите минимальную цену:";
				min_cost = InputArithmetic<size_t>();
				cout<<"Введите максимальную цену:";
				max_cost = InputArithmetic<size_t>(min_cost);

				for(size_t i = 0; i < travels.size(); i++)
				{
					if(travels[i].cost >= min_cost && travels[i].cost <= max_cost)
						tmp_travels.push_back(travels[i]);
				}
			}
			break;
	}

	return tmp_travels;
}

#include <algorithm>

vector<Travel> SortTravels(const vector<Travel> &travels)
{
	if(travels.empty())
		return {};

	vector<Travel> tmp_travels = travels;
	cout<<"Выберите тип сортировки:"<<endl;
	cout<<"1. По Типу"<<endl;
	cout<<"2. По стране"<<endl;
	cout<<"3. По типу транспорта"<<endl;
	cout<<"4. По типу питания"<<endl;
	cout<<"5. По кол-ву дней"<<endl;
	cout<<"6. По цене"<<endl;

	int res = InputArithmetic<int>(1, 6);

	switch(res)
	{
		case 1:
			sort(tmp_travels.begin(), tmp_travels.end(), [](const Travel &tr1, const Travel &tr2)
			{
				return tr1.type < tr2.type;
			});
			break;
		case 2:
			sort(tmp_travels.begin(), tmp_travels.end(), [](const Travel &tr1, const Travel &tr2)
			{
				return tr1.country < tr2.country;
			});
			break;
		case 3:
			sort(tmp_travels.begin(), tmp_travels.end(), [](const Travel &tr1, const Travel &tr2)
			{
				return tr1.vehicle < tr2.vehicle;
			});
			break;
		case 4:
			sort(tmp_travels.begin(), tmp_travels.end(), [](const Travel &tr1, const Travel &tr2)
			{
				return tr1.nurture < tr2.nurture;
			});
			break;
		case 5:
			sort(tmp_travels.begin(), tmp_travels.end(), [](const Travel &tr1, const Travel &tr2)
			{
				return tr1.days < tr2.days;
			});
			break;
		case 6:
			sort(tmp_travels.begin(), tmp_travels.end(), [](const Travel &tr1, const Travel &tr2)
			{
				return tr1.cost < tr2.cost;
			});
			break;
	}

	return tmp_travels;
}

vector<Travel> FindByTypeMaxCostDesc(const vector<Travel> &travels)
{
	if(travels.empty())
		return {};

	vector<Travel> tmp_travels;

	TravelType type;
	cout<<"Выберите тип:"<<endl;
	cout<<"1. Отдых"<<endl;
	cout<<"2. Экскурсионный тур"<<endl;
	cout<<"3. Лечение"<<endl;
	cout<<"4. Шоппинг"<<endl;
	cout<<"5. Круиз"<<endl;

	int res = InputArithmetic<int>(1, 5);
	switch(res)
	{
		case 1: type = TravelType::Rest; break;
		case 2: type = TravelType::ExcursionTour; break;
		case 3: type = TravelType::Treatment; break;
		case 4: type = TravelType::Shoping; break;
		case 5: type = TravelType::Cruise; break;
	}

	size_t max_cost;
	cout<<"Введите максимальную цену: ";
	max_cost = InputArithmetic<size_t>();

	for(size_t i = 0; i < travels.size(); i++)
	{
		if(travels[i].type == type && travels[i].cost < max_cost)
			tmp_travels.push_back(travels[i]);
	}

	sort(tmp_travels.begin(), tmp_travels.end(), [](const Travel &tr1, const Travel &tr2)
	{
		return tr1.cost > tr2.cost;
	});

	return tmp_travels;
}

bool InputYesNo()
{
	string str;
	while(true)
	{
		getline(cin, str);
		if(str == "Да" || str == "да")
			return true;
		else if(str == "Нет" || str == "нет")
			return false;
	}
}

void BuyTravel(vector<Travel>& travels)
{
	if (travels.empty())
		return;

	ShowTravels(travels);

	cout << "Введите индекс путевки для покупки: ";
	size_t ind = InputArithmetic<size_t>(0, travels.size() - 1);

	string name, sname, pname, series;
	uint32_t num;

	cout << "Введите ваше имя: ";
	getline(cin, name);
	cout << "Введите вашу фамилию: ";
	getline(cin, sname);
	cout << "Введите ваше отчество: ";
	getline(cin, pname);
	while (true)
	{
		cout << "Введите серию паспорта (две заглавные латинский буквы): ";
		getline(cin, series);
		if (series.size() != 2)
			cout << "Неверный формат серии!" << endl;
		else
		{
			if (!(series[0] >= 'A' && series[0] <= 'Z' && series[1] >= 'A' && series[1] <= 'Z'))
				cout << "Неверный формат серии!" << endl;
			else
				break;
		}
	}

	cout << "Введите номер паспорта: ";
	num = InputArithmetic<uint32_t>();
	cout << "Вы поупаете:" << endl;
	ShowTravel(travels[ind]);
	cout << "Ваши данные: " << endl;
	cout << "ФИО: " << sname << " " << name << " " << pname << endl;
	cout << "Паспортные данные: " << series << num << endl;

	cout << "Вы подтверждаете действие?(Да/Нет):" << endl;
	bool choice = InputYesNo();

	if (choice)
	{
		cout << "Покупка успешно совершена!" << endl;
		travels.erase(travels.begin() + ind);
	}
	else
	{
		cout << "Покупка отменена!" << endl;
	}
}

//admin
void AdminPanel(vector<Travel> &travels, vector<User> &users, const Auth &ignore)
{
	bool is_run = true;

	while(is_run)
	{
		cout<<"Выберите действие:"<<endl;
		cout<<"1. Работа с пользователями"<<endl;
		cout<<"2. Работа с поездками"<<endl;
		cout<<"3. Выход"<<endl;

		int res = InputArithmetic<int>(1, 3);
		switch(res)
		{
			case 1:
				AdminPanelUsers(users, ignore);
				break;
			case 2:
				AdminPanelTravels(travels);
				break;
			case 3:
				is_run = false;
				break;
		}
	}
}

void AdminPanelUsers(vector<User> &users, const Auth &ignore)
{
	bool is_run = true;

	vector<User> tmp_users;
	while(is_run)
	{
		cout<<"Выберите действие:"<<endl;
		cout<<"1. Вывод всех пользователей"<<endl;
		cout<<"2. Поиск пользователей"<<endl;
		cout<<"3. Сортировка пользователей и вывод"<<endl;
		cout<<"4. Создание нового пользователя"<<endl;
		cout<<"5. Блокировка доступа пользователю"<<endl;
		cout<<"6. Выдача доступа пользователю"<<endl;
		cout<<"7. Удаление пользователя"<<endl;
		cout<<"8. Выход"<<endl;

		int res = InputArithmetic<int>(1, 8);
		switch(res)
		{
			case 1:
				if(users.empty())
					cout<<"Пользователей нет!"<<endl;
				ShowUsers(users);
				break;
			case 2:
				tmp_users = FindUsers(users);
				if(tmp_users.empty())
					cout<<"Никого не найдено!"<<endl;
				else
					ShowUsers(tmp_users);
				break;
			case 3:
				tmp_users = SortUsers(users);
				if(tmp_users.empty())
					cout<<"Никого не найдено!"<<endl;
				else
					ShowUsers(tmp_users);
				break;
			case 4:
				AddUser(users);
				break;
			case 5:
				BlockUser(users, ignore);
				break;
			case 6:
				GiveAccessToUser(users);
				break;
			case 7:
				DeleteUser(users, ignore);
				break;
			case 8:
				is_run = false;
				break;
		}
	}
}

void AdminPanelTravels(vector<Travel> &travels)
{
	bool is_run = true;

	vector<Travel> tmp_travels;
	while(is_run)
	{
		cout<<"1. Вывод всех путевок"<<endl;
		cout<<"2. Поиск путевок"<<endl;
		cout<<"3. Сортировка путевок"<<endl;
		cout<<"4. Поиск путевок одного типа с ограничением по цене по убыванию стоимости"<<endl;
		cout<<"5. Создание новой поездки"<<endl;
		cout<<"6. Выход"<<endl;

		int res = InputArithmetic<int>(1, 6);
		switch(res)
		{
			case 1:
				if(travels.empty())
					cout<<"Путевок нет!"<<endl;
					ShowTravels(travels);
				break;
			case 2:
				tmp_travels = FindTravels(travels);
				if(tmp_travels.empty())
					cout<<"Ничего не найдено!"<<endl;
				else
					ShowTravels(tmp_travels);
				break;
			case 3:
				tmp_travels = SortTravels(travels);
				if(tmp_travels.empty())
					cout<<"Ничего не найдено!"<<endl;
				else
					ShowTravels(tmp_travels);
				break;
			case 4:
				tmp_travels = FindByTypeMaxCostDesc(travels);
				if(tmp_travels.empty())
					cout<<"Ничего не найдено!"<<endl;
				else
					ShowTravels(tmp_travels);
				break;
			case 5:
				AddTravel(travels);
				break;
			case 6:
				is_run = false;
				break;
		}
	}
}

void AddTravel(vector<Travel> &travels)
{
	Travel tr;
	cout<<"Выберите тип поездки: "<<endl;
	cout<<"1. Отдых"<<endl;
	cout<<"2. Экскурсионный тур"<<endl;
	cout<<"3. Лечение"<<endl;
	cout<<"4. Шоппинг"<<endl;
	cout<<"5. Круиз"<<endl;

	int res = InputArithmetic<int>(1, 5);
	switch(res)
	{
		case 1: tr.type = TravelType::Rest; break;
		case 2: tr.type  = TravelType::ExcursionTour; break;
		case 3: tr.type  = TravelType::Treatment; break;
		case 4: tr.type  = TravelType::Shoping; break;
		case 5: tr.type  = TravelType::Cruise; break;
	}

	cout<<"Введите страну: ";
	//while(true)
	//{
		//bool is_found = false;
		getline(cin, tr.country);
		/*for (size_t i = 0; i < tr.country.size(); i++)
		{
			if((tr.country[i] >= 160 && tr.country[i] <= 255) || (tr.country[i] > 65 && tr.country[i] <= 90) || (tr.country[i] > 97 && tr.country[i] <= 122))
				continue;
			else
			{
				is_found = true;
				break;
			}
		}
		if(!is_found)
			break;*/
	//}

	cout<<"Выберите тип:"<<endl;
	cout<<"1. Автомобиль"<<endl;
	cout<<"2. Автобус"<<endl;
	cout<<"3. Самолет"<<endl;
	cout<<"4. Корабль"<<endl;

	res = InputArithmetic<int>(1, 4);
	switch(res)
	{
		case 1: tr.vehicle = TransferVehicle::Auto; break;
		case 2: tr.vehicle = TransferVehicle::Bus; break;
		case 3: tr.vehicle = TransferVehicle::Airplane; break;
		case 4: tr.vehicle = TransferVehicle::Ship; break;
	}

	cout<<"Выберите тип:"<<endl;
	cout<<"1. Без питания"<<endl;
	cout<<"2. Только завтраки"<<endl;
	cout<<"3. Все включено"<<endl;

	res = InputArithmetic<int>(1, 3);
	switch(res)
	{
		case 1: tr.nurture = NurtureType::None; break;
		case 2: tr.nurture = NurtureType::Breakfasts; break;
		case 3: tr.nurture = NurtureType::AllIncluded; break;
	}

	cout<<"Введите кол-во дней:";
	tr.days = InputArithmetic<size_t>();

	cout<<"Введите цену:";
	tr.cost = InputArithmetic<size_t>();

	travels.push_back(tr);
	cout<<"Поездка: "<<endl;
	ShowTravel(tr);
	cout<<"успешно созданана!"<<endl;
}

void DeleteUser(vector<User> &users, const Auth &ignore)
{
	cout<<"Введите индекс удаляемого пользователя"<<endl;
	size_t ind = InputArithmetic<size_t>(0, users.size() - 1);
	if(ignore.login == users[ind].login)
	{
		cout<<"Вы не можете удалить самого себя!"<<endl;
		return;
	}

	cout<<"Удаляемый пользователь: "<<endl;
	ShowUser(users[ind]);

	cout<<"Вы действительно хотите удалить данного пользователя(Да)/(Нет)"<<endl;
	bool choice = InputYesNo();

	if(choice)
	{
		cout<<"Пользователь успешно удален!"<<endl;
		users.erase(users.begin() + ind);
	}
	else
	{
		cout<<"Удаление отменено!"<<endl;
	}
}

void AddUser(vector<User> &users)
{
	User usr;
	string tmp_str;
	while(true)
	{
		cout<<"Введите логин нового пользователя: "<<endl;
		getline(cin, tmp_str);
		auto it = find_if(users.begin(), users.end(), [&](const User &u)
		{
			return u.login == tmp_str;
		});

		if(it == users.end())
		{
			usr.login = tmp_str;
			break;
		}
		else
			cout<<"Пользователь с таким логином уже существует!"<<endl;
	}

	cout<<"Введите пароль нового пользователя: "<<endl;
	getline(cin, tmp_str);
	usr.hashed_pwd = hash<string>{}(tmp_str);

	cout<<"Введите роль нового пользователя: "<<endl;
	cout<<"1. Администратор"<<endl;
	cout<<"2. Клиент"<<endl;

	int res = InputArithmetic<int>(1, 2);
	switch(res)
	{
		case 1: usr.role = UserRole::Admin; break;
		case 2: usr.role = UserRole::Traveler; break;
	}

	cout<<"Введите тип доступа:"<<endl;
	cout<<"1. Открыт"<<endl;
	cout<<"2. Заблокирован"<<endl;
	cout<<"3. Доступ запрошен"<<endl;

	res = InputArithmetic<int>(1, 3);
	switch(res)
	{
		case 1: usr.access = UserAccess::Open; break;
		case 2: usr.access  = UserAccess::Blocked; break;
		case 3: usr.access  = UserAccess::OnRequest; break;
	}

	users.push_back(usr);
	cout<<"Пользователь: "<<endl;
	ShowUser(usr);
	cout<<"успешно создан!"<<endl;
}

void GiveAccessToUser(vector<User> &users)
{
	cout<<"Введите индекс пользователя"<<endl;
	size_t ind = InputArithmetic<size_t>(0, users.size() - 1);
	if(users[ind].access == UserAccess::Open)
	{
		cout<<"Пользователь уже имеет доступ!"<<endl;
		return;
	}

	cout<<"Пользователь, которому выдается доступ: "<<endl;
	ShowUser(users[ind]);

	cout<<"Вы действительно хотите выдать доступ(Да)/(Нет)"<<endl;
	bool choice = InputYesNo();

	if(choice)
	{
		cout<<"Пользователю успешно выдан доступ!"<<endl;
		users[ind].access = UserAccess::Open;
	}
	else
	{
		cout<<"Выдача доступа отменена!"<<endl;
	}
}

void BlockUser(vector<User> &users, const Auth &ignore)
{
	cout<<"Введите индекс пользователя"<<endl;
	size_t ind = InputArithmetic<size_t>(0, users.size() - 1);
	if(users[ind].login == ignore.login)
	{
		cout<<"Вы не можете заблокировать самого себя!"<<endl;
		return;
	}

	if(users[ind].access == UserAccess::Blocked)
	{
		cout<<"Пользователь уже заблокирован!"<<endl;
		return;
	}

	cout<<"Пользователь, который блокируется: "<<endl;
	ShowUser(users[ind]);

	cout<<"Вы действительно хотите заблокировать доступ(Да)/(Нет)"<<endl;
	bool choice = InputYesNo();

	if(choice)
	{
		cout<<"Пользователю успешно заблокирован доступ!"<<endl;
		users[ind].access = UserAccess::Blocked;
	}
	else
	{
		cout<<"Блокировка доступа отменена!"<<endl;
	}
}

vector<User> FindUsers(const vector<User> &users)
{
	if(users.empty())
		return {};

	vector<User> out_users;
	cout<<"Выберите тип поиска: "<<endl;
	cout<<"1. По логину"<<endl;
	cout<<"2. По роли"<<endl;
	cout<<"3. По типу доступа"<<endl;

	int res = InputArithmetic<int>(1, 3);

	switch(res)
	{
		case 1:
			{
				string str;
				cout<<"Введите логин: ";
				getline(cin, str);
				auto it = find_if(users.begin(), users.end(), [&](const User &u1)
				{
					return u1.login == str;
				});

				if(it == users.end())
					cout<<"Никого не найдено!"<<endl;
				else
					out_users.push_back(*it);
			}
			break;
		case 2:
			{
				cout<<"Введите роль:"<<endl;
				cout<<"1. Администратор"<<endl;
				cout<<"2. Клиент"<<endl;

				res = InputArithmetic<int>(1, 2);
				UserRole role;
				switch(res)
				{
					case 1: role = UserRole::Admin; break;
					case 2: role = UserRole::Traveler; break;
				}

				for(size_t i = 0; i < users.size(); i++)
				{
					if(users[i].role == role)
						out_users.push_back(users[i]);
				}
			}
			break;
		case 3:
			{
				cout<<"Введите тип доступа:"<<endl;
				cout<<"1. Открыт"<<endl;
				cout<<"2. Заблокирован"<<endl;
				cout<<"3. Доступ запрошен"<<endl;

				res = InputArithmetic<int>(1, 3);
				UserAccess acc;
				switch(res)
				{
					case 1: acc = UserAccess::Open; break;
					case 2: acc = UserAccess::Blocked; break;
					case 3: acc = UserAccess::OnRequest; break;
				}

				for(size_t i = 0; i < users.size(); i++)
				{
					if(users[i].access == acc)
						out_users.push_back(users[i]);
				}
			}
			break;
	}

	return out_users;
}

vector<User> SortUsers(const vector<User> &users)
{
	if(users.empty())
		return {};

	vector<User> out_users = users;
	cout<<"Выберите тип сортировки: "<<endl;
	cout<<"1. По логину"<<endl;
	cout<<"2. По роли"<<endl;
	cout<<"3. По типу доступа"<<endl;

	int res = InputArithmetic<int>(1, 3);

	switch(res)
	{
		case 1:
			sort(out_users.begin(), out_users.end(), [](const User &u1, const User &u2)
			{
				return u1.login < u2.login;
			});
			break;
		case 2:
			sort(out_users.begin(), out_users.end(), [](const User &u1, const User &u2)
			{
				return u1.role < u2.role;
			});
			break;
		case 3:
			sort(out_users.begin(), out_users.end(), [](const User &u1, const User &u2)
			{
				return u1.access < u2.access;
			});
			break;
	}

	return out_users;
}
