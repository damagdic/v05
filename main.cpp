#include <tchar.h>
#include "nwpwin.h"
#include <list>
#include <algorithm>

class main_window : public vsite::nwp::window
{
private:
	std::list<POINT> points;
protected:
	void on_paint(HDC hdc) override
	{
		if (points.empty()) return; // nothing to draw
		else {
			MoveToEx(hdc, points.front().x, points.front().y, NULL);
			for (POINT p : points)
			{
				LineTo(hdc, p.x, p.y); // draw line to each point
			}
			// TODO: iterate over points in container and draw polyline
		}
	}
	void on_left_button_down(POINT p) override
	{
		points.push_back(p); // add point to container
		InvalidateRect(*this, nullptr, true); // request repaint
	}
	// TODO: add point to container
	
	void on_key_down(int vk) override
	{
		switch (vk)
		{
		case VK_ESCAPE:
		{
			points.clear(); // clear container
			InvalidateRect(*this, nullptr, true); // request repaint
			break;
		}
		case VK_BACK:
		{
			if (!points.empty())
			{
				points.pop_back(); // remove last point
				InvalidateRect(*this, nullptr, true); // request repaint
			}
			break;
		}
		default:
			break;
		}

	// TODO: Esc - empty container
	// TODO: Backspace - remove last point
	}
	void on_destroy() override
	{
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 5");
	return app.run();
}
