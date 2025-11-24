#include <iostream>
#include <windows.h>
#include <limits>
#include <string>
#include <iomanip>
#include <unordered_set>

// --------------------Учетки---------------------------------
size_t userSize = 2;
std::string userStatus[3]{ "Крутой мопс", " мопс", "Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin","user" };
std::string* passArr = new std::string[userSize]{ "1234","123" };
std::string* statusArr = new std::string[userSize]{ userStatus[0], userStatus[2]};
std::string currentStatus;

void ChangeUsers();
void ShowUsers();
void AddNewUsers();


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
void RemoveStorageItem();
void ChangePrice();

void AddNewItem();
void ChangeStorage();
void ChangeName();
void DeleteItem();

template<typename ArrType>
void FillArray(ArrType* dynamicArray, ArrType* staticArray, size_t arraySize);

//-----------------------------------------------------------


// ----------------Служебные----------------------------------
std::unordered_set<char> passSymbols;
std::unordered_set<char> loginSymbols;
bool isLoginSetCreated = false;
bool isPassSetCreated = false;

void Start();
bool Login();
void SetLoginSymbols();
void SetPassSymbols();
bool CheckLogin(const std::string &str);
bool CheckPass(const std::string& str);
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
					
					if (isStorageCreated == false)
					{
						CreateStorage();
					}
					system("cls");
					ShowSuperAdminMenu();
				}
				else if (choose == "2")
				{
					if (isStorageCreated == false)
					{
						
					}
					system("cls");
					ShowSuperAdminMenu();
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
			if (isStorageCreated == false)
			{
				CreateStorage();
			}
		}
		else if (currentStatus == userStatus[2])
		{
			if (isStorageCreated == false)
			{
				CreateStorage();
			}
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
void SetLoginSymbols()
{
	for (char i = '0'; i <= '9'; i++)
	{
		loginSymbols.insert(i);
	}
	for (char i = 'a'; i <= 'z'; i++)
	{
		loginSymbols.insert(i);
	}
	for (char i = 'A'; i <= 'Z'; i++)
	{
		loginSymbols.insert(i);
	}
	isLoginSetCreated = true;
}
void SetPassSymbols()
{
	for (char i = '!'; i <= '&'; i++)
	{
		passSymbols.insert(i);
	}
	for (char i = '('; i <= '+'; i++)
	{
		passSymbols.insert(i);
	}

	for (char i = '/'; i <= '~'; i++)
	{
		passSymbols.insert(i);
	}
	
	
	isPassSetCreated = true;
}
bool CheckLogin(const std::string &str)
{
	if (str.size() < 5 || str.size() > 20)
	{
		std::cout << "Ошибка длины логина\n";
		Sleep(1500);
		return false;
	}
	for (char sym : str)
	{
		if (!loginSymbols.count(sym))
		{
			std::cout << "Ошибка некорректный логие\n";
			Sleep(1500);
			return false;
		}

	}
	return true;
}
bool CheckPass(const std::string& str)
{
	if (str.size() < 8 || str.size() > 30)
	{
		std::cout << "Ошибка длины пароля\n";
		Sleep(1500);
		return false;
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
		
		if (choose == "1" && storageSize > 0)
		{

		}
		else if (choose == "2" && storageSize > 0)
		{
			ShowStorage();
		}
		else if (choose == "3" && storageSize > 0)
		{
			AddStorageItem();
		}
		else if (choose == "4" && storageSize > 0)
		{
			RemoveStorageItem();
		}
		else if (choose == "5" && storageSize > 0)
		{
			ChangePrice();
		}
		else if (choose == "6")
		{
			ChangeStorage();
		}
		else if (choose == "7")
		{
			ChangeUsers();
		}
		else if (choose == "8")
		{

		}
		else if (choose == "0")
		{

		}
		else
		{
			if (storageSize < 1)
			{
				std::cout << "Склад пустой\n";
			}
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

void ChangeUsers()
{
	if (isLoginSetCreated == false)
	{
		SetLoginSymbols();
	}
	if (isPassSetCreated == false)
	{
		SetPassSymbols();
	}

	std::string choose;
	while (true)
	{
		system("cls");
		std::cout << "1 - Добавить нового пользователя\n";
		std::cout << "2 - Показать пользователей\n";
		std::cout << "3 - Изменить пароль пользователя\n";
		std::cout << "4 - Удалить пользователя\n";
		std::cout << "0 - Выход из редактора\n";
		std::cout << "Ввод - ";
		Getline(choose);
		if (choose == "1")
		{
			AddNewUsers();
		}
		else if (choose == "2" && userSize > 1)
		{
			ShowUsers();
		}
		else if (choose == "3" && userSize > 1)
		{

		}
		else if (choose == "4" && userSize > 1)
		{

		}
		else if (choose == "0")
		{
			system("cls");
			break;
		}
		else
		{
			if (userSize < 2)
			{
				std::cout << "Пользователи отсутствуют!\n";
			}
			Err();
		}
	}

}
void ShowUsers()
{
	system("cls");

	std::cout << "№\t" << std::left << std::setw(12) << "Логин\t\t " << "   Пароль\t\t\t" << "Роль\n";
	for (size_t i = 1; i < userSize; i++)
	{
		std::cout << i << "\t" << std::left << std::setw(9) << loginArr[i] << "\t\t" << passArr[i] << "\t\t\t"
			<< statusArr[i] << "\n";
	}
	system("pause");


}
void AddNewUsers()
{
	std::string newLogin, newPass, newRole, choose;
	bool exit = true;
	while (true)
	{
		while (true)
		{
			system("cls");
			std::cout << "Введите логин нового пользователяили exit для выхода";
			Getline(newLogin);
			if (newLogin == "exit")
			{
				std::cout << "Отмена добавление нового пользователя";
				exit = false;
				Sleep(1500);
				break;
			}
			if (CheckLogin(newLogin))
			{
				break;
			}
			else
			{
				std::cout << "Допустимые сиволы a-z, A-Z, 0-9\n\n";
				Sleep(1500);
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "Введите пароль нового пользователяили exit для выхода";
			Getline(newPass);
			if (newPass == "exit")
			{
				std::cout << "Отмена добавление нового пользователя";
				exit = false;
				Sleep(1500);
				break;
			}
			if (CheckLogin(newPass))
			{
				break;
			}
			else
			{
				std::cout << "Допустимые сиволы a-z, A-Z, 0-9 + спец символы\n\n";
				Sleep(1500);
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "Выберите роль нового пользователяили exit для выхода";
			std::cout << "1 - Админ\n 2 - Сотрудник\nВвод: ";
			Getline(choose);
			if (choose == "exit")
			{
				std::cout << "Отмена добавление нового пользователя";
				exit = false;
				Sleep(1500);
				break;
			}
			if (choose == "1")
			{
				newRole = userStatus[1];
				break;
			}
			else if (choose == "2")
			{
				newRole = userStatus[2];
				break;
			}
			else
			{
				Err();
			}
		}

		while (exit)
		{
			//===========================
		}
	}
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
	double price[staticSize]{ 40000, 45000, 35000, 250000,25000, 45000, 70000, 30000, 50000, 777777 };

	if (isStorageCreated)
	{
		delete[] idArr, nameArr, countArr, priceArr;
	}

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
			std::cout << idArr[i] << "\t" << std::left << std::setw(35) << nameArr[i] << "\t" << countArr[i] << "\t" << priceArr[i] << "\t\t\n";
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
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t" << priceArr[i] << "\t\t\n";
		}
	}
	else if (mode == 3)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i]  << "\t\t\n";
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
		
		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > 777)
			{
				std::cout << "Некорректный id или кол-во\nМаксимальное кол-во 777";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t" << countArr[id] << "--->" << countArr[id] + count << "\n\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					countArr[id] += count;
					std::cout << "Товар успешно пополнен\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена пополнения товара\n\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}
		
	}

}

void RemoveStorageItem()
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
			std::cout << "Отмена операции списания товара!\n";
			Sleep(1500);
			break;
		}
		std::cout << "Введите кол-во товара для списания: ";
		Getline(chooseCount);

		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > countArr[id])
			{
				std::cout << "Некорректный id или кол-во\nМаксимальное кол-во -" << countArr[id] << "\n\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t" << countArr[id] << "--->" << countArr[id] - count << "\n\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					countArr[id] -= count;
					std::cout << "Товар успешно списан\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена списание товара\n\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}

	}
}

