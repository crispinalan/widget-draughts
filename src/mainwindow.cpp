/***************************************************************************
 Author Alan Crispin aka. crispina                                    
    crispinalan@gmail.com         
 
   Copyright 2020  Alan Crispin

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 ***************************************************************************/



#include "mainwindow.h"

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
// mouse events
EVT_LEFT_DOWN(MainWindow::onMouseLeftDown)
//EVT_LEFT_UP(MainWindow::onMouseLeftUp)
// catch paint events
EVT_PAINT(MainWindow::paintEvent)

//menu events
EVT_MENU(MENU_Exit, MainWindow::OnMenuExit)
EVT_MENU(MENU_EASY, MainWindow::OnMenuEasyGame)
EVT_MENU(MENU_MEDIUM, MainWindow::OnMenuMediumGame)
EVT_MENU(MENU_HARD, MainWindow::OnMenuHardGame)

EVT_MENU(MENU_RESET, MainWindow::OnMenuResetBoard)
EVT_MENU(MENU_ABOUT, MainWindow::OnMenuAbout)
END_EVENT_TABLE()

MainWindow::MainWindow() 
	:wxFrame(nullptr,wxID_ANY,"Draughts", wxPoint(30,30), wxSize(740,740))
{
    

    setupBoard(theBoard);
	//displayBoard(theBoard);
	paintNow(); //calls render
	currentPiece=BLACK_M; //black to move first

	statusText="Black (human) to move";	
	statusbar=CreateStatusBar(2);
	wxFont font(11,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false);
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
	menuGame->Append(MENU_EASY, "&Search Depth 8 (Quick)", "Easy");
	menuGame->Append(MENU_MEDIUM, "&Search Depth 10 (Moderate)", "Medium");
	menuGame->Append(MENU_HARD, "&Search Depth 14 (Slow)", "Hard");
	
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
	
	wxRect squareRect(wxSize(squareSize, squareSize));
	
	for(int y = 0; y<BOARDSIZE; ++y){  //y=rows
		for(int x = 0; x<BOARDSIZE; ++x) //x=cols
		{
			if((y+x)%2 == 0)
			{
				dc.SetBrush(*wxWHITE_BRUSH);
				dc.SetPen( wxPen( wxColor(0,0,0), 1 ) ); //reset pen
				dc.DrawRectangle(squareRect);
			}
			else{
				
				dc.SetBrush(*wxLIGHT_GREY_BRUSH);
				dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );//reset pen
				dc.DrawRectangle(squareRect);
				
				//char p = theBoard[y][x]; //re-orientate board
				char p = theBoard[x][y];
				//cout<<"Piece ("<<x<<","<<y<<") = "<<p<<endl;
				
				if(p == WHITE_M) {
					dc.SetBrush(*wxWHITE_BRUSH);
					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;
					dc.DrawCircle(xc, yc, radius);
				}

				if(p== WHITE_K)

					{
					dc.SetBrush(*wxWHITE_BRUSH);  //filling
					dc.SetPen( wxPen( wxColor(255,0,0), 5 ) );  //5-pixels-thick red king outline

					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;
					dc.DrawCircle(xc, yc, radius);
					dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );//reset pen
				    }

				if(p == BLACK_M){
					dc.SetBrush(*wxBLACK_BRUSH); // filling
					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;
					dc.DrawCircle(xc, yc, radius);
					}

				if(p == BLACK_K)
					{
					dc.SetBrush(*wxBLACK_BRUSH);  //filling
					dc.SetPen( wxPen( wxColor(255,0,0), 5 ) );  //5-pixels-thick red king outline

					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;
					dc.DrawCircle(xc, yc, radius);
					dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );//reset
					}			
				
				
			}//else
			
				squareRect.Offset(squareSize,0);
		}//x (cols)
		
		squareRect.Offset(0,squareSize); //new line
		squareRect.SetLeft(0);
		
	}//y (row)
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
	int x=0;
	int y=0;
	wxString msg;
	
	if(!convertMousePosToXY(event.GetPosition(),x,y)) return;
	
	if(firstClick){		
		
	x1=x;
	y1=y;
	
	//msg.clear();	
	//msg<<"First Click: Pos ("<<x1<<","<<y1<<")";
	//wxMessageBox(msg);		
	firstClick=false;
	event.Skip();
	return;
	}
	else {
	
	x2=x;
	y2=y;	
	currentPiece=getPiece(theBoard,x1,y1); //set gobally
	currentPlayer=BLACK;
	
	if (findMakeBlackMove(theBoard,x1,y1,x2,y2))
	{
		paintNow();	//board with black move			
		firstClick=true;
		playerFinished=true;
		
		if(checkForWin(theBoard,BLACK)) {
			msg.clear();
			msg<<"Black wins..";
			wxMessageBox(msg);
			firstClick=true;
			playerFinished=false;			
			event.Skip();
			return;
		}
	}
	else {
		msg.clear();
		msg<<"Illegal move (wrong position or check for jumps)";
	    wxMessageBox(msg);
		firstClick=true;
		playerFinished=false;
		event.Skip();
		return;
	}	
		
	if (playerFinished)	
	{
		//computer move		
		wxString ds; 
	    ds<<maxDepth;
		statusText.clear();
		statusText="Computer thinking (Depth = ";
		statusText.append(ds);
		statusText.append(")");
		SetStatusText(statusText, 0);	
		
		makeBestAIMovement(theBoard);			
		paintNow();	
		playerFinished=false;
		statusText.clear();
		statusText="Black to move";
		SetStatusText(statusText, 0);
			
		if(checkForWin(theBoard,WHITE)) {
		msg.clear();
		msg<<"White wins..";
		wxMessageBox(msg);
		firstClick=true;
		playerFinished=false;			
		statusText.clear();
		statusText="Black to move";
		SetStatusText(statusText, 0);
		event.Skip();
		return;
		}
	}	
	
	} //else first click
	
