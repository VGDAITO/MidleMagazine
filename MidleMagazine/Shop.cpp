#include <iostream>
#include <windows.h>
#include <limits>
#include <string>
#include <iomanip>
#include <unordered_set>

// --------------------Учетки---------------------------------
size_t userSize = 3;
size_t staffCount = 1; 
std::string userStatus[3]{ "Крутой мопс", " мопс", "Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin", "admin123", "user" };
std::string* passArr = new std::string[userSize]{ "1234","123" , "12345"};
std::string* statusArr = new std::string[userSize]{ userStatus[0],userStatus[1],userStatus[2]};
double* bonusArr = new double[userSize] {0.0, 0.0, 0.0};
unsigned int* userIdArr = new unsigned int[userSize] {1, 2, 3};
unsigned int currentId = 0;
std::string currentStatus;


void ChangeUsers();
void ShowUsers(int mode = 0);
void AddNewUsers();

void ChangePass();

void DeleteUser();

//-----------------------------------------------------------


// ------------------------Склад-----------------------------
size_t storageSize = 0;
unsigned int* idArr = nullptr;
std::string* nameArr = nullptr;
unsigned int* countArr = nullptr;
double* priceArr = nullptr;
bool isStorageCreated = false;

void CreateStorage();
void ZeroCreateStorage();
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

//-----------------------------------------------------------------


//-----------------------------Продажи-----------------------------



size_t checkSize = 0;
int* idArrCheck;
std::string* nameArrCheck;
unsigned int* countArrCheck;
double* priceArrCheck;
double* totalPriceArrCheck;
double cashIncome = 0.0;
double bankIncome = 0.0;
double cash = 300000 + rand() % 75000;

void Selling();
void CheckArrAppend();
void PrintCheck(double& totalSum);
void StorageReturner();

double DiscountFromAmount(double& totalSum);
double Promo(double& totalSum, std::string& promo, int &attempts);


// ---------------------------Служебные----------------------------
std::unordered_set<char> passSymbols;
std::unordered_set<char> loginSymbols;
bool isLoginSetCreated = false;
bool isPassSetCreated = false;

void Start();
bool Login();
bool Logout();
void SetLoginSymbols();
void SetPassSymbols();
bool CheckLogin(const std::string &str);
bool CheckPass(const std::string& str);
void ShowSuperAdminMenu();
bool IsNumber(const std::string& str);
inline void Getline(std::string& str);
inline void Err(int time = 1500);
void ShowIncome();


//------------------------------------------------------------
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	Start();
	delete[]loginArr;
	delete[] passArr;
	delete[] statusArr;
	delete[] bonusArr;
	delete[] userIdArr;
	if (isStorageCreated)
	{
		delete[]idArr;
		delete[] nameArr;
		delete[] countArr;
		delete[] priceArr;
	}

	return 0;
}

