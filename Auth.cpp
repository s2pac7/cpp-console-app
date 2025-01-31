#include "Auth.h"
#include "Common.hpp"
#include <iostream>


	//#include <windows.h>
	#include <conio.h>


string EnterPassword()
{
	/*string tmp_str;
	char symbol = _getch();
	while(symbol != '\n')
	{
		if(symbol == 127)
		{
			if(!tmp_str.empty())
			{
				tmp_str.pop_back();
				cout<<"\b \b";
			}
		}
		else
		{
			cout<<"*";
			tmp_str.push_back(symbol);
		}
		symbol = _getch();
	}
	cout<<"\n";
	return tmp_str;*/

	string password;
	char c;

	while (true) {
		int i = 0;
		while ((c = _getch()) != 13)
		{
			if (c == 8) {
				if (i == 0)
					continue;
				cout << (char)8 << ' ' << (char)8;
				if (!password.empty())
					password.pop_back();
				i--;
				continue;
			}
			password += c;
			_putch('*');
			i++;
		}
		/*if (i < 5 || i>11) {
			cout << "\n*������ ������ ���� ������� 4 �������� � ������ 11, ��������� ����*" << endl;
			password = "";
		}*/
		//else
			break;
	}
	return password;
}

Auth InputAuth()
{
	Auth out_auth;
	cout<<"Введите логин: ";
	getline(cin, out_auth.login);
	cout<<"Введите пароль: ";
	out_auth.hashed_pwd = hash<string>{}(EnterPassword());
	cout<<endl<<"Роль:"<<endl;
	cout<<"1. Админ"<<endl;
	cout<<"2. Клиент"<<endl;
	int res = InputArithmetic<int>(1, 2);
	switch(res)
	{
		case 1: out_auth.role = UserRole::Admin; break;
		case 2: out_auth.role = UserRole::Traveler; break;
	}
	return out_auth;
}

auto FindAuthExistance(const Auth &auth, const vector<User> &users, bool check_pwd)
{
	auto it = find_if(users.begin(), users.end(), [&](const User &u)
	{
		if(auth.login == u.login)
		{
			if(auth.role == u.role)
			{
				if(check_pwd)
				{
					if(auth.hashed_pwd == u.hashed_pwd)
						return true;
					else
						return false;
				}
				else
					return true;
			}
		}
		return false;
	});

	return it;
}

void Register(const Auth &reg, vector<User> &users)
{
	auto it = FindAuthExistance(reg, users, false);
	if(it != users.end())
		cout<<"Пользователь уже существует!"<<endl;
	else
	{
		cout<<"Вы успешно зарегистрировались!"<<endl;
		//cout<<"�������������� ���������� ���� ��������� � ������ ��� �������!"<<endl;
		users.push_back(AuthToUser(reg));
	}
}

bool LogIn(const Auth &log_in, vector<User> &users)
{
	auto it = FindAuthExistance(log_in, users, true);
	if(it == users.end())
	{
		cout<<"Пользователь не существует!"<<endl;
		return false;
	}
	else if(it->access == UserAccess::Blocked)
	{
		cout<<"Вы были заблокированы!"<<endl;
		return false;
	}
	else if(it->access == UserAccess::OnRequest)
	{
		cout<<"Ваш аккаунт на рассмотрении!"<<endl;
		return false;
	}
	else
		return true;
}

User AuthToUser(const Auth &auth)
{
	User usr;
	usr.login = auth.login;
	usr.hashed_pwd = auth.hashed_pwd;
	usr.role = auth.role;
	usr.access = UserAccess::OnRequest;
	return usr;
}
