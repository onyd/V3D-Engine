//Quaternion<float> p1(1.0f, -0.5f, -0.5f, -0.5f);
//Quaternion<float> p2(1.0f, 0.5f, -0.5f, -0.5f);
//Quaternion<float> p3(1.0f, -0.5f, 0.5f, -0.5f);
//Quaternion<float> p4(1.0f, -0.5f, -0.5f, 0.5f);
//Quaternion<float> p5(1.0f, 0.5f, 0.5f, -0.5f);
//Quaternion<float> p6(1.0f, -0.5f, 0.5f, 0.5f);
//Quaternion<float> p7(1.0f, 0.5f, -0.5f, 0.5f);
//Quaternion<float> p8(1.0f, 0.5f, 0.5f, 0.5f);
//
//
//QMesh m = vector<QTriangle>{
//
//	// SOUTH
//	{ p1,    p3,    p5 },
//	{ p1,    p5,    p2 },
//
//	// EAST                                                      
//	{ p2,    p5,    p8 },
//	{ p2,    p8,    p7 },
//
//	// NORTH                                                     
//	{ p7,    p8,    p6 },
//	{ p7,    p6,    p4 },
//
//	// WEST                                                      
//	{ p4,    p6,    p3 },
//	{ p4,    p3,    p1 },
//
//	// TOP                                                       
//	{ p3,    p6,    p8 },
//	{ p3,    p8,    p5 },
//
//	// BOTTOM                                                    
//	{ p7,    p4,    p1 },
//	{ p7,    p1,    p2 },
//
//};