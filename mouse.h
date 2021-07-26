

class cMouse
{
public:
	void Update(int width, int height);
	bool LeftClick(int x,int y,int w,int h);
	bool OneLeftClick(int x,int y,int w,int h);
	bool IsOver(int x,int y,int w,int h);

	void Drag(bool& bDrag, bool bCheck, bool bDragCheck,int& x, int& y, int& xdif, int& ydif);

	void GetMousePosition(int &posx, int &posy)
	{
		posx = mouse_x;
		posy = mouse_y;
	}

	bool HasMouseOneJustBeenReleased()
	{
		return mouse1released;
	}

	bool IsMouseTwoBeingHeld()
	{
		return mouse2pressed;
	}

	bool bDragged[3];
	int iDiffX[3];
	int iDiffY[3];

	int mouse_x, mouse_y;
private:
	bool mouse1pressed;
	bool mouse1released;
	bool mouse2pressed;
	bool mouse2released;
};

extern cMouse g_Mouse;
