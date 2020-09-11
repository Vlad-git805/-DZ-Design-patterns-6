#include<iostream>
#include<list>
#include<ctime>
#include<windows.h>

using namespace std;

class Cryptocurrency
{
protected:
	string name;
	int pric;
	bool trend;

public:

	void Raising_prices(int price)
	{
		pric += price;
	}

	void Price_reduction(int price)
	{
		pric -= price;
	}
	bool Get_Trend()
	{
		return trend;
	}
	void Set_Trend(bool trend)
	{
		this->trend = trend;
	}
	int Get_Prise()
	{
		return pric;
	}

};

class Bitcoin : public Cryptocurrency
{
public:
	Bitcoin()
	{
		this->name = "Bitcoin";
		this->pric = 10000;
	}
};
class Ethereum : public Cryptocurrency
{
public:
	Ethereum()
	{
		this->name = "Ethereum";
		this->pric = 5000;
	}
};
class XRP : public Cryptocurrency
{
public:
	XRP()
	{
		this->name = "XRP";
		this->pric = 3000;
	}
};
class Bitcoin_Cash : public Cryptocurrency
{
public:
	Bitcoin_Cash()
	{
		this->name = "Bitcoin Cash";
		this->pric = 2000;
	}
};
class Litecoin : public Cryptocurrency
{
public:
	Litecoin()
	{
		this->name = "Litecoin";
		this->pric = 1000;
	}
};

class Exchange;

class Buyer
{
public:

	virtual void Update(Exchange*) = 0;
};


class Exchange
{
private:

	Bitcoin bitcoin;
	Ethereum ethereum;
	XRP  xrp;
	Bitcoin_Cash bitcoin_Cash;
	Litecoin litecoin;
	list<Buyer*> buyers;

public:


	void Attach(Buyer* pBuyer)
	{
		buyers.push_back(pBuyer);
	}
	void Detach(Buyer* pBuyer)
	{
		for (auto it = buyers.begin(); it != buyers.end(); it++)
		{
			if (*it == pBuyer)
			{
				buyers.erase(it);
				return;
			}
		}
	}
	void Notify()
	{
		for (auto it = buyers.begin(); it != buyers.end(); it++)
		{
			(*it)->Update(this);
		}
		cout << "\n";
	}

	void SetPrice()
	{
		int rnd;

		rnd = rand() % 2;

		if (rnd == 1)
		{
			bitcoin.Price_reduction(10);
			bitcoin.Set_Trend(false);
			ethereum.Price_reduction(10);
			ethereum.Set_Trend(false);
			xrp.Price_reduction(10);
			xrp.Set_Trend(false);
			bitcoin_Cash.Price_reduction(10);
			bitcoin_Cash.Set_Trend(false);
			litecoin.Price_reduction(10);
			litecoin.Set_Trend(false);
		}
		else
		{
			bitcoin.Raising_prices(10);
			bitcoin.Set_Trend(true);
			ethereum.Raising_prices(10);
			ethereum.Set_Trend(true);
			xrp.Raising_prices(10);
			xrp.Set_Trend(true);
			bitcoin_Cash.Raising_prices(10);
			bitcoin_Cash.Set_Trend(true);
			litecoin.Raising_prices(10);
			litecoin.Set_Trend(true);
		}
		Notify();
	}
	bool Get_status_bitcoin()
	{
		return bitcoin.Get_Trend();
	}
	bool Get_status_Ethereum()
	{
		return ethereum.Get_Trend();
	}
	bool Get_status_XRP()
	{
		return xrp.Get_Trend();
	}
	bool Get_status_bitcoin_Cash()
	{
		return bitcoin_Cash.Get_Trend();
	}
	bool Get_status_litecoin()
	{
		return litecoin.Get_Trend();
	}

	int Get_prise_bitcoin()
	{
		return bitcoin.Get_Prise();
	}

	int Get_prise_Ethereum()
	{
		return ethereum.Get_Prise();
	}
	int Get_prise_XRP()
	{
		return xrp.Get_Prise();
	}
	int Get_prise_bitcoin_Cash()
	{
		return bitcoin_Cash.Get_Prise();
	}
	int Get_prise_litecoin()
	{
		return litecoin.Get_Prise();
	}

};




class UkrainianBuyer : public Buyer
{
private:
	Exchange* ptr;
	string name;
	int money = 100000;
public:
	UkrainianBuyer(string pName)
	{
		name = pName;
	}

	void Update(Exchange* pProduct)
	{
		if (pProduct->Get_status_bitcoin())
		{
			money -= pProduct->Get_prise_bitcoin();
		}
		else
		{
			money += pProduct->Get_prise_bitcoin();
		}

		if (pProduct->Get_status_bitcoin_Cash())
		{
			money -= pProduct->Get_prise_bitcoin_Cash();
		}
		else
		{
			money += pProduct->Get_prise_bitcoin_Cash();
		}

		if (pProduct->Get_status_Ethereum())
		{
			money -= pProduct->Get_prise_Ethereum();
		}
		else
		{
			money += pProduct->Get_prise_Ethereum();
		}

		if (pProduct->Get_status_litecoin())
		{
			money -= pProduct->Get_prise_litecoin();
		}
		else
		{
			money += pProduct->Get_prise_litecoin();
		}

		if (pProduct->Get_status_XRP())
		{
			money -= pProduct->Get_prise_XRP();
		}
		else
		{
			money += pProduct->Get_prise_XRP();
		}
	}

	void Show_money()
	{
		cout << "money:" << money << endl;
	}
};

int main()
{
	srand(time(NULL));

	Exchange exchange;
	UkrainianBuyer* Buyer1 = new UkrainianBuyer("Vasa");
	UkrainianBuyer* Buyer2 = new UkrainianBuyer("Xtosi");
	exchange.Attach(Buyer1);
	exchange.Attach(Buyer2);

	while (true)
	{
		exchange.SetPrice();
		Buyer2->Show_money();
		Sleep(1000);
		system("cls");
	}

	system("pause");
	return 0;
}