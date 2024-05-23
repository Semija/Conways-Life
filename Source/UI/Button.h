#pragma once
#include "UIElement.h"
#include <functional>
#include "CellsWindow.h"



class Button : public UIElement {
public:
	bool pressed = 0;

	Button() {};
	Button(int X, int Y) {
		x = X; y = Y;
		width = 7; height = 7;
	}

	void Update(const std::function<void()> logicFunc) {
		logicFunc();
	}

	void Render(const std::function<void()> renderFunc) {
		renderFunc();
	}
};



class PauseButton : Button {
public:
	PauseButton(int X, int Y) {
		x = X; y = Y;
		width = 7; height = 7;
	}

	void Update(CellsWindow& CW1) {
		pressed = CW1.pause;
		if (Window.GetMouse(olc::Mouse::LEFT).bPressed && IsMouseOver()) {
			pressed = !pressed;
			CW1.pause = pressed;
		}
	}

	void Render() {
		Window.DrawLine(x, y, x + width, y, olc::WHITE);
		Window.DrawLine(x + width, y, x + width, y + height, olc::WHITE);
		Window.DrawLine(x + width, y + height, x, y + height, olc::WHITE);
		Window.DrawLine(x, y + height, x, y, olc::WHITE);
		Window.DrawLine(x + 2, y + 2, x + 2, y + height - 2, pressed ? olc::RED : olc::GREEN);
		Window.DrawLine(x + 5, y + 2, x + 5, y + height - 2, pressed ? olc::RED : olc::GREEN);
	}
};



class RuleButton : Button {
public:
	RuleButton(int X, int Y) {
		x = X; y = Y;
		width = 2; height = 2;
	}

	void Update(std::vector<bool>& Rules, int ruleNumber) {
		pressed = Rules[ruleNumber];
		if (Window.GetMouse(olc::Mouse::LEFT).bPressed && IsMouseOver()) {
			pressed = !pressed;
			Rules[ruleNumber] = !Rules[ruleNumber];
		}
	}

	void Render() {
		Window.Draw(x,	 y,		pressed ? olc::GREEN : olc::WHITE);
		Window.Draw(x,	 y+1,	pressed ? olc::GREEN : olc::WHITE);
		Window.Draw(x+1, y,		pressed ? olc::GREEN : olc::WHITE);
		Window.Draw(x+1, y+1,	pressed ? olc::GREEN : olc::WHITE);
	}
};