event.Skip();	
}



void MainWindow::OnMenuAbout(wxCommandEvent& evt)
{


wxMessageBox(wxString("Widget Draughts  2020 v1.1.0"
						"\nAuthor Alan Crispin\ngithub.com/crispinalan"
						"\nBlack: human player"
						"\nWhite: AI player"								
						"\nClick start position then click end position"),
                wxString("About Widget Draughts "),
                wxOK|wxICON_INFORMATION, this );

}
void MainWindow::OnMenuResetBoard(wxCommandEvent& evt)
{
	statusText.clear();
	statusText="Black (human) to move.";
	SetStatusText(statusText, 0);
	setupBoard(theBoard);
	paintNow();
}
void MainWindow::OnMenuExit(wxCommandEvent& evt)
{
	Close(true);
	evt.Skip();
}
void MainWindow::setupBoard(char board[BOARDSIZE][BOARDSIZE])
{
	for (int y = 0; y < BOARDSIZE; y++){
		for (int x = 0; x < BOARDSIZE; x++){
				board[x][y] = EMPTY;
			}
	}
		
	//White pieces (x,y)
	board[0][1] =WHITE_M;
	board[1][0] =WHITE_M;
	board[1][2] =WHITE_M;
	board[2][1] =WHITE_M;
	board[3][0] =WHITE_M;
	board[3][2] =WHITE_M;
	board[4][1] =WHITE_M;
	board[5][0] =WHITE_M;
	board[5][2] =WHITE_M;	
	board[6][1] =WHITE_M;
	board[7][0] =WHITE_M;
	board[7][2] =WHITE_M;
	
	//black pieces	
	board[0][7] = BLACK_M;
	board[0][5] = BLACK_M;
	board[1][6] = BLACK_M;
	board[2][7] = BLACK_M;
	board[2][5] = BLACK_M;
	board[3][6] = BLACK_M;
	board[4][7] = BLACK_M;
	board[4][5] = BLACK_M;
	board[5][6] = BLACK_M;
	board[6][7] = BLACK_M;
	board[6][5] = BLACK_M;
	board[7][6] = BLACK_M;
	
}


Pos MainWindow::getPrevDiag(Pos from, Pos to)
{
	Pos res;
	if (from.x - to.x > 0) res.x = to.x + 1;
	else res.x = to.x - 1;
	if (from.y - to.y > 0) res.y = to.y + 1;
	else res.y = to.y - 1;
	return res;	
}
Pos MainWindow::getNextDiag(Pos from, Pos to)
{
	Pos res;
	if (from.x - to.x > 0) res.x = to.x - 1;
	else res.x = to.x + 1;
	if (from.y - to.y > 0) res.y = to.y - 1;
	else res.y = to.y + 1;
	return res;	
}



void MainWindow::duplicateBoard(char board1[BOARDSIZE][BOARDSIZE], char board2[BOARDSIZE][BOARDSIZE])
{
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++) 
			board2[i][j] = board1[i][j];
}

