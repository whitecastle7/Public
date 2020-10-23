
#include <console.h>
#include "ShapeOptimizer.h"

using namespace std;
using namespace windows_console;



int main()
{
	ShapeOptimizer so;
	so.run();


	return 0;
}



//void example()
//{
//
//	csl << key_events::add_filter<key_filter_up>;
//
//	csl << window::title("B52")
//		<< window::fit(300, 200, "Consolas", font::size_type{ 3 }, font::ratio_type{ 1.0 })
//		<< window::unclosable
//		<< window::unresizable
//		<< window::center
//		<< cursor::invisible;
//
//	image img;
//	// pen couleur le contour
//	img << pen(dot, text_color(bright, red), background_color(dark, red))
//		<< point(100, 100)
//		// brush couleur lìntérieur
//		<< brush(dot, text_color(dark, blue), background_color(bright, blue))
//		<< rectangle(50, 105, 120, 120)
//		<< circle(50, 150, 10)
//		<< no_brush
//		<< pen(dot, text_color(bright, blue), background_color(dark, blue))
//		<< circle(150, 130, 10)
//		<< pen(dot, text_color(dark, yellow), background_color(dark, red))
//		<< line(10, 10, 150, 50);
//
//	// L'insertion d'une image est lourde, il faut donc le faire le moins souvent
//	csl << img;
//
//	image img2;
//	img2 << fill;
//
//	console_events ce;
//
//	while (true)
//	{
//		ce.read_events();
//		while (ce.key_events_count())
//		{
//			switch (ce.next_key_event().ascii_value())
//			{
//			case 27:
//				break;
//			case ' ':
//				csl << img2;
//				break;
//			case 'a':
//			case 'A':
//				csl << img;
//				break;
//			}
//		}
//	}
//
//}