void Selling()
{
	std::string chooseId, chooseCount, chooseMoney, choose;
	unsigned int id = 0, count = 0;
	int index = -1;
	double money = 0.0, totalSum = 0.0;
	bool isFirst = false;
	int attempts = 0;

	while (true)
	{
		ShowStorage();
		std::cout << "\n Введите ID товара для покупки или \"exit\" завершение выбора товаров: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			if (isFirst == false)
			{
				std::cout << "Выход без покупок\n";
				Sleep(1500);
				break;
			}
			
			double beforeAmount = totalSum;
			totalSum = DiscountFromAmount(totalSum);
			std::cout << "\nСумма до скидки: " << beforeAmount << "\nСумма после скидок: " << totalSum << "\n";
			Sleep(1500);

			PrintCheck(totalSum);

			
			
			std::cout << "\nПодтвердить покупку?\n1 - Да\n2 - Добавить еще товар\n3 - Отмена\n4 - Ввести промокод\nВвод: ";
			Getline(choose);
			if (choose == "1")
			{
				while (true)
				{
					system("cls");
					std::cout << "Выберите способ оплаты\n1 - Наличными\n2 - Безнал\nВвод: ";
					Getline(choose);
					if (choose == "1")
					{
						std::cout << "К оплате: " << totalSum << "\n\n";
						std::cout << "Введите кол-во наличных: ";
						Getline(chooseMoney);
						if (IsNumber(chooseMoney))
						{
							money = std::stod(chooseMoney);
							if (money < totalSum)
							{
								std::cout << "Недостаточно средств!\n";
								Sleep(1500);
								continue;
							}
							else if (money - totalSum > cash)
							{
								std::cout << "Нет возможности дать сдачи\n";
								Sleep(1500);
								continue;
							}
							else
							{
								std::cout << "Ваши: " << money << "\n\n";
								Sleep(400);
								std::cout << "Оплата прошла успешно. Сдача: " << money - totalSum << " рублей\n";
								Sleep(2000);
								cash += totalSum;
								cashIncome += totalSum;
								bonusArr[currentId] += totalSum;

								system("cls");
								break;
							}
						}


					}

					else if ( choose == "2")
					{
						std::cout << "Приложите карту \n\n";
						Sleep(1500);
						if (rand() % 10 <= 2)
						{
							for (size_t i = 0; i < 5; i++)
							{
								std::cout << i + 1 << "\t";
								Beep(500, 400);
								Sleep(1000);
							}
							std::cout << "\nСоединение не установлено. Повторите попытку\n\n";
							Sleep(1000);
						}
						else
						{
							for (size_t i = 0; i < 5; i++)
							{
								std::cout << i + 1 << "\t";
								Beep(500, 400);
								Sleep(1000);
							}
							std::cout << "\nОплата прошла успешно. Спасибо за покупку!\n";
							Sleep(2000);
							bankIncome += totalSum;
							bonusArr[currentId] += totalSum;
							system("cls");
							break;
						}
					}
					else if (choose == "Мопсик" || choose == "мопсик")
					{
						std::cout << "Мопсик оплатил вам счет\n\n";
						Sleep(1500);
						system("cls");
						break;

					}
					else
					{
						Err();
					}
				}
				delete[]idArrCheck;
				delete[]nameArrCheck;
				delete[]countArrCheck;
				delete[]priceArrCheck;
				delete[]totalPriceArrCheck;

				idArrCheck = nullptr;
				nameArrCheck = nullptr;
				countArrCheck = nullptr;
				priceArrCheck = nullptr;
				totalPriceArrCheck = nullptr;

				checkSize = 0;
			}
			else if (choose == "2")
			{
				continue;
			}
			else if (choose == "3")
			{
				std::cout << "Отмена покупки!\n";
				StorageReturner();
				Sleep(1500);
				system("cls");
				return;
			}
			else if (choose == "4" && attempts < 1)
			{
				
				std::string promo;
				std::cout << "\nВведите промокод: ";
				Getline(promo);
				
				double beforePromo = totalSum;
				totalSum = Promo(totalSum, promo,attempts);
				std::cout << "\nСумма до скидки: " << beforePromo << "\nСумма после скидок: " << totalSum << "\n";
				Sleep(1500);
				continue;

			}
			
			else
			{
				Err();
				continue;
			}

			
		}

		if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Ошибка ID\n";
				Sleep(1500);
				continue;
			}
		}
		else
		{
			continue;
		}

		std::cout << "\nВведите кол-во товара или \"exit\" для выбора другого товара: ";
		Getline(chooseCount);
		if (chooseCount == "exit")
		{
			std::cout << "Отмена покупки товара: " << nameArr[id] << "\n";
			Sleep(1500);
			continue;
		}
		if (IsNumber(chooseCount))
		{
			count = std::stoi(chooseCount);
			if (count < 1 || count > countArr[id])
			{
				std::cout << "Ошибка кол-ва! Максимум: " << countArr[id] << "\n\n\n";
				Sleep(1500);
				continue;
			}
		}
		else
		{
			continue;
		}

		CheckArrAppend();
		if (isFirst == false)
		{
			isFirst = true;
		}
		index++;
		idArrCheck[index] = idArr[id];
		nameArrCheck[index] = nameArr[id];
		priceArrCheck[index] = priceArr[id];
		countArrCheck[index] = count;
		totalPriceArrCheck[index] = count * priceArr[id];
		countArr[id] -= count;
		totalSum += totalPriceArrCheck[index];

		std::cout << "\nТовар добавлен в чек\n\n";
		Sleep(1000);

	}


}

