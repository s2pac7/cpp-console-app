#pragma once

#include "User.h"

//значения таблицы пользователей, которые находятся в заголовке таблицы
static const string USER_TABLE_LOGIN_STR = "Логин";
static const string USER_TABLE_ROLE_STR = "Роль";
static const string USER_TABLE_ACCESS_STR = "Доступ";
static const size_t USER_TABLE_IND_COUNT_BASE = 3;

//хранит максимальные значения полей таблицы пользователей
struct TableOutputSizesUser
{
	size_t login_count;
	size_t role_count;
	size_t access_count;
};

//считают размеры для таблицы пользователей
TableOutputSizesUser CalculateSizesUser(const vector<User> &users);
TableOutputSizesUser CalculateSizesUser(const User &user);

//для вывода таблицы пользователей
void ShowFooterUser(TableOutputSizesUser sizes, bool show_ind = false);
void ShowHeaderUser(TableOutputSizesUser sizes, bool show_ind = false);
void CreateTableStringUser(TableOutputSizesUser sizes, const User &usr, bool show_ind = false, size_t ind = 0);
void ShowUser(const User &user, bool show_header = true);
void ShowUsers(const vector<User> &users);