bool MainWindow::isValidPos(Pos pos)
{
	if(pos.x>=0 && pos.x<BOARDSIZE && 
	pos.y >=0 && pos.y<BOARDSIZE) return true;
	else return false;	
}

int MainWindow::isKing(char piece)
{
	return (piece==WHITE_K || piece ==BLACK_K);
}

int MainWindow::isOpposite(COLOUR player, char piece)
{
	if (player == WHITE && (piece == BLACK_M || piece == BLACK_K)) return 1;
	if (player == BLACK && (piece == WHITE_M || piece == WHITE_K)) return 1;
	return 0;	
}

COLOUR MainWindow::getOppositeColour(COLOUR player)
{
	// Return the opposite colour to the argument
   if(player == WHITE) return BLACK;
	else return WHITE;
}

int MainWindow::isEndOfBoard(Pos piece, COLOUR player)
{
	if (player == WHITE) return piece.y == BOARDSIZE - 1;
	else return piece.y == 0;
}

int MainWindow::getDiagDirection(Pos from, Pos to)
{
	if (from.y>to.y )  return -1;
		else return 1;
	return 0;
}

bool MainWindow::destinationsValid(std::vector<Pos> dests)
{
	//check destinations are on board
	for(unsigned int i=0; i<dests.size(); i++)
	{
		Pos p =dests.at(i);
		if(!isValidPos(p)) return false;
	}
		
	return true;
}

int MainWindow::getBestCaptureCount(std::vector<Movement> moves)
{
	//Each position can have a set of moves
	// stored in a vector<Movement> list
	
	int bestCaptureCount=0;
	
	for(unsigned int i=0; i< moves.size(); i++)
	{
		Movement m =moves.at(i);
		int captures = m.numberOfCaptures;
		if(captures>bestCaptureCount)
		{
			bestCaptureCount=captures;
		}
	}
	return bestCaptureCount;
}

int MainWindow::numberWhitePiecesOnBoard(char board[BOARDSIZE][BOARDSIZE])
{
	int numberWhitePieces=0;

	for(int y=0; y<BOARDSIZE; y++){
		for(int x=0; x<BOARDSIZE; x++){
			if(board[x][y]==WHITE_M || board[x][y]==WHITE_K ){
				numberWhitePieces++;
			}
		}
	}
	return numberWhitePieces;
}

int MainWindow::numberBlackPiecesOnBoard(char board[BOARDSIZE][BOARDSIZE])
{
	int numberBlackPieces=0;

	for(int y=0; y<BOARDSIZE; y++){
		for(int x=0; x<BOARDSIZE; x++){
			if(board[x][y]==BLACK_M || board[x][y]==BLACK_K ){
				numberBlackPieces++;
			}
		}
	}
	return numberBlackPieces;
}

std::vector<Movement> MainWindow::getPawnMoves(char board[BOARDSIZE][BOARDSIZE], COLOUR player, Pos pos1)
{
	//Pass board by value as it should be copied for each call so that the 
	//previous state is retained in the call function 	
	vector<Movement> filteredMoves{};	
	vector<Pos> destPositions{}; //destination positions for jump moves
	
	moves.clear(); //clear global moves vector
		
	//pos array of the 4 possible diagonals
	Pos pos[4] = {  { pos1.x - 1, pos1.y - 1 }, 
					{ pos1.x + 1, pos1.y - 1 }, 
					{ pos1.x - 1, pos1.y + 1 }, 
					{ pos1.x + 1, pos1.y + 1 } };
	
	int direction = 1;
	int foundFront = -1;
	
	
	if (player == BLACK) direction = -1;

	for (int i = 0; i < 4; i++){
		
		if ((isValidPos(pos[i])) && 
				(pos[i].y == pos1.y + direction) &&
				(board[pos[i].x][pos[i].y] == EMPTY) )
		{ 	
			//---------------------------------------
			//normal single move
			//----------------------------------------
			destPositions.clear();	//clear		
			destPositions.push_back(pos[i]); //push current move						
			addMove(pos1,destPositions,0);	
			//return moves;	
			destPositions.clear();
										
		}
		
		else if ((isValidPos(pos[i])) && 
				(pos[i].y == pos1.y + direction) &&
				(isOpposite(player, board[pos[i].x][pos[i].y])))
		{
			//-------------------------------------
			//now in single jump terrirory
			//-------------------------------------
			
			
			char tmp = board[pos[i].x][pos[i].y];	//opposite colour		
			board[pos[i].x][pos[i].y] = EMPTY;			
			board[pos1.x][pos1.y] = EMPTY;			
			Pos pos2 = getNextDiag(pos1, pos[i]);
			//pos2 = getNextDiag(pos1, pos[i]);
			
			
			destPositions.push_back(pos2);		

			//&&(pos[i].y == pos2.y + direction)
								
			if (isValidPos(pos2)  && board[pos2.x][pos2.y] == EMPTY)				
			{
														
				//-----------------------------------------------------
				//now in multiple jumps terriory (recursion)
				//-----------------------------------------------------
				
				//dest_positions.push_back(pos2);
				
				if (!isEndOfBoard(pos2, player)) {					
									 
					//recursively adds capture moves to moves
					foundFront = getPawnCaptureMoves(pos1, pos2, 
													board, player, 1, destPositions);
				}
			   if (foundFront == 0 || isEndOfBoard(pos2, player)) 
				{	
					addMove(pos1,destPositions,1);					
				}				
							
			}
			board[pos[i].x][pos[i].y] = tmp;
			board[pos1.x][pos1.y] = currentPiece; //put piece back on board e.g.curr_piece= BLACK_M
			destPositions.clear();
		}
	}
	return filteredMoves=filterMovesOnCaptureCount(moves);
}