void CheckArrAppend()
{
	checkSize++;
	int* idArrCheckTemp = new int[checkSize];
	std::string* nameArrCheckTemp = new std::string[checkSize];
	unsigned int *countArrCheckTemp = new unsigned int[checkSize];
	double* priceArrCheckTemp = new double[checkSize];
	double* totalPriceArrCheckTemp = new double[checkSize];

	FillArray(idArrCheckTemp, idArrCheck, checkSize - 1);
	FillArray(nameArrCheckTemp, nameArrCheck, checkSize - 1);
	FillArray(countArrCheckTemp, countArrCheck, checkSize - 1);
	FillArray(priceArrCheckTemp, priceArrCheck, checkSize - 1);
	FillArray(totalPriceArrCheckTemp, totalPriceArrCheck, checkSize - 1);

	std::swap(idArrCheckTemp, idArrCheck);
	std::swap(nameArrCheckTemp, nameArrCheck);
	std::swap(countArrCheckTemp, countArrCheck);
	std::swap(priceArrCheckTemp, priceArrCheck);
	std::swap(totalPriceArrCheckTemp, totalPriceArrCheck);

	delete[]idArrCheckTemp; 
	delete[]nameArrCheckTemp; 
	delete[]countArrCheckTemp;
	delete[]priceArrCheckTemp;
	delete[]totalPriceArrCheckTemp;

}

void PrintCheck(double& totalSum)
{
	std::cout <<"№\t" << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Цена за ед\t" << "Кол-во\t" << "Итого\n";

	for (size_t i = 0; i < checkSize; i++)
	{
		std::cout << i + 1<<  "\t" << idArrCheck[i] << "\t" << std::left << std::setw(35) << nameArrCheck[i] << "\t" << priceArrCheck[i]<< "\t\t" << countArrCheck[i] << "\t" << totalPriceArrCheck[i] << "\t\t\n";
	}
	std::cout << "Итого к оплате: " << totalSum << "\n\n";
}

void StorageReturner()
{
	for (size_t i = 0; i < checkSize; i++)
	{
		countArr[idArrCheck[i] - 1] += countArrCheck[i];
	}
	delete[]idArrCheck;
	delete[]nameArrCheck;
	delete[]countArrCheck;
	delete[]priceArrCheck;
	delete[]totalPriceArrCheck;

	idArrCheck = nullptr;
	nameArrCheck = nullptr;
	countArrCheck = nullptr;
	priceArrCheck = nullptr;
	totalPriceArrCheck = nullptr;

	checkSize = 0;
}

double DiscountFromAmount(double& totalSum)
{
	if (totalSum >= 700000)
	{
		return totalSum * 0.70;
	}
	if (totalSum >= 350000)
	{
		return totalSum * 0.80;
	}
	if (totalSum >= 200000)
	{
		return totalSum * 0.90;
	}
	if (totalSum >= 70000)
	{
		return totalSum * 0.95;
	}
	return totalSum;
}

