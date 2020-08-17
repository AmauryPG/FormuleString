#include <iostream>
#include <string>

using namespace std;

class Operation
{
	class State *current;
public:
	Operation();
	void setCurrent(State *s)
	{
		current = s;
	}

	void addition(string valeur1, string valeur2);
	void on();
	void off();
};

class State
{
public:
	virtual void on(Operation *m)
	{
		cout << "   already ON\n";
	}
	virtual void off(Operation *m)
	{
		cout << "   already OFF\n";
	}
};

void Operation::addition()
{

}

void Operation::on()
{
	current->on(this);
}

void Operation::off()
{
	current->off(this);
}

class ON : public State
{
public:
	ON()
	{
		cout << "   ON-ctor ";
	};
	~ON()
	{
		cout << "   dtor-ON\n";
	};
	void off(Operation *m);
};

class OFF : public State
{
public:
	OFF()
	{
		cout << "   OFF-ctor ";
	};
	~OFF()
	{
		cout << "   dtor-OFF\n";
	};
	void on(Operation *m)
	{
		cout << "   going from OFF to ON";
		m->setCurrent(new ON());
		delete this;
	}
};

void ON::off(Operation *m)
{
	cout << "   going from ON to OFF";
	m->setCurrent(new OFF());
	delete this;
}

Operation::Operation()
{
	current = new OFF();
	cout << '\n';
}