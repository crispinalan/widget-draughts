#include "mainwindow.h"

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
// mouse events
EVT_LEFT_DOWN(MainWindow::OnMouseLeftDown)
EVT_LEFT_UP(MainWindow::OnMouseLeftUp)
// catch paint events
EVT_PAINT(MainWindow::PaintEvent)
EVT_MENU(MENU_Exit, MainWindow::OnMenuExit)
EVT_MENU(MENU_RESET, MainWindow::OnMenuResetBoard)
EVT_MENU(MENU_ABOUT, MainWindow::OnMenuAbout)
END_EVENT_TABLE()


MainWindow::MainWindow() 
	:wxFrame(nullptr,wxID_ANY,"Widget Draughts", wxPoint(30,30), wxSize(640,740))
{
	ResetBoard();
	statusText="Black (human) to move ...";	
	this->SetMinSize(wxSize(640,740));	
	
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
	
	//this->Refresh();	
	Bind(wxEVT_SIZE, &MainWindow::OnReSize, this ); //crude resizing
		
	white =1; //1=computer 0 = human (main scope)
	black=0;  //1=computer 0=human
	
}

MainWindow::~MainWindow()
{
}

void MainWindow::ResetBoard()
{
	copy(&c[0][0], &c[0][0]+8*8,&board[0][0]);    
	PaintNow();
}


void MainWindow::OnMenuAbout(wxCommandEvent& evt)
{
	wxMessageBox(wxString("Widget Draughts 2020\nAuthor Alan Crispin\ngithub.com/crispinalan"),
                wxString("About Widget Draughts 1.0.1"),
                wxOK|wxICON_INFORMATION, this );
}
void MainWindow::OnMenuResetBoard(wxCommandEvent& evt)
{
	ResetBoard();
}
void MainWindow::OnMenuExit(wxCommandEvent& evt)
{
	Close(true);
	evt.Skip();
	
}

bool MainWindow::isBlack(int player)
{
	if((player== BLACK) || (player==BKING)){
		return true;
	}
	else{
		return false;
	}
}
bool MainWindow::isWhite(int player)
{
	if((player== WHITE) || (player==WKING)){
		return true;
	}
	else{
		return false;
	}
}

void MainWindow::PaintNow()
{
	wxClientDC dc(this);
    render(dc);
}

void MainWindow::PaintEvent(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
    render(dc);
}
void MainWindow::render(wxDC& dc)
{
    
   	wxRect squareRect(wxSize(squareSize, squareSize));	
		
	for(int row=0; row<ROWS; row++) {
		for(int col=0; col<COLS; col++) {
			
			//int index =row+ col*BOARDSIZE;
			
			if((row+col)%2 == 0)
			{
				dc.SetBrush(*wxWHITE_BRUSH);
				dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );//reset pen	
				dc.DrawRectangle(squareRect);				
			}			
			else{
				//dc.SetBrush(*wxMEDIUM_GREY_BRUSH);
				dc.SetBrush(*wxLIGHT_GREY_BRUSH);
				dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );//reset pen	
				//dc.SetBrush(*wxGREEN_BRUSH);
				dc.DrawRectangle(squareRect);
				
				if (board[row][col] == WHITE) { //transform coordinates to row col
					
					dc.SetBrush(*wxWHITE_BRUSH); 
					//dc.SetBrush(*wxYELLOW_BRUSH); // yellow filling					
					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;
					
					dc.DrawCircle(xc, yc, radius);	
				}
				
				if (board[row][col] == WKING) { //transform coordinates to row col
										
					dc.SetBrush(*wxWHITE_BRUSH); // yellow filling
					dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red king outline

					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;
					dc.DrawCircle(xc, yc, radius);	
					dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );//reset pen					
					
				}
				
				if (board[row][col] == BLACK) {
					
					dc.SetBrush(*wxBLACK_BRUSH); // filling				
					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;
					dc.DrawCircle(xc, yc, radius);	
				}
				
				if (board[row][col] == BKING) {
										
					dc.SetBrush(*wxBLACK_BRUSH); // filling					
					dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red king outline

					int xc = squareRect.GetX() + squareRect.GetWidth() / 2;
					int yc = squareRect.GetY() + squareRect.GetHeight() / 2;
					int radius = (squareRect.GetWidth()/2)-5;
					dc.DrawCircle(xc, yc, radius);
					dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );//reset pen						
				}				
				
				
			}//else
			
			 squareRect.Offset(squareSize,0);
		}
		squareRect.Offset(0,squareSize); //new line
		squareRect.SetLeft(0);	
	}	
}
bool MainWindow::isComputer(int player)
{
	if(player==WHITE){
    	if(white==0){
			return false;
		}
		else{
			return true;
		}
	}
	else{
		if(black==0){
			return false;
		}
		else{
			return true;
		}
	}
}
int MainWindow::switchPlayer(int player)
{
	if(player==WHITE){ //WHITE
		return BLACK; //BLACK
	}
	else{
		return WHITE;
	}
	return EMPTY;
}
void MainWindow::swap(int grid[ROWS][COLS], int row1, int col1, int row2, int col2)
{
	int temp;      
    if(row2==7 && (grid[row1][col1]==2 || grid[row1][col1]==4)){
    	grid[row1][col1] = grid[row2][col2];
    
    	grid[row2][col2] = WKING;
    }
    else if(row2==0 && (grid[row1][col1]==3 || grid[row1][col1]==5)){
    	grid[row1][col1] = grid[row2][col2];
    
    	grid[row2][col2] = BKING;
    }
    else{
    temp = grid[row1][col1];
    
    grid[row1][col1] = grid[row2][col2];
    
    grid[row2][col2] = temp;
	}	
}

