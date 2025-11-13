#include <iostream>
#include <windows.h>
#include <limits>
#include <string>
#include <iomanip>

// --------------------Учетки---------------------------------
size_t userSize = 2;
std::string userStatus[3]{ "Крутой мопс", " мопс", "Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin","user" };
std::string* passArr = new std::string[userSize]{ "1234","123" };
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
void ShowStorage(int mode = 0);
void AddStorageItem();

template<typename ArrType>
void FillArray(ArrType* dynamicArray, ArrType* staticArray, size_t arraySize);

//-----------------------------------------------------------


// ----------------Служебные----------------------------------

void Start();
bool Login();
void ShowSuperAdminMenu();
bool IsNumber(const std::string& str);
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
	
	std::string choose;

	if (Login())
	{
		if (currentStatus == userStatus[0])
		{
			while (true)
			{
				std::cout << "Выберетие склад\n1 - Готовый склад\n2 - Создать новый\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					system("cls");
					CreateStorage();
					ShowSuperAdminMenu();
				}
				else if (choose == "2")
				{
					// создать новый склад
				}
				else
				{
					Err();
				}
			}
			CreateStorage();
		}
		else if (currentStatus == userStatus[1])
		{
			CreateStorage();
		}
		else if (currentStatus == userStatus[2])
		{
			CreateStorage();
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
		std::cout << "\t\t\tМагазин ЧИУВАУВА\t\t\t\n";
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
			if (login == loginArr[i] && pass == passArr[i])
			{
				system("cls");
				std::cout << "Пользователь: " << loginArr[i] << "\n\nДобыр ден!\n\n";
				std::cout << "Ваш статус: " << statusArr[i] << "\n\n\n";
				currentStatus = statusArr[i];
				return true;
			}
		}
		Err();
	}
}
void ShowSuperAdminMenu()
{
	std::string choose;
	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "3 - Пополнить склад\n";
		std::cout << "4 - Списать товар\n";
		std::cout << "5 - Изменить цену\n";
		std::cout << "6 - Редактировать склад\n";
		std::cout << "7 - Редактировать персонал\n";
		std::cout << "8 - Отчет о прибыли\n";
		std::cout << "0 - Закрыть смену\n";
		std::cout << "Ввод: ";
		Getline(choose);
		
		if (choose == "1")
		{

		}
		else if (choose == "2")
		{
			ShowStorage();
		}
		else if (choose == "3")
		{
			
		}
		else if (choose == "4")
		{

		}
		else if (choose == "5")
		{

		}
		else if (choose == "6")
		{

		}
		else if (choose == "7")
		{

		}
		else if (choose == "8")
		{

		}
		else if (choose == "0")
		{

		}
		else
		{
			Err();
		}

	}
}
bool IsNumber(const std::string& str)
{
	if (str.size() <= 0 || str.size() >= 10)
	{
		std::cout << "Ошибка длины числа. Максимум девятизначные числа!\n\n";
		Sleep(1500);
		return false;
	}
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
		{
			std::cout << "Введенные данные не являются числом!\n\n";
			Sleep(1500);
			return false;
		}
	}
	return true;

}
inline void Getline(std::string& str)
{
	std::getline(std::cin, str, '\n');
}
inline void Err(int time)
{
	std::cout << "Некорректный ввод\n\n\n";
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

	FillArray(idArr, id, storageSize);
	FillArray(nameArr, name, storageSize);
	FillArray(countArr, count, storageSize);
	FillArray(priceArr, price, storageSize);
}

void ShowStorage(int mode)
{
	if (mode == 0)
	{
		system("cls");
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Кол-во\t" << "Цена\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t" << countArr[i] << "\t" << priceArr[i] << "\n";
		}
		system("pause");
		system("cls");
	}
	else if (mode == 1)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Кол-во\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t" << countArr[i] << "\n";
		}
	}
	else if (mode == 2)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" <<"Цена\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t" << priceArr[i] << "\n";
		}
	}
}

void AddStorageItem()
{
	std::string chooseId, chooseCount, choose;
	unsigned int count = 0, id = 0;

	while (true)
	{
		system("cls");
		ShowStorage(1);
		std::cout << "Введите ID товара или слово \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции пополнение товара!\n";
			Sleep(1500);
			break;
		}
		std::cout << "Введите кол-во товара для пополнения: ";
		Getline(chooseCount);
		
		
	}

}

template<typename ArrType>
void FillArray(ArrType* dynamicArray, ArrType* staticArray, size_t arraySize)
{
	for (size_t i = 0; i < arraySize; i++)
	{
		dynamicArray[i] = staticArray[i];
	}
}
