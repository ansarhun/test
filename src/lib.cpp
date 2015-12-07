#include "lib.h"

#include <QDebug>

void DataBase::storeComponents(const QList<Component> &components)
{
	qDebug() << "Write items to database";
	for (const Component &component : components) {
		qDebug() << "Item saved:" << component.name;
	}
}

Store::Store(DataBase *dataBase)
	: dataBase(dataBase)
{
	addComponent(Component("A", 49));
	addComponent(Component("B", 22));
	addComponent(Component("C", 73));
}

void Store::printItems()
{
	qDebug() << "Available products:";
	for (const Component &component : items) {
		qDebug().nospace() << "Name: " << component.name << ", price: " << component.price;
	}
}

void Store::storeItemsInDataBase()
{
	dataBase->storeComponents(items);
}

Component Store::getComponent(int index)
{
	return items.value(index, Component());
}

void Store::addComponent(const Component &component)
{
	qDebug() << "Item added" << component.name;
	items << component;
}
