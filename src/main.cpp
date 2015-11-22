#include "lib.h"

#include <QDebug>

int main(int argc, char *argv[]) {
	Store store;

	qDebug() << "---------------------";

	store.printItems();

	qDebug() << "---------------------";

	store.storeItemsInDataBase();

	qDebug() << "---------------------";

	Component c = store.getComponent(0);
	qDebug() << "1. component" << c.name;

	return 0;
}
