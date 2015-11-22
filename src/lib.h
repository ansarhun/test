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
	void storeComponents(const QList<Component> &components);
};

class Store
{
public:
	Store();

	void printItems();
	void storeItemsInDataBase();
	Component getComponent(int index);

protected:
	QList<Component> items;
	DataBase dataBase;
};
