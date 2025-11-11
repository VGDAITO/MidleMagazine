#include <iostream>
#include <windows.h>
#include <limits>
#include <string>
#include <iomanip>

// --------------------Учетки---------------------------------
size_t userSize = 2;
std::string userStatus[3]{ "Крутой мопс", " мопс", "Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin", "user" };
std::string* passArr = new std::string[userSize]{ "1234", "123" };
std::string* statusArr = new std::string[userSize]{ userStatus[0], userStatus[2]};
std::string currentStatus;
//-----------------------------------------------------------


// ------------------------Склад-----------------------------
size_t storageSize = 0;
unsigned int* idArr = nullptr;
std::string* nameArr = nullptr;
unsigned int* countArr = nullptr;
double* priceArr = nullptr;
bool isStorageCreated = false;

void CreateStorage();
//-----------------------------------------------------------


// ----------------Служебные----------------------------------

void Start();
bool Login();
inline void Getline(std::string& str);
inline void Err(int time = 1500);
//------------------------------------------------------------
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	Start();
	delete[]loginArr, passArr, statusArr;
	if (isStorageCreated)
	{
		delete[]idArr, nameArr, countArr, priceArr;
	}

	return 0;
}

void Start()
{
	
	std::cout << "\t\t\tМагазин ЧИУВАУВА\t\t\t\n";

	if (Login())
	{
		if (currentStatus == userStatus[0])
		{

		}
		else if (currentStatus == userStatus[1])
		{

		}
		else if (currentStatus == userStatus[2])
		{

		}
	}
	else
	{
		system("cls");
		std::cout << "Завершение работы программы\n\n\n";
	}

}
bool Login()
{
	std::string login, pass;

	while (true)
	{
		std::cout << "Введите логин: ";
		Getline(login);
		std::cout << "\nВведите пароль: ";
		Getline(pass);

		if (login == "exit" && pass == "exit")
		{
			currentStatus = "";
			return false;
		}

		for (size_t i = 0; i < userSize; i++)
		{
			if (login == loginArr[0] && pass == passArr[0])
			{
				std::cout << "Пользователь: " << loginArr[0] << "\n\nДобыр ден!\n\n";
				std::cout << "Ваш статус: " << statusArr[0] << "\n\n\n";
				currentStatus = statusArr[i];
				return true;
			}
		}
		Err();
	}
}
inline void Getline(std::string& str)
{
	std::getline(std::cin, str, '\n');
}
inline void Err(int time)
{
	std::cout << "Некорректный ввод\n\n'n";
	Sleep(time);
	system("cls");
}

void CreateStorage()
{
	const int staticSize = 10;
	
	unsigned int id[staticSize]{ 1,2,3,4,5,6,7,8,9,10 };
	std::string name[staticSize]
	{
		"Мопс","Алабай","Чихуахуа","Сиба-ину", "Доберман","Лабрадор","Бультерьер","Ротвейлер","Шпиц","The dog house"
	};
	unsigned int count[staticSize]{1,5,3,2,10,7,9,8,4,777};
	double price[staticSize]{ 40000, 45000, 35000, 250000,25000, 45000, 70000, 30000, 50000, 7777777 };
	storageSize = staticSize;
	idArr = new unsigned int[storageSize];
	nameArr = new std::string[storageSize];
	countArr = new unsigned int[storageSize];
	priceArr = new double[storageSize];
	isStorageCreated = true;
}