void ChangePrice()
{
	std::string chooseId, choosePrice, choose;
	unsigned int id = 0;
	double newPrice = 0.0;

	while (true)
	{
		system("cls");
		ShowStorage(2);
		std::cout << "Введите ID товара или слово \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции изменения цуны!\n";
			Sleep(1500);
			break;
		}
		std::cout << "Введите новую цену товара:  ";
		Getline(choosePrice);

		if (IsNumber(chooseId) && IsNumber(choosePrice))
		{
			id = std::stoi(chooseId) - 1;
			newPrice = std::stod(choosePrice);

			if (id < 0 || id > storageSize - 1 || newPrice < 0 || newPrice > 7777777)
			{
				std::cout << "Некорректный id или цена\nМаксимальная цена 7777777";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t" << priceArr[id] << "--->" << newPrice << "\n\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					priceArr[id] = newPrice;
					std::cout << "Товар успешно пополнен\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена пополнения товара\n\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}

	}
}

void AddNewItem()
{
	std::string newName, newPrice, newCount, choose;
	double price = 0.0;
	unsigned int count = 0;
	bool exit;

	while (true)
	{
		exit = true;
		while (true)
		{
			system("cls");
			std::cout << "\tДобавление нового товара:\n\nВведите \"exit\" для прекращение операции \n\n ";
			std::cout << "Введите название нового товара: ";
			Getline(newName);
			if (newName == "exit")
			{
				std::cout << "Операция добавления товара прервана! \n";
				Sleep(1500);
				exit = false;
				break;
			}
			
			if (newName.size() <= 0 || newName.size() >= 60)
			{
				std::cout << "Ошибка имени. Максимальная длина 60 символов\n";
				
			}
			else
			{
				break;
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "\tДобавление нового товара:\n\nВведите \"exit\" для прекращение операции \n\n ";
			std::cout << "Введите кол-во товара: ";
			Getline(newCount);
			if (newCount == "exit")
			{
				std::cout << "Операция добавления товара прервана! \n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (IsNumber(newCount))
			{
				count = std::stoi(newCount);
				if (count > 777 || count < 0)
				{
					std::cout << "Ошибка максимального размера товара. Не более 777 ед.\n";
					Sleep(1500);

				}
				else
				{
					break;
				}
			}
		}
		
		while (exit)
		{
			system("cls");
			std::cout << "\tДобавление нового товара:\n\nВведите \"exit\" для прекращение операции \n\n ";
			std::cout << "Введите цену нового товара: ";
			Getline(newPrice);
			if (newPrice == "exit")
			{
				std::cout << "Операция добавления товара прервана! \n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (IsNumber(newPrice))
			{
				price = std::stod(newPrice);
				if (price > 7777777 || price < 0)
				{
					std::cout << "Ошибка максимальная цена товара. Не более 7777777 руб.\n";
					Sleep(1500);

				}
				else
				{
					break;
				}
			}
		}
		
		while (exit)
		{
			system("cls");
			std::cout << "Новый товар: " << newName << "\n";
			std::cout << "Кол-во товар: " << count << "\n";
			std::cout << "Цена товар: " << price << "\n";
			std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
			Getline(choose);
			if (choose == "1")
			{
				storageSize++;
				unsigned int* idArrTemp = new unsigned int[storageSize];
				std::string* nameArrTemp = new std::string[storageSize];
				unsigned int* countArrTemp = new unsigned int[storageSize];
				double* priceArrTemp = new double[storageSize];

				FillArray(idArrTemp, idArr, storageSize - 1);
				FillArray(nameArrTemp, nameArr, storageSize - 1);
				FillArray(countArrTemp, countArr, storageSize - 1);
				FillArray(priceArrTemp, priceArr, storageSize - 1);

				idArrTemp[storageSize-1] = storageSize;
				nameArrTemp[storageSize - 1]= newName;
				countArrTemp[storageSize - 1] = count;
				priceArrTemp[storageSize - 1] = price;

				std::swap(idArr, idArrTemp);
				std::swap(nameArr, nameArrTemp);
				std::swap(countArr, countArrTemp);
				std::swap(priceArr, priceArrTemp);

				delete[] idArrTemp, nameArrTemp, countArrTemp, priceArrTemp;
				std::cout << "Идет подготовка...";
				Sleep(2000);
				std::cout << "Товар успешно добавлен\n\n";
				Sleep(1500);
				break;
			}
			else if (choose == "2")
			{
				std::cout << "Отмена\n\n";
				Sleep(1500);
				break;
			}
			else
			{
				Err();
			}
			

		}

		if (exit == false)
		{
			break;
		}
	}
}

void ChangeStorage()
{
	std::string choose;
	while (true)
	{
		system("cls");
		std::cout << "1 - Добавить новый товар\n";
		std::cout << "2 - Изменить название товара\n";
		std::cout << "3 - Удалить товар\n";
		std::cout << "0 - Выход из редактора\n";
		std::cout << "Ввод: ";
		Getline(choose);

		if (choose == "1")
		{
			AddNewItem();
		}
		else if (choose == "2" && storageSize > 0)
		{
			ChangeName();
		}
		else if (choose == "3" && storageSize > 0)
		{
			DeleteItem();
		}
	
		else if (choose == "0")
		{
			system("cls");
			break;
		}
		else
		{
			if (storageSize < 1)
			{
				std::cout << "Склад пустой\n";
			}
			Err();
		}

	}
}

void ChangeName()
{
	std::string chooseId, newName, choose;
	unsigned int id = 0;

	while (true)
	{
		system("cls");
		ShowStorage(3);
		std::cout << "\nВведите ID товара или \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции изменения цены\n";
			Sleep(1500);
			break;
		}
		
		std::cout << "Введите новое название товара: ";
		Getline(newName);

		if (newName.size() <= 0 || newName.size() >= 60)
		{
			std::cout << "Ошибка имени. Максимальная длина 60 символов\n";
			Sleep(1500);

		}
		else if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Ошибка ID! \n";
				Sleep(1500);
			}
			else
			{
				std::cout << nameArr[id] << "-->" << newName << "\n\n";
				std::cout << "Подтвердить:\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					nameArr[id] = newName;
					std::cout << "Смена названия завершена\n";
					Sleep(1500);
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена операции\n";
				}
				else
				{
					Err();
				}
			}
		}

	}

}