int MainWindow::makeComputerMove(int grid[ROWS][COLS], int player, int row1, int col1, 
																int row2, int col2)
{
    int jmp_r = 0;
    int jmp_c = 0;
    //  A regular move
    if(row1 - row2 == -1 || row1 - row2 == 1) {
	if(col1 - col2 == 1 || col1 - col2 == -1) {
	    if(canJump == 0) {
		swap(grid, row1, col1, row2, col2);
		return 0;
	    } else {
		//cout << "Computer must capture" << endl;
		return -1;
	    }
	}
    }
    // A jump move
    if(row1 - row2 == -2 || row1 - row2 == 2) {
	if(col1 - col2 == -2 || col1 - col2 == 2) {
	    // check jump position 
	    if(row1 < row2) { 
		jmp_r = row1 + 1;
	    } else { // move up
		jmp_r = row1 - 1;
	    }
	    if(col1 < col2) { 
		jmp_c = col1 + 1;
	    } else { // move up
		jmp_c = col1 - 1;
	    }

	    if(isWhite(player) && !(isBlack(grid[jmp_r][jmp_c]))) {
		// can only jump over opposition
		return -1;
	    }
	    if(isBlack(player) && !(isWhite(grid[jmp_r][jmp_c]))) {
		// can only jump over opposition (put in for future development)
		return -1;
	    }

	    // jump valid:
	    grid[jmp_r][jmp_c] = 1;
	    swap(grid, row1, col1, row2, col2);

	    while(checkJump(grid, player, row2, col2) == 0) {
		computerMove(grid, player);
	    }
	    return 0;
	}
    }
    return -1; // something wrong
}

