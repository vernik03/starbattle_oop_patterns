#pragma once
#include <Windows.h>
#include <iostream>
#include <memory>
#include <set>

#include "HeadSprite.h"
#include "Framework.h"


class EventManager
{
public:
	EventManager() {};
	virtual ~EventManager() {};

	virtual void Subscribe(HeadSprite* listener) {
		listeners.insert(listener);
	}

	virtual void Unsubscribe(HeadSprite* listener) {
		listeners.erase(listener);
	}

	virtual void Notify(...) {}

protected:
	std::set<HeadSprite*> listeners;

};

class MouseClick : public EventManager
{
public:
	MouseClick(){};
	~MouseClick() {};
	
	void Notify(FRMouseButton button, bool isReleased) {
		for (auto listener : listeners) {
			listener->SendMouseClickEvent(button, isReleased);
		}
	}

private:
};


class MouseMove : public EventManager
{
public:
	MouseMove() {};
	~MouseMove() {};

	void Notify(int x, int y) {
		for (auto listener : listeners) {
			listener->SendMouseMoveEvent(x, y);
		}
	}

private:
};


class KeyPress : public EventManager
{
public:
	KeyPress() {};
	~KeyPress() {};

	void Notify(FRKey k)  {
		for (auto listener : listeners) {
			listener->SendKeyPressEvent(k);
		}
	}

private:
};



