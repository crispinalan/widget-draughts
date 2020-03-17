/***************************************************************************
 *   Author Alan Crispin aka. crispina                                     *
 *   crispinalan@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/



#include "mainwindow.h"

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
// mouse events
EVT_LEFT_DOWN(MainWindow::onMouseLeftDown)
EVT_LEFT_UP(MainWindow::onMouseLeftUp)
// catch paint events
EVT_PAINT(MainWindow::paintEvent)
EVT_MENU(MENU_Exit, MainWindow::OnMenuExit)
EVT_MENU(MENU_RESET, MainWindow::OnMenuResetBoard)
EVT_MENU(MENU_ABOUT, MainWindow::OnMenuAbout)
END_EVENT_TABLE()



MainWindow::MainWindow() 
	:wxFrame(nullptr,wxID_ANY,"Widget Draughts", wxPoint(30,30), wxSize(800,760))
{
    	
	statusText="White (human) to move ...";	
	statusbar=CreateStatusBar(2);
	wxFont font(14,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false);
    statusbar->SetFont(font);	
    SetStatusText(statusText, 0);
	
	//Add menu bar
	m_MenuBar = new wxMenuBar();
    this->SetMenuBar(m_MenuBar);
	
	//Add menu operations
	wxMenu *menuFile = new wxMenu();
	menuFile->Append(MENU_Exit, "&Exit", "Exit Draughts Game");
	m_MenuBar->Append(menuFile,"File");
	
	wxMenu *menuGame = new wxMenu();
	menuGame->Append(MENU_RESET, "&Reset Board", "Reset Board");
	m_MenuBar->Append(menuGame,"Game");
	
	wxMenu *menuHelp = new wxMenu();
	menuHelp->Append(MENU_ABOUT,"&About Draughts","About Draughts");
	m_MenuBar->Append(menuHelp,"Help");	
	//resizing to do
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintNow()
{
	wxClientDC dc(this);
    render(dc);
}
void MainWindow::paintEvent(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
    render(dc);
}
void MainWindow::render(wxDC& dc)
{
	
	board.render(dc);
}
bool MainWindow::convertMousePosToXY(const wxPoint& pos, int& x, int& y) const
{
	const int xpos = pos.x / squareSize;
    const int ypos = pos.y / squareSize;
	
	if ( xpos < 0 || xpos >= 8
         || ypos < 0 || ypos >= 8)
    {
        return false; // not on a square
    }
	x=xpos;
	y=ypos;
	return true;
}

void MainWindow::onMouseLeftDown(wxMouseEvent& event)
{
	int row;
	int col;
	playerFinished =false;	
	if (!ConvertMousePosToRowAndColumn(event.GetPosition(), row, col))
		return;	
	m_rowLeftMDown=row;
	m_colLeftMDown=col; 

 event.Skip();	
	
}

void MainWindow::onMouseLeftUp(wxMouseEvent& event)
{
	
	int row;
	int col;	
	if (!ConvertMousePosToRowAndColumn(event.GetPosition(), row, col))
		return;	
	m_rowLeftMUp=row;
	m_colLeftMUp=col;
	
	int row1=m_rowLeftMDown;
	int col1=m_colLeftMDown;
	int row2 =m_rowLeftMUp;
	int col2= m_colLeftMUp;

    	
	if (board.makeWhiteMove(row1,col1,row2,col2))
	{
		paintNow();	
		
		if (board.isWhiteMoveAJump(row1,col1,row2,col2)
		 && board.canJumpAgainWhite(row2,col2))
		{
			
			statusText.clear();
	        statusText="White can jump again ...";
			SetStatusText(statusText, 0);
			playerFinished=false;
			event.Skip();
			return;
			
		}
		else
		{
		playerFinished=true;
		statusText.clear();
		}		
	}	
	
	//check for white win	
	int blackNumber = board.numberBlackKingsOnBoard() + board.numberBlackPiecesOnBoard();
    if(blackNumber==0)
	{		

	wxString msg;
	msg<<"White wins..";
    wxMessageBox(msg);
	
	board.resetBoard();
	paintNow();
	statusText.clear();
	statusText="New game: White (human) to move ...";
	SetStatusText(statusText, 0);
    event.Skip();
	return;	
	}
	
	
	if (playerFinished)	
	{
	statusText="Computer thinking ...";
	SetStatusText(statusText, 0);	
	board.makeComputerMovement();
	paintNow();	
	statusText.clear();
	statusText="White to move ...";
	SetStatusText(statusText, 0);
		
	//check for black win	
    int whiteNumber=board.numberWhiteKingsOnBoard() + board.numberWhitePiecesOnBoard();
    if(whiteNumber==0)
	{	
	wxString msg;
	msg<<"Black wins..";
    wxMessageBox(msg);
	board.resetBoard();
	paintNow();
	statusText.clear();
	statusText="New game: White (human) to move ...";
	SetStatusText(statusText, 0);
    event.Skip();
	return;		
	}	
	}
	paintNow();		
	event.Skip();
}
bool MainWindow::ConvertMousePosToRowAndColumn(const wxPoint& pos, int& row, int& col) const
{

    const int colIdx = pos.x / squareSize;
    const int rowIdx = pos.y / squareSize;

    if(colIdx < 0 || colIdx >= 8 || rowIdx < 0 || rowIdx >= 8) {
	return false; // not on a square
    }
    row = rowIdx;
    // row =static_cast<int>(SquaresPerSide - rowIdx);
    col = colIdx;
    return true;
}
void MainWindow::OnMenuAbout(wxCommandEvent& evt)
{
	
wxMessageBox(wxString("Widget Draughts 2020\nAuthor Alan Crispin\ngithub.com/crispinalan"),
                wxString("About Widget Draughts 1.1.0"),
                wxOK|wxICON_INFORMATION, this );

}
void MainWindow::OnMenuResetBoard(wxCommandEvent& evt)
{
	
	board.resetBoard();
	paintNow();
}
void MainWindow::OnMenuExit(wxCommandEvent& evt)
{
	Close(true);
	evt.Skip();
}













