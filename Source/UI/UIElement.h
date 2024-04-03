#pragma once
#include "../Engine/olcPixelGameEngine.h"



class UIElement {
protected:
	int x = 0, y = 0; // Position in pixels
	int width = 1, height = 1; // Size

public:
	virtual ~UIElement() {}

	virtual void Render() {}
};