int MainWindow::getPawnCaptureMoves(Pos pos1, Pos pos2, char board[BOARDSIZE][BOARDSIZE], COLOUR player, 
										int countCaptures, std::vector<Pos> destPositions)
{
	//Pass the current board to recursive function by value.
	//It should be copied for each call so that the previous state is retained
	//in the call function (captures).
	
	//cout <<"getCaptureMoves: pos1 = ("<<pos1.col<<","<<pos1.row<<")"<<endl;	
	//cout <<"getCaptureMoves: pos2 = ("<<pos2.col<<","<<pos2.row<<")"<<endl; 
	
	
	Pos pos[4] = { 	{ pos2.x - 1, pos2.y - 1 }, 
					{ pos2.x + 1, pos2.y - 1 }, 
					{ pos2.x - 1, pos2.y + 1 }, 
					{ pos2.x + 1, pos2.y + 1 } };
	int direction = 1;
	int foundNow = 0;
	char tmp =board[pos1.x][pos1.y];
	int foundFront = -1;
	if (player == BLACK) direction = -1;
	
	for (int i = 0; i < 4; i++)
		
		//add direction checking
		//&&(pos[i].y == pos2.y + direction)
		if (isValidPos(pos[i]) 	
		&&(pos[i].y == pos2.y + direction)
		&& isOpposite(player, board[pos[i].x][pos[i].y])){
			
			Pos newPiece = getNextDiag(pos2, pos[i]);		
		
		if (isValidPos(newPiece) && board[newPiece.x][newPiece.y] == EMPTY){
			
			foundNow++;
			
			tmp = board[pos[i].x][pos[i].y]; //copy board piece to tmp 			
			board[pos[i].x][pos[i].y] = EMPTY; //now make pos position empty			
			//vector<Pos> newDests(destPositions.begin(), destPositions.end());			  
			vector<Pos> newDests;			
			newDests.insert(newDests.end(),destPositions.begin(), destPositions.end());
			newDests.push_back(newPiece);			
			
			//if (!(isEndOfBoard(newPiece, player) && !isKing(currentPiece))) 
			if (!(isEndOfBoard(newPiece, player)) && !isKing(currentPiece)) 
				
				foundFront = getPawnCaptureMoves(pos1, newPiece, board, player, countCaptures + 1, newDests);
				
			if (foundFront == 0 || (isEndOfBoard(newPiece, player) && !isKing(currentPiece))) {						
				addMove(pos1,newDests,countCaptures+1);
				newDests.clear();
				
			}				
			newDests.clear();
			board[pos[i].x][pos[i].y] = tmp;
		}
	}	
	return foundNow;
}