double Promo(double& totalSum, std::string& promo, int &attempts)
{
	

	if (promo == "14")
	{
		attempts++;
		return totalSum * 0.80;
	}
	if (promo == "ЧИУЛАВА")
	{
		attempts++;
		return totalSum * 0.85;
	}
	if (promo == "ИМБА")
	{
		attempts++;
		return totalSum * 0.90;
	}
	
	return totalSum;

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
						ZeroCreateStorage();
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
				currentId = userIdArr[i];
				return true;
			}
		}
		Err();
	}
}
bool Logout()
{
	std::string choose;
	system("cls");

	while (true)
	{
		std::cout << "Для подтверждения выхода из пользователя введите свой пароль или \"exit\" для возврата в меню: ";
		Getline(choose);
		if (choose == "exit")
		{
			system("cls");
			return false;
		}
		else if (choose == passArr[currentId - 1] || choose == passArr[0])
		{
			system("cls");
			return true;
		}
		else
		{
			Err();
		}
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
bool CheckLogin(const std::string& str)
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
			std::cout << "Некоретный логин\n";
			Sleep(1500);
			return false;
		}
	}

	for (size_t i = 0; i < userSize; i++)
	{
		if (str == nameArr[i])
		{
			std::cout << "Такой пользователь уже существует!\n";
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

	int numCount = 0;
	int symCount = 0;
	std::unordered_set<char> specialSymbols{ '!','@','#','$','%','^','&','*','(',')','-','_','+','=','/','?','|','\\','\"',
	'\'',',','.','<','>','~','`',';',':','{','}','[',']' };

	for (char sym : str)
	{
		if (!passSymbols.count(sym))
		{
			std::cout << "Некоретный пароль\n";
			Sleep(1500);
			return false;
		}
		if (std::isdigit(sym))
		{
			numCount++;
		}
		if (specialSymbols.count(sym))
		{
			symCount++;
		}

		
	}
	if (numCount > 2 && symCount > 2)
	{
		return true;
	}
	else
	{
		std::cout << "Минимум 3 символа и 3 цифры\n";
		return false;
	}
	return true;



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
			Selling();
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
			ShowIncome;
		}
		else if (choose == "0")
		{
			if (Logout())
			{
				break;
			}
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

void ShowIncome()
{
	system("cls");
	std::cout << "Текущая прибыль за смену\n\n";
	std::cout << "Наилчный расчет: " << cashIncome << "\n\n";
	std::cout << "Безналичный расчет: " << bankIncome << "\n\n";
	std::cout << "Итого: " << bankIncome + cashIncome << "\n\n";
	std::cout << "Сумма ваших продаж: " << bonusArr[currentId] << "\n\n";
	
	system("pause");
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
		system("cls");
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
			ChangePass();
		}
		else if (choose == "4" && userSize > 1)
		{
			DeleteUser();
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
void ShowUsers(int mode)
{
	if (mode == 0)
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
	else if (mode == 1)
	{
		std::cout << "№\t" << std::left << std::setw(12) << "Логин\t\t " << "   Пароль\t\t\t" << "Роль\n";
		for (size_t i = 0; i < userSize; i++)
		{
			std::cout << i << "\t" << std::left << std::setw(9) << loginArr[i] << "\t\t" << passArr[i] << "\t\t\t"
				<< statusArr[i] << "\n";
		}
	}


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
			std::cout << "Введите логин нового пользователяили exit для выхода: ";
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
				std::cout << "\nДопустимые сиволы a-z, A-Z, 0-9\n\n";
				Sleep(1500);
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "Введите пароль нового пользователяили exit для выхода: ";
			Getline(newPass);
			if (newPass == "exit")
			{
				std::cout << "Отмена добавление нового пользователя";
				exit = false;
				Sleep(1500);
				break;
			}
			if (CheckPass(newPass))
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
			std::cout << "Выберите роль нового пользователяили exit для выхода: ";
			std::cout << "\n1 - Админ\n2 - Сотрудник\nВвод: ";
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
			system("cls");
			std::cout << "Пользователь: " << newLogin << "\n";
			std::cout << "Пароль: " << newPass << "\n";
			std::cout << "Роль: " << newRole << "\n";
			std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
			Getline(choose);
			if (choose == "1")
			{

				userSize++;

				if (newRole == userStatus[2])
				{
					staffCount++;
				}

				std::string* loginArrTemp = new std::string[userSize];
				std::string* passArrTemp = new std::string[userSize];
				std::string* statusArrTemp = new std::string[userSize];
				double* bonusArrTemp = new double[userSize];
				unsigned int *userIdArrTemp = new unsigned int[userSize];

				FillArray(loginArrTemp, loginArr, userSize - 1);
				FillArray(passArrTemp, passArr, userSize - 1);
				FillArray(statusArrTemp, statusArr, userSize - 1);
				FillArray(bonusArrTemp, bonusArr, userSize - 1);
				FillArray(userIdArrTemp, userIdArr, userSize - 1);

				loginArrTemp[userSize - 1] = newLogin;
				passArrTemp[userSize - 1] = newPass;
				statusArrTemp[userSize - 1] = newRole;
				bonusArrTemp[userSize - 1] = 0.0;
				userIdArrTemp[userSize - 1] = userSize;

				std::swap(loginArr, loginArrTemp);
				std::swap(passArr, passArrTemp);
				std::swap(statusArr, statusArrTemp);
				std::swap(bonusArr, bonusArrTemp);
				std::swap(userIdArr, userIdArrTemp);

				delete[]loginArrTemp;
				delete[] passArrTemp;
				delete[] statusArrTemp;
				delete[] userIdArrTemp;
				delete[] bonusArrTemp;

				std::cout << "Идет подготовка...\n";
				Sleep(2000);
				std::cout << "Пользователь успешно добавлен\n\n";
				Sleep(1500);
				exit = false;
				break;

			}
			else if (choose == "2")
			{
				std::cout << "Отмена\n";
				Sleep(1500);
			}
			else
			{
				
			}
		}
		if (exit == false)
		{
			break;
		}
	}
}

void ChangePass()
{
	std::string newPass1, newPass2, choose;
	int userId = 0, isAdmin = 0;

	while (true)
	{
		if (currentStatus == userStatus[0])
		{
			ShowUsers(1);
			isAdmin = 0;
		}
		else
		{
			ShowUsers();
			isAdmin = 1;
		}

		std::cout << "\nВыберите номер пользователя для смены пароля\"exit\" для выхода ";
		Getline(choose);
		if (choose == "exit")
		{
			std::cout << "Отмена изменения пароля!\n";
			Sleep(1500);
			break;
		}
		else if (IsNumber(choose))
		{
			userId = std::stoi(choose);
			if (userId < isAdmin || userId > userSize - 1)
			{
				std::cout << "Пользователя с таким номером не существует!\n";
				Sleep(1500);
				continue;
			}
		}
		else
		{
			Err();
			continue;
		}
		while (true)
		{
			system("cls");

			if (currentStatus == userStatus[1] && statusArr[userId] == userStatus[1])
			{
				std::cout << "Нельзя менять пароль администратору!\n";
				Sleep(1500);
				break;
			}
			std::cout << "Введите новый пароль для пользователя " << loginArr[userId] << ":  ";
			Getline(newPass1);
			std::cout << "Подтвердите пароль для пользователя " << loginArr[userId] << ":  ";
			Getline(newPass2);
			
			if (CheckPass(newPass1) && CheckPass(newPass2))
			{
				if (newPass1 == newPass2 && newPass1 != passArr[userId] && newPass2 != passArr[userId])
				{
					passArr[userId] = newPass1;
					std::cout << "Успешно\n";
					Sleep(1500);
					break;
				}
				else
				{
					std::cout << "Повторите попытку\nПароли не одинаковы или совпадают с действующим паролем\n";
					Sleep(1200);
				}
			}
			
		}
	}

}

void DeleteUser()
{
	std::string chooseId, checkPass, choose;
	int userId, isAdmin = 1;

	while (true)
	{
		if (currentStatus == userStatus[0] && userSize < 2)
		{
			std::cout << "Нет доступных пользователей для удаления\n";
			Sleep(1500);
			return;
		}
		else if (currentStatus == userStatus[1] && staffCount < 1)
		{
			std::cout << "Нет доступных пользователей для удаления\n";
			Sleep(1500);
			return;
		}

		ShowUsers();
		std::cout << "\nВыберите номер пользователя для удаления или \"exit\" для выхода: ";
		Getline(choose);
		if (choose == "exit")
		{
			std::cout << "Отмена удаление пользователя!\n";
			Sleep(1500);
			break;
		}

		else if (IsNumber(choose))
		{
			userId = std::stoi(choose);
			if (userId < isAdmin || userId > userSize - 1)
			{
				std::cout << "Пользователь с таким номером не существует!\n";
				Sleep(1500);
				break;
			}
			while (true)
			{
				system("cls");
				if (currentStatus == userStatus[1] && statusArr[userId] == userStatus[1])
				{
					std::cout << "Нельзя удалять администратора!\n";
					Sleep(1500);
					break;
				}

				std::cout << "Удаление пользователя: " << loginArr[userId] << "\n\n";
				std::cout << "Для подтверждения введите пароль супер администратора или \"exit\": ";
				Getline(checkPass);
				if (checkPass == "exit")
				{
					std::cout << "Отмена удаления пользователя: " << loginArr[userId] << "\n\n";
					Sleep(1500);
					break;
				}
				
				else if (checkPass == passArr[0])
				{
					if (statusArr[userId] == userStatus[2])
					{
						staffCount--;
					}
					userSize--;

					std::string* loginArrTemp = new std::string[userSize];
					std::string* passArrTemp = new std::string[userSize];
					std::string* statusArrTemp = new std::string[userSize];
					double* bonusArrTemp = new double[userSize];
					unsigned int* userIdArrTemp = new unsigned int[userSize];

					for (size_t i = 0, c = 0; i < userSize; i++, c++)
					{
						if (userId == c)
						{
							c++;
						}
						loginArrTemp[i] = loginArr[c];
						passArrTemp[i] = passArr[c];
						statusArrTemp[i] = statusArr[c];
						bonusArrTemp[i] = bonusArr[c];
						userIdArrTemp[i] = i + 1;
					}


					std::swap(loginArr, loginArrTemp);
					std::swap(passArr, passArrTemp);
					std::swap(statusArr, statusArrTemp);
					std::swap(bonusArr, bonusArrTemp);
					std::swap(userIdArr, userIdArrTemp);

					delete[]loginArrTemp;
					delete[]passArrTemp;
					delete[]statusArrTemp;
					delete[]userIdArrTemp;
					delete[]bonusArrTemp;

					std::cout << "Идет подготовка...\n";
					Sleep(2000);
					std::cout << "Пользователь успешно добавлен\n\n";
					Sleep(1500);

					break;


				}
				else
				{
					Err();
				}
			}
		}
		else
		{
			Err();
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
		delete[] idArr;
		delete[]nameArr;
		delete[]countArr;
		delete[]priceArr;
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

void ZeroCreateStorage()
{
	std::string choose;

	if (isStorageCreated)
	{
		delete[] idArr;
		delete[] nameArr;
		delete[] countArr;
		delete[] priceArr;
		isStorageCreated = false;
	}

	idArr = new unsigned int[storageSize];
	nameArr = new std::string[storageSize];
	countArr = new unsigned int[storageSize];
	priceArr = new double[storageSize];

	for (int i = 0; i < storageSize; i++)
	{
		idArr[i] = 0;
		nameArr[i] = "";
		countArr[i] = 0;
		priceArr[i] = 0.0;
	}

	while (true)
	{
		AddNewItem();
		break;
	}

	isStorageCreated = true;
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

				delete[] idArrTemp;
				delete[] nameArrTemp;
				delete[] countArrTemp;
				delete[] priceArrTemp;
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

					delete[] idArrTemp;
					delete[] nameArrTemp;
					delete[] countArrTemp;
					delete[] priceArrTemp;
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
