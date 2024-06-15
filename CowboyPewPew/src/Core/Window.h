#pragma once

#include <stdint.h>
#include <Events/Event.h>

struct WindowProps
{
	uint32_t Width, Height;
	std::string Title;
};

class Window
{
public:
	virtual ~Window() {}

	virtual void OnUpdate() = 0;

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;

	virtual void Shutdown() = 0;

public:

	EventHandler<KeyPressedEventArg> KeyPressedEventHandler;
private:
	
};