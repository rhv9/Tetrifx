#pragma once

#include "InputCode.h"

template <class T> 
class EventHandler
{
	using Callback = void(*)(T&);
public:
	void Invoke(T& arg)
	{
		for (int i = 0; i < Callbacks.size(); i++)
		{
			Callbacks[i](arg);
		}
	}

	void RegisterCallback(Callback callbackFunction)
	{
		Callbacks.push_back(callbackFunction);
	}

	void operator += (Callback callbackFunction)
	{
		Callbacks.push_back(callbackFunction);
	}

private:
	std::vector<Callback> Callbacks;
};


struct EventArg
{
};

struct KeyPressedEventArg : public EventArg
{
	const int Key;
	const int Mods;

	KeyPressedEventArg(int key, int mods) : Key(key), Mods(mods) {}
};

struct KeyReleasedEventArg : public EventArg
{
	const int Key;
	const int Mods;

	KeyReleasedEventArg(int key, int mods) : Key(key), Mods(mods) {}
};

struct MousePressEventArg : public EventArg
{

};

struct MouseReleaseEventArg : public EventArg
{

};

struct MouseMoveEventArg : public EventArg
{

};