std::vector<Movement> MainWindow::getKingMoves(char board[BOARDSIZE][BOARDSIZE], COLOUR player, Pos pos1)
{
	vector<Pos> destPositions{}; //destination positions for jump moves
	vector<Movement> filteredMoves {};	
	moves.clear(); //clear global moves vector
	
	
	//pos array of the 4 possible diagonals
	Pos pos[4] = {  { pos1.x - 1, pos1.y - 1 }, 
					{ pos1.x + 1, pos1.y - 1 }, 
					{ pos1.x - 1, pos1.y + 1 }, 
					{ pos1.x + 1, pos1.y + 1 } };
	
	Pos curr, newPiece;
	int foundFront = -1;
	

	for (int i = 0; i < 4; i++){
		curr=pos[i];
		if ((isValidPos(curr)) && 				
				(board[curr.x][curr.y] == EMPTY) )
		{ 	
			//---------------------------------------
			//normal single move
			//----------------------------------------
			destPositions.clear();	//clear		
			destPositions.push_back(curr); //push current move								
			addMove(pos1,destPositions,0);	
								
										
		}
		
		else if ((isValidPos(curr)) && 
				(isOpposite(player, board[curr.x][curr.y])))
		{
			//-------------------------------------
			//now in jumping terrirory
			//-------------------------------------
		
			char tmp = board[curr.x][curr.y];	//opposite colour		
			board[curr.x][curr.y] = EMPTY;			
			board[pos1.x][pos1.y] = EMPTY;			
			//Pos pos2 = getNextDiag(pos1, pos[i]);
			newPiece=getNextDiag(pos1,curr);
			destPositions.push_back(newPiece);
								
			if (isValidPos(newPiece) && board[newPiece.x][newPiece.y] == EMPTY)				
			{
				
				foundFront = getKingCaptureMoves(pos1, newPiece,board, player, 1, destPositions);	
				
			   if (foundFront == 0) 
				{		
				
					addMove(pos1,destPositions,1);
				}				
							
			}
			
			destPositions.clear();
			board[pos[i].x][pos[i].y] = tmp;		
		}
		
	}
		return filteredMoves=filterMovesOnCaptureCount(moves);
}

int MainWindow::getKingCaptureMoves(Pos pos1, Pos pos2, char board[BOARDSIZE][BOARDSIZE], COLOUR player, int countCaptures, std::vector<Pos> destPositions)
{
	//cout <<"getKingCaptureMoves: pos1 = ("<<pos1.col<<","<<pos1.row<<")"<<endl;
	//cout <<"getKingCaptureMoves: pos2 = ("<<pos2.col<<","<<pos2.row<<")"<<endl; 
	
	Pos pos[4] = { 	{ pos2.x - 1, pos2.y - 1 }, 
					{ pos2.x + 1, pos2.y - 1 }, 
					{ pos2.x - 1, pos2.y + 1 }, 
					{ pos2.x + 1, pos2.y + 1 } };
	
	int foundNow = 0;
	char tmp =board[pos1.x][pos1.y];
	int foundFront = -1;
	
	for (int i = 0; i < 4; i++)
		
		if (isValidPos(pos[i]) && isOpposite(player, board[pos[i].x][pos[i].y])){
			
			Pos newPiece = getNextDiag(pos2, pos[i]);
					
		if (isValidPos(newPiece) && board[newPiece.x][newPiece.y] == EMPTY){
			
			foundNow++;
			
			tmp = board[pos[i].x][pos[i].y]; //copy board piece to tmp 			
			board[pos[i].x][pos[i].y] = EMPTY; //now make pos position empty			
						
			vector<Pos> newDests(destPositions.begin(), destPositions.end());	
			newDests.push_back(newPiece);	
			
							
			if (!(isEndOfBoard(newPiece, player)))
							
				foundFront = getKingCaptureMoves(pos1, newPiece, board, player, countCaptures + 1, newDests);
				
			if (foundFront == 0) {
				addMove(pos1,newDests,countCaptures+1);				
			}
				
			newDests.clear();
			board[pos[i].x][pos[i].y] = tmp;	
		}
	}
	
	return foundNow;
}

void MainWindow::addMove(Pos piece, std::vector<Pos> destinationsList, int captureCount)
{
	Movement m_tmp {};
	m_tmp.start=piece;
	m_tmp.dests=destinationsList;	
	m_tmp.numberOfCaptures=captureCount;	
	
	if (destinationsValid(destinationsList)) 
	moves.push_back(m_tmp);
}

