#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT;
			case ITM_Circ: return DRAW_ELLIPSE;
			case ITM_Line: return DRAW_LINE;
			case ITM_Rhombus: return DRAW_RHOMBUS;
			case ITM_Tri: return DRAW_TRI;
			case ITM_Save:return SAVE;
			case ITM_SAVE_TYPE : return SAVE_TYPE;
			case ITM_BRING_BACK:return BRING_BACK;
			case ITM_BRING_FRONT:return BRING_FRONT;
			case ITM_RESIZE :return RESIZE;
			case ITM_SOUND : return SOUND;
			case ITM_Del:return DEL;
			case ITM_Load:return LOAD;
			case ITM_Color:return CHNG_FILL_CLR;
			case ITM_Select:return SELECT;
			case ITM_EXIT: return EXIT;
			case ITM_Play:return TO_PLAY;
			case ITM_Copy:return COPY;
			case ITM_Cut:return CUT;
			case ITM_Paste:return PASTE;
			case ITM_DrawColor:return CHNG_DRAW_CLR;
		

			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			 return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
		//GUI is in PLAY mode
		
else if(UI.InterfaceMode == MODE_PLAY)
	{
		
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_DRAWMODE:return TO_DRAW;
			case ITM_CLOSE :return EXIT;
			case ITM_PICK:return PICK;
			case ITM_PICK_COLOR : return PICK_COLOR;


			default: return EMPTY;}}
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
		
			 return DRAWING_AREA;	
		}

		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}	

else if(UI.InterfaceMode == MODE_COLOR) {
	
	if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
            case ITM_BLACK : return C_BLACK;
            case ITM_BLUE : return C_BLUE;
			case ITM_RED : return C_RED;
			case ITM_GREEN : return C_GREEN;
			case ITM_WHITE : return C_WHITE;
				default: return EMPTY;}
			if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
		
			 return DRAWING_AREA;	
		}
/////////////////////////////////
	}
}
else{
UI.InterfaceMode = MODE_DRAWCOLOR;
if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
            case ITM_BLACK2 : return C_BLACK2;
            case ITM_BLUE2 : return C_BLUE2;
			case ITM_RED2 : return C_RED2;
			case ITM_GREEN2 : return C_GREEN2;
			case ITM_WHITE2 : return C_WHITE2;
				default: return EMPTY;}
			if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
		
			 return DRAWING_AREA;	
		}

}
}	}
Input::~Input()
{
}