int MainWindow::checkMove(int grid[ROWS][COLS], int player, int row1, int col1, int row2, int col2)
{
	int jmp_r;
    int jmp_c;  
    
    if(row1 < 0 && ROWS <= row1){ // keeping in bounds
        return -1;
    }
    if(col1 < 0 && COLS <= col1){
        return -1;
    }
        
    if(row2 < 0 && ROWS <= row2){
        return -1;
        
    }
    if(col2 < 0 && COLS<= col2){
        return -1;
    }        
    // check player is moving own piece.
    if(player == WHITE){
        if(grid[row1][col1] != WHITE && grid[row1][col1] != WKING){
            return -1;
        }
    } else { //BLACK
        if(grid[row1][col1] != BLACK && grid[row1][col1] != BKING){
            return -1;
        }
    }    
    //check jumping to a empty location
    if(grid[row2][col2] != EMPTY){
        return -1;
    }    
    // check moving in correct direction
    if(player == WHITE){        
        if(row1 >= row2 &&  grid[row1][col1]==WHITE){
            return -1;
        }
    } else { //BLACK       
        if(row1 <= row2 &&  grid[row1][col1]==BLACK){
            return -1;
        }
    }
    
    // check if a regular move
	if(row1 - row2 == -1 || row1 - row2 == 1){
	    if(col1 - col2 == 1 || col1 - col2 == -1){
	    	if(canJump==0){
	        	return 0;
	        }
	        else{
	        	return -1;
	        }
	    }
	}
    
    //check if a jump move
    if(row1 - row2 == -2 || row1 - row2 == 2){
        if(col1 - col2 == -2 || col1 - col2 == 2){
            // check if the jump position is enemy
            if(row1 < row2){ // move down
                jmp_r = row1 + 1;
            } else { // move up
                jmp_r = row1 - 1;
            }
            if(col1 < col2){ // move down
                jmp_c = col1 + 1;
            } else { // move up
                jmp_c = col1 - 1;
            }
            
            if(isWhite(player) && !(isBlack(grid[jmp_r][jmp_c])))
            {
                return -1;
            }
            if(isBlack(player) && !(isWhite(grid[jmp_r][jmp_c]))){
                return -1;
            }
            
            // move is valid:
            return 0;
        }
    }
  
    return -1; 
}
int MainWindow::testMove(int grid[ROWS][COLS], int player, int row1, int col1, int row2, int col2)
{
	int jmp_r;
    int jmp_c;
    
    // check if a regular move
	if(row1 - row2 == -1 || row1 - row2 == 1){
		if(col1 - col2 == 1 || col1 - col2 == -1){
			if(canJump==0){
				swap(grid,row1,col1,row2,col2);
				return 0;
			}
		}
	}
	//check jump
	if(row1 - row2 == -2 || row1 - row2 == 2){
	    if(col1 - col2 == -2 || col1 - col2 == 2){
	        // check if the jump position is enemy
	        if(row1 < row2){ // move down
	            jmp_r = row1 + 1;
	        } else { // move up
	            jmp_r = row1 - 1;
	        }
	        if(col1 < col2){ // move down
	            jmp_c = col1 + 1;
	        } else { // move up
	            jmp_c = col1 - 1;
	        }
	        
	        // move is valid:
	        grid[jmp_r][jmp_c] = 1;
	        swap(grid,row1,col1,row2,col2); //make the move by swapping 
	               

	        while(checkJump(grid, player, row2, col2)==0){ 	        	
			    testComputer(grid, player); 
	        }	        	
	        return 0;       
	    }
	}
    return -1;    
}
int MainWindow::legalMoves(int player, int grid[ROWS][COLS])
{
	//return number of legal moves
	int num=0;		
	vector<MovePiece> moves = computerCheck(grid, player);	
	if(moves.size()!=0){
		//cout<< "\n\nLegal Moves: "<<endl;		
		for(unsigned int i=0; i<moves.size(); i++){	
			++num;
		}
	}	
return num;	
}
int MainWindow::checkJump(int grid[ROWS][COLS], int player, int rr, int cc)
{
	if(checkMove(grid, player, rr, cc, rr+2, cc-2) == 0){
		return 0;
	}
	if(checkMove(grid, player, rr, cc, rr+2, cc+2) == 0){
		return 0;
	}
	if(checkMove(grid, player, rr, cc, rr-2, cc-2) == 0){
		return 0;
	}
	if(checkMove(grid, player, rr, cc, rr-2, cc+2) == 0){
		return 0;
	}	
	return -1;
}
void MainWindow::computerMove(int grid[ROWS][COLS], int player)
{
	int row1, col1, row2, col2 =0;
	//cout<< "Computer is searching for move now...\n";
	
	vector<MovePiece> moves = computerCheck(grid, player);
	
	MovePiece *best = minimax(grid, player);

	//cout<< "Computer finished searching at depth "<<dep<<" in "<<tim<<" seconds"<<endl;

	row1 = best->r1;
	col1 = best->c1;
	row2 = best->r2;
	col2 = best->c2;	
	canJump=0;	
	delete best; //to prevent sementation fault	
	makeComputerMove(grid, player, row1-1,col1,row2-1,col2);
}
int MainWindow::testComputer(int grid[ROWS][COLS], int player)
{
	int row1, col1, row2, col2 =0;		
	vector<MovePiece> moves = computerCheck(grid, player);
	MovePiece *best = minimax(grid, player);
	row1 = best->r1;
	col1 = best->c1;
	row2 = best->r2;
	col2 = best->c2;	
	canJump=0;	
	delete best;  //nto prevent seg fault		
	testMove(grid, player, row1-1,col1,row2-1,col2);
	return 0;
}
vector<MovePiece> MainWindow::computerCheck(int grid[ROWS][COLS], int player)
{
	//return movelist
	int rr =0;
	int cc= 0;	
	vector<MovePiece> moveList;
	MovePiece current(rr,cc,rr,cc);
	canJump = 0;	
	for(rr=0; rr<ROWS; ++rr){
		for(cc=0; cc<COLS; ++cc){			
			//Jumping moves
			if(checkMove(grid, player, rr, cc, rr+2, cc-2) == 0){   
				canJump = 1;				
				current.Change((rr+1), (cc), (rr+3), (cc-2));				
				moveList.push_back(current);
			}
			if(checkMove(grid, player, rr, cc, rr+2, cc+2) == 0){ 
				canJump = 1;
				current.Change(rr+1, cc,rr+3,cc+2);
				moveList.push_back(current);
			}
			if(checkMove(grid, player, rr, cc, rr-2, cc-2) ==0){ 
				canJump = 1;
				current.Change(rr+1,cc,rr-1,cc-2);
				moveList.push_back(current);
			}
			if(checkMove(grid, player, rr, cc, rr-2, cc+2) ==0){ 
				canJump = 1;
				current.Change(rr+1,cc,rr-1,cc+2);
				moveList.push_back(current);
			}
		}
	}
	
	for(rr=0; rr<ROWS; ++rr){
		for(cc=0; cc<COLS; ++cc){			
			//Normal moves
			if(checkMove(grid, player, rr, cc, rr+1, cc-1) == 0){ 
				current.Change(rr+1,cc,rr+2,cc-1);
				moveList.push_back(current);
			}
			if(checkMove(grid, player, rr, cc, rr+1, cc+1) == 0){ 
				current.Change(rr+1,cc,rr+2,cc+1);
				moveList.push_back(current);
			}
			if(checkMove(grid, player, rr, cc, rr-1, cc-1) == 0){
				current.Change(rr+1,cc,rr,cc-1);
				moveList.push_back(current);
			}
			if(checkMove(grid, player, rr, cc, rr-1, cc+1) == 0){ 
				current.Change(rr+1,cc,rr,cc+1);				
				moveList.push_back(current);
			}
		}
	}	
	//cout<< "computerCheck moveList size =: "<<moveList.size()<<endl;
	return moveList;	
}