std::vector<Movement> MainWindow::filterMovesOnCaptureCount(std::vector<Movement> moves)
{
	//filter moves for valid moves only
	vector<Movement> filteredMoves {};
	//filteredMoves.insert(filteredMoves.end(), moves.begin(), moves.end());
	
	int bestCaptureCount = getBestCaptureCount(moves);
	
	if (bestCaptureCount>0)
	{
		//only add moves with capture count >zero
		
	for(unsigned int i=0; i<moves.size(); i++)
	{
		Movement m =moves.at(i);
		int captures = m.numberOfCaptures;
		if(captures>0) filteredMoves.push_back(m);
	}		
	return filteredMoves;			
	}
	
	return moves; //else just return original moves
}

std::vector<Movement> MainWindow::getAllMoves(char board[BOARDSIZE][BOARDSIZE], COLOUR player)
{
	Pos p;
	vector<Movement> allMoves{};
	vector<Movement> legalMoves{};
	char currPiece;
	
	for (int x = 0; x < BOARDSIZE; x++)
		for (int y = 0; y < BOARDSIZE; y++)
			if (!isOpposite(player, board[x][y]) && board[x][y] != EMPTY){
		p.y = y;
		p.x = x;
		currPiece = board[x][y];
		
		//cout<<"getAllMoves(): testing currPiece ("<<x<<","<<y<<") = "<<currPiece<<endl;
		if (isKing(currPiece)){ 
			if(player==WHITE) currentPiece=WHITE_K; //globals
			if(player==BLACK) currentPiece=BLACK_K;
			vector<Movement> king_moves =getKingMoves(board, player, p);
            allMoves.insert(allMoves.end(), king_moves.begin(),king_moves.end()); 
			}
		else {
			if(player==WHITE) currentPiece=WHITE_M; //globals
			if(player==BLACK) currentPiece=BLACK_M;
			vector<Movement> pawn_moves = getPawnMoves(board, player, p);
			allMoves.insert(allMoves.end(), pawn_moves.begin(),pawn_moves.end());
			} 
		}
		
	int count = getBestCaptureCount(allMoves);
		
	if (count == 0) return allMoves; //don't change allmoves as no capture
	else {		
	for(unsigned int i=0; i<allMoves.size(); i++)
	{
		Movement m =allMoves.at(i);
		int captures = m.numberOfCaptures;
		if(captures >0)
		{
			legalMoves.push_back(m);
		}
	}	
	}
	return legalMoves;	
}

void MainWindow::makeMove(char board[BOARDSIZE][BOARDSIZE], Movement move)
{
	
	
	Pos cur;
	Pos cap;  //capture
		
	cur.x=move.start.x;
	cur.y=move.start.y;	
			
	//cout<<"makeMove: start ("<<cur.x<<","<<cur.y<<") piece_type = "<<board[cur.x][cur.y]<<endl;
			
	if(move.dests.empty()) return;
		
	for(unsigned int i =0; i<move.dests.size(); i++)
	{
			
		board[move.dests[i].x][move.dests[i].y] = board[cur.x][cur.y];	
				
		//check for kings
		if((move.dests[i].y == 0) && (board[cur.x][cur.y] == BLACK_M)) {
			board[move.dests[i].x][move.dests[i].y] = BLACK_K;
			currentPiece=BLACK_K;
		}

		if((move.dests[i].y == BOARDSIZE - 1) && (board[cur.x][cur.y] == WHITE_M)) {
			board[move.dests[i].x][move.dests[i].y] = WHITE_K;
			currentPiece=WHITE_K;
		}
		
		board[cur.x][cur.y] = EMPTY;
			
		if (move.numberOfCaptures > 0){
			 cap = getPrevDiag(cur, move.dests[i]);
			 //cout<<"Capture pos = ("<<cap.x<<","<<cap.y<<")"<<endl;
			 board[cap.x][cap.y] = EMPTY;
		}
		
	cur.x = move.dests[i].x;
	cur.y = move.dests[i].y;	
		
	}		
}

