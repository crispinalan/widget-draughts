/***************************************************************************
 Author Alan Crispin aka. crispina                                    
    crispinalan@gmail.com         
 
   Copyright  2020  Alan Crispin

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
	// Create the main application window
	w = new MainWindow();
	// repaint on resize
	w->SetWindowStyle(w->GetWindowStyle() | wxFULL_REPAINT_ON_RESIZE);
	
	// Set the background to white
	//w->SetBackgroundColour(wxColour( 114, 104, 104));

	// Show it
	w->Show( true );

	 // Start the event loop
	 return true;
		
	//w = new MainWindow();
	//w->SetAutoLayout(true);
	//w->Show(true);

	//return true;
}