#include "olcPixelGameEngine.h"
#include "QuatEngine.h"

   
int main()    
{
	V3DQEngine demo;
	if (demo.Construct(512, 240, 2, 2)) 
		demo.Start();
	return 0;     
} 

//#include "maths_tests.h"
// 
//int main() {
//	fast_functions_tests();
//
//	return 0;
//}