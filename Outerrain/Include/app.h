#pragma once

#include "Window.h"

class App
{
protected:
	Window m_window;
	Context m_context;

public:
	App(const int&, const int&, const int&, const int&);
	virtual ~App();

	virtual int Init();
	virtual int Update(const float, const float);
	virtual int Render();
	virtual void Run();
	virtual void Quit();
};