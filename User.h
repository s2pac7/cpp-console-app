#pragma once

#include <string>
#include <functional>
#include "Travel.h"

struct Auth;

using namespace std;

enum UserRole
{
	Admin = 0,
	Traveler = 1
};

enum UserAccess
{
	Open = 0,
	Blocked = 1,
	OnRequest = 2
};

//стркутура пользователя(админ/клиент)
struct User
{
	string login;
	size_t hashed_pwd;
	UserRole role;
	UserAccess access;
};

//Преобразовывают поль и доступ в строку
string GetRole(const User &usr);
string GetAccess(const User &usr);

//если нет файла с пользователями, то берем запасной аккаунт от сюда
static const vector<User> rescue
{
	{
		"Admin",
		hash<string>{}("admin"),
		UserRole::Admin,
		UserAccess::Open
	}
};

//common
//считывает всех пользователей из файла(возвращает вектор пользователей или строку с ошибкой)
pair<vector<User>, string> ReadAllUsers(const string &path);

//записывает всех пользователей в файл
void WriteAllUsers(const string &path, const vector<User> &users);

//traveler
//панель пользователя
void UserPanel(vector<Travel> &travels);

//возвращает вектор поездок по заданным параметрам поиска
vector<Travel> FindTravels(const vector<Travel> &travels);

//возвращает вектор поездок по заданным параметрам сортировки
vector<Travel> SortTravels(const vector<Travel> &travels);

//индивидуальное
vector<Travel> FindByTypeMaxCostDesc(const vector<Travel> &travels);

//покупка
void BuyTravel(vector<Travel> &travels);

//admin
//админская панель
void AdminPanel(vector<Travel> &travels, vector<User> &users, const Auth &ignore);

//админская панель работы с юзерами
void AdminPanelUsers(vector<User> &users, const Auth &ignore);

//админская панель работы с поездками
void AdminPanelTravels(vector<Travel> &travels);

//добавляет новую поездку в вектор
void AddTravel(vector<Travel> &travels);

//удаляет пользователя из вектора
void DeleteUser(vector<User> &users, const Auth &ignore);

//добавляет нового пользователя в вектор
void AddUser(vector<User> &users);

//выдает доступ пользователю
void GiveAccessToUser(vector<User> &users);

//блокирует пользователя
void BlockUser(vector<User> &users, const Auth &ignore);

//поиск пользователей по параметрам и возвращает вектор пользователей
vector<User> FindUsers(const vector<User> &users);

//сортировка пользователей по параметрам и возвращает вектор пользователей
vector<User> SortUsers(const vector<User> &users);
