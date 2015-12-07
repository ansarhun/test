#pragma once

#include <QString>
#include <QList>

struct Component
{
	QString name;
	int price = 0;

	Component(const QString &name, int price) : name(name), price(price)
	{ }

	Component()
	{ }
};

class DataBase
{
public:
	virtual void storeComponents(const QList<Component> &components);
};

class Store
{
public:
	Store(DataBase *dataBase = new DataBase());

	void printItems();
	void storeItemsInDataBase();
	Component getComponent(int index);

protected:
	void addComponent(const Component &component);

protected:
	QList<Component> items;
	DataBase *dataBase;
};
