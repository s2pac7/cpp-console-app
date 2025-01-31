#include <iostream>
#include "User.h"
#include "Auth.h"
#include "Common.hpp"
#include <filesystem>

//#include <Windows.h>

//пути для файлов, где записаны пользователи и поездки
static const string DB_PATH_USERS = "users.txt";
static const string DB_PATH_TRAVELS = "travels.txt";

//чтение файлов и запись данных в вектора
bool ReadDb(vector<User> &users, vector<Travel> &travels)
{
	bool is_error = false;
	if(!filesystem::exists(DB_PATH_USERS))
	{
		cout<<DB_PATH_USERS<<" не существует!"<<endl;
		cout<<"В базу сохранен резервный аккаунт администратора!"<<endl;
		users = rescue;
	}
	else
	{
		auto users_pr = ReadAllUsers(DB_PATH_USERS);
		if(!users_pr.second.empty())
		{
			is_error = true;
			cout<<users_pr.second<<endl;
		}
		else
			users = users_pr.first;
	}

	if (!filesystem::exists(DB_PATH_TRAVELS))
		return is_error;

	auto travels_pr = ReadAllTravels(DB_PATH_TRAVELS);

	if(!travels_pr.second.empty())
	{
		is_error = true;
		cout<<travels_pr.second<<endl;
	}
	else
		travels = travels_pr.first;

	return is_error;
}

//запись данных в файл
void WriteDb(const vector<User> &users, const vector<Travel> &travels)
{
	WriteAllUsers(DB_PATH_USERS, users);
	WriteAllTravels(DB_PATH_TRAVELS, travels);
}

namespace win
{
#include <Windows.h>
}

int main()
{
	setlocale(LC_ALL, "Rus");
	win::SetConsoleCP(1251);
	win::SetConsoleOutputCP(1251);

	vector<User> users_db;
	vector<Travel> travels_db;
	bool db_error = ReadDb(users_db, travels_db);
	if(db_error)
		return EXIT_FAILURE;

	bool is_run = true;
	Auth target_auth;
	while(is_run)
	{
		cout<<"Выберите действие:"<<endl;
		cout<<"1. Регистрация"<<endl;
		cout<<"2. Авторизация"<<endl;
		cout<<"3. Выход"<<endl;

		int res = InputArithmetic<int>(1, 3);

		switch(res)
		{
			case 1:
				system("cls");
				target_auth = InputAuth();
				Register(target_auth, users_db);
				break;
			case 2:
				system("cls");
				target_auth = InputAuth();
				if(LogIn(target_auth, users_db))
				{
					if(target_auth.role == UserRole::Admin)
						AdminPanel(travels_db, users_db, target_auth);
					else
						UserPanel(travels_db);
				}
				break;
			case 3:
				is_run = false;
				break;
		}
	}

	WriteDb(users_db, travels_db);

	return EXIT_SUCCESS;
}
