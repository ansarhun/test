#include <gtest/gtest.h>

#include <lib.h>

class UnitStore : public Store
{
public:
	UnitStore()
			: Store()
	{}

	UnitStore(DataBase *db)
			: Store(db)
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

class MockDataBase : public DataBase
{

public:
	virtual void storeComponents(const QList<Component> &components) override
	{
		this->components = components;
	}

	QList<Component> components;
};

bool operator ==(const Component &a, const Component &b)
{
	return a.name == b.name && a.price == b.price;
}

void PrintTo(const Component& comp, ::std::ostream* os) {
	*os << "Component(" << comp.name.toStdString() << ", " << comp.price << ")";
}

TEST(Lib, Test) {
	ASSERT_TRUE(true);
}

TEST(TestStore, ItemsCreated) {
	UnitStore store;
	ASSERT_EQ(3, store._getComponents().size());
}

TEST(TestStore, Items) {
	UnitStore store;

	ASSERT_EQ(Component("A", 49), store._getComponents().first());
	ASSERT_EQ(Component("B", 22), store._getComponents().at(1));
	ASSERT_EQ(Component("C", 73), store._getComponents().last());
}

TEST(TestStore, AddItem) {
	UnitStore store;

	store._addComponent(Component("D", 220));
	ASSERT_EQ(4, store._getComponents().size());

	ASSERT_EQ(Component("D", 220), store._getComponents().last());
}

TEST(TestStore, GetComponent) {
	Store store;

	ASSERT_EQ(Component("A", 49), store.getComponent(0));
	ASSERT_EQ(Component(), store.getComponent(200));
}

TEST(TestStore, SaveItemsToDb) {
	MockDataBase db;
	UnitStore store(&db);


	store.storeItemsInDataBase();
	ASSERT_EQ(3, db.components.size());

	ASSERT_EQ(Component("A", 49), db.components.first());
	ASSERT_EQ(Component("B", 22), db.components.at(1));
	ASSERT_EQ(Component("C", 73), db.components.last());
}