MovePiece* MainWindow::minimax(int grid[ROWS][COLS], int player)
{
	wxString msg;
	MovePiece *bestMove = new MovePiece(0,0,0,0);
	vector<MovePiece> moves = computerCheck(grid, player);	
	if(moves.size()==1){ //only one move
		searchDepth = 1;
		//cout<<"Single move: Search Depth = "<<searchDepth<<endl;
		msg.clear();
		msg<<"Only one move possible";
		SetStatusText(msg, 1);	
		bestMove->Change(moves[0].r1, moves[0].c1, moves[0].r2, moves[0].c2);
		return bestMove;
	}	
	
	int bottom=0;	
	
	//int res =0;
	for(;;){
		 
		if(bottom >= MAX_DEPTH){
			break;
		}
		int depth = 0;
		bottom++;					
		maxMove(grid, bestMove, player, 
		numeric_limits<int>::min(), numeric_limits<int>::max(), bottom, depth);
		
		msg.clear();
		msg<<"Search depth "<<bottom;
		SetStatusText(msg, 1);		

		
		
		//cout <<"maxMove result = "<<res<<endl;
		//cout <<"bottom = "<<bottom<<endl;
		//cout <<"depth = "<<depth<<endl;
	
	}	
	//searchDepth = bottom;	
	//cout<<"Search Depth = "<<searchDepth<<endl;
	return bestMove;
}
int MainWindow::maxMove(int grid[ROWS][COLS],
    MovePiece* bestMove,
    int player,    
    int alpha,
    int beta,
    int bottom,
    int depth)
{
	int res = numeric_limits<int>::min();
	int b[ROWS][COLS];
	std::copy(&grid[0][0], &grid[0][0]+ROWS*COLS,&b[0][0]);	
	vector<MovePiece> moves = computerCheck(b, player);	
		
	if(moves.size()==0 || depth >= bottom){		
		return evaluation2(b,player);
	}	
	for(unsigned int i=0; i<moves.size(); i++){
		moves = computerCheck(b, player);
		testMove(b, player, moves[i].r1-1, moves[i].c1, moves[i].r2-1, moves[i].c2);
		MovePiece *opp = new MovePiece(0,0,0,0);		
		int temp;
		depth++;		
		if(!isComputer(switchPlayer(player))){
			if(player==WHITE){
				black = 1;
			}
			else{
				white = 1;
			}
			temp = minMove(b, opp, switchPlayer(player), alpha, beta, bottom, depth);
			if(player==WHITE){
				black = 0;
			}
			else{
				white = 0;
			}
		}
		else{
			temp = minMove(b, opp, switchPlayer(player), alpha, beta, bottom, depth);
		}		
		delete opp;  //delete to avoid segmentation fault?	
		//cout<<"temp: "<<temp<<endl;
		if(temp > res){
			res = temp;
			bestMove->Change(moves[i].r1, moves[i].c1, moves[i].r2, moves[i].c2);
		}

		if(res > beta){
			return res;
		}
		
		alpha = std::max(alpha, res);		
		std::copy(&grid[0][0], &grid[0][0]+ROWS*COLS,&b[0][0]);
	}
	return res;
}
int MainWindow::minMove(int grid[ROWS][COLS],
    MovePiece* bestMove,
    int player,    
    int alpha,
    int beta,
    int bottom,
    int depth)
{
	int res= numeric_limits<int>::max();
	int b[ROWS][COLS];
	std::copy(&grid[0][0], &grid[0][0]+ROWS*COLS,&b[0][0]); //copy grid into b
	vector<MovePiece> moves = computerCheck(b, player);	
		
	if(moves.size()==0 || depth >= bottom){
		return evaluation2(b,player);
	}	
	depth++;	
	for(unsigned int i=0; i<moves.size(); i++){
		moves = computerCheck(b, player);
		testMove(b, player, moves[i].r1-1, moves[i].c1, moves[i].r2-1, moves[i].c1);		
		MovePiece *opp = new MovePiece(0,0,0,0);		
		int temp = maxMove(b, opp, switchPlayer(player),alpha, beta, bottom, depth);
		delete opp; //to prevent segmentation fault
		if(temp < res){
			res = temp;
			bestMove->Change(moves[i].r1, moves[i].c1, moves[i].r2, moves[i].c2);			
		}
		std::copy(&grid[0][0], &grid[0][0]+ROWS*COLS,&b[0][0]);		
		if(res < alpha){
			return res;
		}		
		beta = std::min(beta, res);		
	}	
	return res;
}

