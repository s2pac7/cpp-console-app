#pragma once

#include <string>
#include <vector>
#include "User.h"

using namespace std;

//хранит в себе данные, которые ввел пользователь при логине или регистрации
struct Auth
{
	string login;
	size_t hashed_pwd;
	UserRole role;
	UserAccess access;
};

//ввод данных при логине и регистрации
Auth InputAuth();

//ищет, существует ли такой логин и пароль среди users. Возвращает итератор на этот аккаунт
auto FindAuthExistance(const Auth &auth, const vector<User> &users, bool check_pwd);

//регистрация пользователя
void Register(const Auth &reg, vector<User> &users);

//логин пользователя
bool LogIn(const Auth &log_in, vector<User> &users);

//переводит auth в пользователя, который ожидает подтверждения доступа
User AuthToUser(const Auth &auth);
