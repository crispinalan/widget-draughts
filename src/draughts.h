#pragma once
#include <wx/wx.h>
#include "mainwindow.h"

class Draughts : public wxApp
{
public:
	Draughts();
	~Draughts();
	MainWindow *w = nullptr;
	
public:
    virtual bool OnInit();
};

