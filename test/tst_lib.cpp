#include <gtest/gtest.h>

#include <lib.h>

class MockDataBase : public DataBase
{
public:
	virtual void storeComponents(const QList<Component> &components) override
	{
		storedComponents = components;
	}

	QList<Component> storedComponents;
};

class TestStore : public Store
{
public:
	TestStore()
			: Store()
	{}

	TestStore(DataBase *dataBase)
			: Store(dataBase)
	{}

	QList<Component> _getComponents()
	{
		return items;
	}

	void _addComponent(const Component &c)
	{
		addComponent(c);
	}
};

bool operator ==(const Component &a, const Component &b)
{
	return a.name == b.name && a.price == b.price;
}

void PrintTo(const Component& component, ::std::ostream* os) {
	*os << "Component(name: " << component.name.toStdString() << ", price: " << component.price << ")";
}

TEST(Lib, TestItems) {
	TestStore store;
	ASSERT_EQ(3, store._getComponents().size());

	ASSERT_EQ(Component("A", 49), store._getComponents().value(0));
	ASSERT_EQ(Component("B", 22), store._getComponents().value(1));
	ASSERT_EQ(Component("C", 73), store._getComponents().value(2));
}

TEST(Lib, TestAddItems)
{
	TestStore store;
	int size = store._getComponents().size();

	store._addComponent(Component("NEW", 10));

	ASSERT_EQ(size + 1, store._getComponents().size());
	ASSERT_EQ(Component("NEW", 10), store._getComponents().last());
}

TEST(Lib, TestGetComponent)
{
	TestStore store;

	ASSERT_EQ(Component("A", 49), store.getComponent(0));
	ASSERT_EQ(Component(), store.getComponent(1000));
}

TEST(Lib, TestDataBase)
{
	MockDataBase db;
	TestStore store(&db);
//	TestStore store;

	store.storeItemsInDataBase();

	ASSERT_EQ(3, db.storedComponents.size());
}