bool MainWindow::isRegularMove(int grid[ROWS][COLS], int r1, int c1, int r2, int c2)
{
	//check if it's a regular move
	if(r1 - r2 == -1 || r1 - r2 == 1){
		if(c1 - c2 == 1 || c1 - c2 == -1){			
				return true;
			}			
		}
return false;	
}
int MainWindow::numberWhitePiecesOnBoard(int grid[ROWS][COLS])
{
	//int score=0;
	int numberWhitePieces=0;	
    int numberWhiteKings=0;	
 		
	for(int row=0; row<ROWS; row++){
		for(int col=0; col<COLS; col++){
			if(grid[row][col]==WHITE){
				numberWhitePieces++;				
			}
			if(grid[row][col]==WKING){
				numberWhiteKings++ ;				
			}	
		}
	}
	
	return numberWhitePieces+numberWhiteKings;
}
int MainWindow::numberBlackPiecesOnBoard(int grid[ROWS][COLS])
{
	int numberBlackPieces=0;
	int numberBlackKings=0;
 		
	for(int row=0; row<ROWS; row++){
		for(int col=0; col<COLS; col++){					
			if(grid[row][col]==BLACK){
				numberBlackPieces++;				
			}			
			if(grid[row][col]==BKING){
				numberBlackKings++;				
			}
		}
	}
	
	return numberBlackPieces+numberBlackKings;
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
bool MainWindow::isMoveValid2(int grid[ROWS][COLS], int row1, int col1, int row2, int col2)
{
	//cout<<"checking if BLACK (human) move legal"<<endl;	        
		//Need to rewrite to make generic by adding player argument			
	    vector<MovePiece> blackmoves = computerCheck(board, BLACK);	
		if(blackmoves.size()!=0){
		//cout<< "\n\nLegal Moves: "<<endl;		
		for(unsigned int i=0; i<blackmoves.size(); i++){			
			
			if((row1 == blackmoves[i].r1-1) && (col1==blackmoves[i].c1) 
				&&(row2==blackmoves[i].r2-1) && (col2==blackmoves[i].c2))
					return true;
			
		}
		}
	return false;
}


int MainWindow::evaluation1(int grid[ROWS][COLS], int player)
{
	int score=0;
	int numberWhitePieces=0;	
    int numberWhiteKings=0;
	int numberBlackPieces=0;
	int numberBlackKings=0;
 		
	for(int row=0; row<ROWS; row++){
		for(int col=0; col<COLS; col++){
			if(grid[row][col]==WHITE){
				numberWhitePieces++;				
			}
			if(grid[row][col]==WKING){
				numberWhiteKings++ ;				
			}			
			if(grid[row][col]==BLACK){
				numberBlackPieces++;				
			}			
			if(grid[row][col]==BKING){
				numberBlackKings++;				
			}
		}
	}
	
	//Need to check if bank ranks intact
	
	if ((grid[0][1]==WHITE) 
		&& (grid[0][3]==WHITE)
		&& (grid[0][5]==WHITE)
		&& (grid [0][7]==WHITE)
			&& (numberBlackPieces>1))	
			{
				score-=BACKRANK1;
			}
        

	if((grid[7][0]=BLACK) 
		&& (grid[7][2]==BLACK)
		&& (grid[7][4]==BLACK)
		&& (grid[7][6]==BLACK)
		&& (numberWhitePieces>1)) 
		{
			score+=BACKRANK1;
		}  
	
	int materialBlack= numberBlackKings*KING+numberBlackPieces*CHECKER; 
	int materialWhite= numberWhiteKings*KING+numberWhitePieces*CHECKER;
	
	score+= ((materialBlack-materialWhite)*200)
            /(materialBlack+materialWhite);
			
	score+=materialBlack-materialWhite;		
	
	if (player==BLACK)
		return score;
	else
		return -score;
//return score;	
}


int MainWindow::evaluation2(int grid[ROWS][COLS], int player)
{


	int whiteValue=0;
	int blackValue=0;
	 		
	for(int row=0; row<ROWS; row++){
		for(int col=0; col<COLS; col++){
			if(grid[row][col]==WHITE){
				whiteValue-=CHECKER;				
			}
			if(grid[row][col]==WKING){
				whiteValue-=KING;				
			}			
			if(grid[row][col]==BLACK){
				blackValue+=CHECKER;				
			}			
			if(grid[row][col]==BKING){
				blackValue+=KING;				
			}
		}
	}	

//for(int row=0; row<ROWS; row++){
//		for(int col=0; col<COLS; col++){
//			if ((row==0 || row==7)){
//				whiteValue-=BACKRANK1;
//				blackValue+=BACKRANK1;
//			}
//			if ((row==1 || row==6)){
//				whiteValue-=BACKRANK2;
//				blackValue+=BACKRANK2;
//			}
//			if ((row==2 || row==5)){
//				whiteValue-=2;
//				blackValue+=2;
//			}
//			if ((row==3 || row==4)){
//				whiteValue-=BACKRANK3;
//				blackValue+=BACKRANK3;
//			}
//		}
//}


for(int row=0; row<ROWS; row++){
		for(int col=0; col<COLS; col++){
			if ((row==0 || row==7) ||(col==0 ||col==7)){
				whiteValue-=BACKRANK1;
				blackValue+=BACKRANK1;
			}
			if ((row==1 || row==6) ||(col==1 ||col==6)){
				whiteValue-=BACKRANK2;
				blackValue+=BACKRANK2;
			}
			if ((row==2 || row==5) ||(col==2 ||col==5)){
				whiteValue-=2;
				blackValue+=2;
			}
			if ((row==3 || row==4) ||(col==3 ||col==4)){
				whiteValue-=BACKRANK3;
				blackValue+=BACKRANK3;
			}
		}
}


if (player==WHITE)
{
	return whiteValue;
}	
	
else {
	return blackValue;
	}

}

void MainWindow::OnReSize(wxSizeEvent& event)
{
	int frameWidth = this->GetSize().GetWidth();
	//cout <<"framewidth = "<<frameWidth<<endl;
	squareSize=frameWidth/8;

}


void MainWindow::OnMouseLeftDown(wxMouseEvent& event)
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

void MainWindow::OnMouseLeftUp(wxMouseEvent& event)
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
	int jmp_r = 0;
	int jmp_c = 0;
	
	
	//Check if legal move..	
	if (isMoveValid2(board,row1,col1,row2,col2) == false)
	{
			
		statusText.clear();
		statusText = "Move is not valid or jump required";
		SetStatusText(statusText, 0);
		//cout<<"Move is not valid or jump";
		event.Skip();
		return;
	}	
		
	if (isRegularMove(board,row1,col1,row2,col2))
	{
		//regular move
		//cout<<"Regular move ..."<<endl;
		swap(board,row1,col1,row2,col2); //regular move
		playerFinished=true;		
		PaintNow();		
	}
	else{ //jump move		 
		 statusText.clear();
		 statusText = "Black must jump";
		 SetStatusText(statusText, 0);
		 
		 if(row1 - row2 == -2 || row1 - row2 == 2) {
	        if(col1 - col2 == -2 || col1 - col2 == 2) {
		    // check jump position is opposition
		    if(row1 < row2) jmp_r = row1 + 1; // move down		        
		    else jmp_r = row1 - 1; // move up
		    if(col1 < col2) jmp_c = col1 + 1; // move down
			else jmp_c = col1 - 1; // move up
			//  move is valid:
		    board[jmp_r][jmp_c] = EMPTY; // remove jump piece
		    swap(board, row1, col1, row2, col2);	//move	   
		    PaintNow();
			//cout << "Jump move completed -checking for further jumps.." << endl;
		    // playerFinished=false;
			 // check for further jumps
			if (checkJump(board, BLACK, row2, col2) == 0) {

		        //cout << "There is another jump" << endl;
		        statusText.clear();
		        statusText = "Black can jump again ...";
		        SetStatusText(statusText, 0);
				playerFinished=false;
				event.Skip();
				return;				
			}
			else {
				//no more jumps
				//cout << "No more jumps" << endl;
				playerFinished=true;
				statusText.clear();
				//event.Skip();				
			}			
	        }
	    }
		
	}

//Check for black win
int numberWhitePieces=numberWhitePiecesOnBoard(board);
//cout<<"Number of white pieces left = "<<numberWhitePieces<<endl;
 if(numberWhitePieces==0)
	{
	cout<<"Black wins..";
	wxString msg;
	msg<<"Black wins..";
    wxMessageBox(msg);
	event.Skip();
	return;
	}

if (playerFinished)
{
	//cout<<"Computer to move"<<endl;
	//statusText.clear();
	statusText="Computer calculating move ...";
	SetStatusText(statusText, 0);
	PaintNow();
	computerMove(board, WHITE);
	statusText.clear();
	statusText="Black (human) to move ...";
	SetStatusText(statusText, 0);
	PaintNow();	
}

//check for white (Computer) win
int numberBlackPieces = numberBlackPiecesOnBoard(board);
//cout<<"Number of black pieces left = "<<numberBlackPieces<<endl;
if(numberBlackPieces==0)
	{
	//cout<<"White wins..";
	wxString msg;
	msg<<"White wins..";
    wxMessageBox(msg);
	event.Skip();
	return;
	}
	
	PaintNow();
	event.Skip();
}