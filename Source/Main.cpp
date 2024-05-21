#include "MainWindow.h"



constexpr auto Window_Width		= 100;
constexpr auto Window_Height	= 100;
constexpr auto Pixel_Width		= 16;
constexpr auto Pixel_Height		= 16;



int main() {
	MainWindow& Window = MainWindow::GetInstance();
	if (Window.Construct(Window_Width, Window_Height, Pixel_Width, Pixel_Height))
		Window.Start();

	return 0;
}