void DeleteItem()
{
	std::string chooseId, choose;
	unsigned int id = 0;
	while (true)
	{
		system("cls");
		ShowStorage(3);
		std::cout << "\nВведите ID товара для удаления или \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции удаления товара\n";
			Sleep(1500);
			break;
		}
		if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Ошибка ID\n";
				Sleep(1500);
			}
			else
			{
				std::cout << "Товар на удаление: " << nameArr[id] << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					storageSize--;
					unsigned int* idArrTemp = new unsigned int[storageSize];
					std::string* nameArrTemp = new std::string[storageSize];
					unsigned int* countArrTemp = new unsigned int[storageSize];
					double* priceArrTemp = new double[storageSize];

					for (size_t i = 0, c = 0; i < storageSize; i++, c++)
					{
						if (id == c)
						{
							c++;
						}
						idArrTemp[i] = i + 1;
						nameArrTemp[i] = nameArr[c];
						countArrTemp[i] = countArr[c];
						priceArrTemp[i] = priceArr[c];
					}


					std::swap(idArr, idArrTemp);
					std::swap(nameArr, nameArrTemp);
					std::swap(countArr, countArrTemp);
					std::swap(priceArr, priceArrTemp);

					delete[] idArrTemp, nameArrTemp, countArrTemp, priceArrTemp;
					std::cout << "Идет подготовка...";
					Sleep(2000);
					std::cout << "Товар успешно удален\n\n";
					Sleep(1500);
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}

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
