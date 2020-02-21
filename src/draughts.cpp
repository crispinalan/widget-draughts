#include "draughts.h"

wxIMPLEMENT_APP(Draughts); // macro to generate main entry point

Draughts::Draughts()
{
}

Draughts::~Draughts()
{
}

bool Draughts::OnInit()
{
	w = new MainWindow();
	w->SetAutoLayout(true);
	w->Show(true);

	return true;
}