#pragma once
#include "../MainWindow.h"



class UIElement {
public:
	int x = 0, y = 0;			// Position on MainWindow in pixels
	int width = 1, height = 1;	// Size in pixels

	virtual void Render() {}

	// Check if mouse position is incide size box
	const bool IsMouseOver() const {
		olc::vi2d mousePos = Window.GetMousePos();
		return (mousePos.x >= x && mousePos.x <= x + width
			&& mousePos.y >= y && mousePos.y <= y + height);
	}

	static MainWindow& Window;
};