int MainWindow::alphabeta(char board[BOARDSIZE][BOARDSIZE], int depth, int alpha, int beta, COLOUR player, Movement& bestMovement)
{
	char newBoard[BOARDSIZE][BOARDSIZE];
	//duplicateBoard(board, copyboard);
	vector<Movement> moveList = getAllMoves(board, player);
	if(depth == 0 && !moveList.empty()) //first run
	{
		bestMovement=moveList.at(0);
		if(moveList.size()==1) return 100; //no other moves
	}

	
	// If it is a leaf (end node), return the value of the heuristic function
	if(depth == maxDepth) {	
		return calcScore(board, player);
		
	}
	
	if(player != aiColour)
	{
		
		for(auto& m: getAllMoves(board, player))
		{
			
			duplicateBoard(board,newBoard);			
			makeMove(newBoard,m);
			// take the MIN value
			beta = std::min(beta, alphabeta(newBoard, depth+1, alpha, beta, aiColour, bestMovement));
			// If alpha> = beta  cut off the alpha branch
			if(alpha >= beta) break;
		}		
		return beta;
	}

	//AI movement
	else
	{		
		for(auto& m: getAllMoves(board, player))
		{			
			duplicateBoard(board,newBoard);			
			makeMove(newBoard,m);			
			int temp = alphabeta(newBoard, depth+1, alpha, beta, getOppositeColour(aiColour), bestMovement);

			// MAX 			
			if(temp > alpha)
			{
				// if temp> alpha, then assign alpha = temp
				alpha = temp;
				if(depth == 0) bestMovement = m;
			}
			// if alpha> = beta cut off the beta branch
			if(alpha >= beta) break;

		}
		return alpha;
	}
}

int MainWindow::getPieceScore(char piece, COLOUR player)
{
	if (player == WHITE) switch (piece){
	case BLACK_M: return -1;
	case BLACK_K: return -3;
	case WHITE_M: return 1;
	case WHITE_K: return 3;
	}
	else switch (piece){
	case BLACK_M: return 1;
	case BLACK_K: return 3;
	case WHITE_M: return -1;
	case WHITE_K: return -3;
	}
	return 0;
}

int MainWindow::calcScore(char board[BOARDSIZE][BOARDSIZE], COLOUR player)
{
	int score = 0;
    int opposites = 0;
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++){
		if (isOpposite(player, board[i][j])) opposites++;
		score += getPieceScore(board[i][j], player);
		//cout<<"Board position: board["<<i<<"]["<<j<<"] score: "<<score<<endl;
		}
	if (opposites == 0) return 100;
	return score;
}


bool MainWindow::findMakeBlackMove(char board[BOARDSIZE][BOARDSIZE],int x1, int y1, int x2, int y2)
{
	//Get black moves for board
	char copyBoard[BOARDSIZE][BOARDSIZE];
	duplicateBoard(board,copyBoard);
	
	std::vector<Movement> blackMoves = getAllMoves(board,BLACK);
		
	if(blackMoves.empty()) return false;
	
	duplicateBoard(copyBoard,board);
	
	for(unsigned int i=0; i<blackMoves.size(); i++)
	{
		Movement m =blackMoves.at(i);		
		
		if (m.start.x ==x1 && m.start.y == y1)
		{			
			if(m.dests.at(m.dests.size()-1).x ==x2 &&
				m.dests.at(m.dests.size()-1).y ==y2)	{
					//found move
					//duplicateBoard(copyBoard,board);
					makeMove(board,m);
					return true;
				}
			
		}
	}
	duplicateBoard(copyBoard,board);
	return false;
}
bool MainWindow::checkForWin(char board[BOARDSIZE][BOARDSIZE], COLOUR player)
{
	if(player ==BLACK)	{
	//check for black win	
	int whiteNumber =numberWhitePiecesOnBoard(board);
    if(whiteNumber==0) return true;	
	}
	if(player ==WHITE) {
		//check for white win	
    int blackNumber=numberBlackPiecesOnBoard(board);
    if(blackNumber==0) return true;
	}
	
	return false;
}
char MainWindow::getPiece(char board[BOARDSIZE][BOARDSIZE], int x, int y)
{
	char piece = board[x][y];	
	return piece;
}

void  MainWindow::makeBestAIMovement(char board[BOARDSIZE][BOARDSIZE])
{
		
	Movement best_movement;		
	
	char copyBoard[BOARDSIZE][BOARDSIZE];
	duplicateBoard(board, copyBoard);
	alphabeta(board,0,-100,100,WHITE,best_movement);
	
	//resore original board
	duplicateBoard(copyBoard,board);	
	makeMove(board,best_movement);	
}

void MainWindow::OnMenuEasyGame(wxCommandEvent& evt)
{
	maxDepth=8;
}

void MainWindow::OnMenuMediumGame(wxCommandEvent& evt)
{
	maxDepth=10;
}

void MainWindow::OnMenuHardGame(wxCommandEvent& evt)
{
	maxDepth=14;
}
