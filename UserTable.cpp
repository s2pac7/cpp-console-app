#include "UserTable.h"
#include <iostream>
#include <iomanip>

TableOutputSizesUser CalculateSizesUser(const vector<User> &users)
{
	TableOutputSizesUser tbl;
	tbl.login_count = USER_TABLE_LOGIN_STR.size();
	tbl.role_count = USER_TABLE_ROLE_STR.size();
	tbl.access_count = USER_TABLE_ACCESS_STR.size();
	for(size_t i = 0; i < users.size(); i++)
	{
		if(size_t login_size = users[i].login.size(); login_size > tbl.login_count)
			tbl.login_count = login_size;
		if(size_t role_size = GetRole(users[i]).size(); role_size > tbl.role_count)
			tbl.role_count = role_size;
		if(size_t access_size = GetAccess(users[i]).size(); access_size > tbl.access_count)
			tbl.access_count = access_size;
	}

	return tbl;
}

TableOutputSizesUser CalculateSizesUser(const User &user)
{
	TableOutputSizesUser tbl;
	tbl.login_count = USER_TABLE_LOGIN_STR.size();
	tbl.role_count = USER_TABLE_ROLE_STR.size();
	tbl.access_count = USER_TABLE_ACCESS_STR.size();

	if(size_t login_size = user.login.size(); login_size > tbl.login_count)
		tbl.login_count = login_size;
	if(size_t role_size = GetRole(user).size(); role_size > tbl.role_count)
		tbl.role_count = role_size;
	if(size_t access_size = GetAccess(user).size(); access_size > tbl.access_count)
		tbl.access_count = access_size;

	return tbl;
}

void ShowFooterUser(TableOutputSizesUser sizes, bool show_ind)
{
	if(show_ind)
	{
		cout<<"+";
		for(size_t i = 0; i < USER_TABLE_IND_COUNT_BASE; i++)
			cout<<"-";
	}

	cout<<"+";

	for(size_t i = 0; i < sizes.login_count; i++)
		cout<<"-";
	cout<<"+";

	for(size_t i = 0; i < sizes.role_count; i++)
		cout<<"-";
	cout<<"+";

	for(size_t i = 0; i < sizes.access_count; i++)
		cout<<"-";
	cout<<"+\n";
}

void ShowHeaderUser(TableOutputSizesUser sizes, bool show_ind)
{
	ShowFooterUser(sizes, show_ind);

	if(show_ind)
	{
		cout<<"|";
		int dt = USER_TABLE_IND_COUNT_BASE / 2;
		for(size_t i = 0; i < dt; i++)
			cout<<" ";

		cout<<"#";
		for(size_t i = 0; i < USER_TABLE_IND_COUNT_BASE - dt - 1; i++)
			cout<<" ";
	}

	cout<<"|";

	string tmp_str = USER_TABLE_LOGIN_STR;
	tmp_str.resize(sizes.login_count, ' ');
	for(size_t i = 0; i < tmp_str.size(); i++)
		cout<<tmp_str[i];
	cout<<"|";

	tmp_str = USER_TABLE_ROLE_STR;
	tmp_str.resize(sizes.role_count, ' ');
	for(size_t i = 0; i < tmp_str.size(); i++)
		cout<<tmp_str[i];
	cout<<"|";

	tmp_str = USER_TABLE_ACCESS_STR;
	tmp_str.resize(sizes.access_count, ' ');
	for(size_t i = 0; i < tmp_str.size(); i++)
		cout<<tmp_str[i];
	cout<<"|\n";

	ShowFooterUser(sizes, show_ind);
}

void CreateTableStringUser(TableOutputSizesUser sizes, const User &usr, bool show_ind, size_t ind)
{
	if(show_ind)
		cout<<"|"<<setw(USER_TABLE_IND_COUNT_BASE)<<ind;
	cout<<"|";

	string tmp_str(usr.login);
	tmp_str.resize(sizes.login_count, ' ');
	cout<<tmp_str;
	cout<<"|";

	tmp_str = string(GetRole(usr));
	tmp_str.resize(sizes.role_count, ' ');
	cout<<tmp_str;
	cout<<"|";

	tmp_str = string(GetAccess(usr));
	tmp_str.resize(sizes.access_count, ' ');
	cout<<tmp_str;
	cout<<"|\n";
}

void ShowUser(const User &user, bool show_header)
{
	auto sizes = CalculateSizesUser(user);
	if(show_header)
		ShowHeaderUser(sizes, false);

	CreateTableStringUser(sizes, user, false);
	ShowFooterUser(sizes, false);
}


void ShowUsers(const vector<User> &users)
{
	auto sizes = CalculateSizesUser(users);
	ShowHeaderUser(sizes, true);

	for(size_t i = 0; i < users.size(); i++)
		CreateTableStringUser(sizes, users[i], true, i);
	ShowFooterUser(sizes, true);
}
