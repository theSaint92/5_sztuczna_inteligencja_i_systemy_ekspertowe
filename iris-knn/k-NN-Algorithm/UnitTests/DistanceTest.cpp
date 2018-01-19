#include "stdafx.h"
#include "CppUnitTest.h"
#include <cmath>

#include "../k-NN-Algorithm/Distance.h"
#include "../k-NN-Algorithm/EuclideanDistance.h"
#include "../k-NN-Algorithm/EuclideanSquaredDistance.h"
#include "../k-NN-Algorithm/ManhattanDistance.h"
#include "../k-NN-Algorithm/ChebyshevDistance.h"
#include "../k-NN-Algorithm/MinkowskiDistance.h"

//Czemu muszê to (Inline funckji)?
#include "../k-NN-Algorithm/EuclideanDistance.cpp"
#include "../k-NN-Algorithm/EuclideanSquaredDistance.cpp"
#include "../k-NN-Algorithm/ManhattanDistance.cpp"
#include "../k-NN-Algorithm/ChebyshevDistance.cpp"
#include "../k-NN-Algorithm/MinkowskiDistance.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(DistanceTest)
	{
	public:
		
		TEST_METHOD(EuclideanDistanceTest)
		{
			EuclideanDistance d;
			double result;
			double expected;
			double epsilon = 0.01;

			//Try block
			double v1[2]{ 0,0 };
			double v2[2]{ 0,1 };
			result = d.dist(2, v1, v2);
			expected = 1.0;
			Assert::IsTrue(result-expected < epsilon);

			//Try block
			double v3[2]{ 0,0 };
			double v4[2]{ 1,1 };
			result = d.dist(2, v3, v4);
			expected = 1.41421356237; //sqrt(2)
			Assert::IsTrue(result - expected < epsilon);

			//Try block
			double v5[3]{ 0,0,0 };
			double v6[3]{ 1,1,1 };
			result = d.dist(3, v5, v6);
			expected = 1.73205080757; //sqrt(3)
			Assert::IsTrue(result - expected < epsilon);
		}

		TEST_METHOD(EuclideanSquaredDistanceTest)
		{
			EuclideanSquaredDistance d;
			double result;
			double expected;
			double epsilon = 0.01;

			//Try block
			double v1[2]{ 0,0 };
			double v2[2]{ 0,1 };
			result = d.dist(2, v1, v2);
			expected = 1.0;
			Assert::IsTrue(result - expected < epsilon);

			//Try block
			double v3[2]{ 0,0 };
			double v4[2]{ 1,2 };
			result = d.dist(2, v3, v4);
			expected = 5; 
			Assert::IsTrue(result - expected < epsilon);

			//Try block
			double v5[3]{ 0,0,0 };
			double v6[3]{ 1,1,1 };
			result = d.dist(3, v5, v6);
			expected = 3; 
			Assert::IsTrue(result - expected < epsilon);
		}

		TEST_METHOD(ManhattanDistanceTest)
		{
			ManhattanDistance d;
			double result;
			double expected;
			double epsilon = 0.01;

			//Try block
			double v1[2]{ 0,0 };
			double v2[2]{ 0,1 };
			result = d.dist(2, v1, v2);
			expected = 1.0;
			Assert::IsTrue(result - expected < epsilon);

			//Try block
			double v3[2]{ 0,0 };
			double v4[2]{ 1,1 };
			result = d.dist(2, v3, v4);
			expected = 2;
			Assert::IsTrue(result - expected < epsilon);

			//Try block
			double v5[3]{ 0,0,0 };
			double v6[3]{ 1,1,1 };
			result = d.dist(3, v5, v6);
			expected = 3; 
			Assert::IsTrue(result - expected < epsilon);

		}

		TEST_METHOD(ChebyshevDistanceTest)
		{
			ChebyshevDistance d;
			double result;
			double expected;
			double epsilon = 0.01;

			//Try block
			double v1[2]{ 0,0 };
			double v2[2]{ 0,1 };
			result = d.dist(2, v1, v2);
			expected = 1.0;
			Assert::IsTrue(result - expected < epsilon);

			//Try block
			double v3[2]{ 0,0 };
			double v4[2]{ 1,1 };
			result = d.dist(2, v3, v4);
			expected = 1;
			Assert::IsTrue(result - expected < epsilon);

			//Try block
			double v5[3]{ 0,0,0 };
			double v6[3]{ 1,5,1 };
			result = d.dist(3, v5, v6);
			expected = 5;
			Assert::IsTrue(result - expected < epsilon);

		}

		TEST_METHOD(MinkowskiDistanceTest)
		{
			MinkowskiDistance d;
			double result;
			double expected;
			double epsilon = 0.01;

			//Try block
			d.p = 2; //Wynik jak euklidesowa
			double v1[2]{ 0,0 };
			double v2[2]{ 1,1 };
			result = d.dist(2, v1, v2);
			expected = 1.41421356237; //sqrt(2)
			Assert::IsTrue(result - expected < epsilon);

			//Try block
			d.p = 1; //Wynik jak manhattan
			double v3[2]{ 0,0 };
			double v4[2]{ 1,1 };
			result = d.dist(2, v3, v4);
			expected = 2;
			Assert::IsTrue(result - expected < epsilon);

			//Try block
			d.p = 2;
			double v5[3]{ 0,0,0 };
			double v6[3]{ 1,1,1 };
			result = d.dist(3, v5, v6);
			expected = 1.73205080757; //sqrt(3)
			Assert::IsTrue(result - expected < epsilon);

			//Try block
			d.p = 0.5; //Wynik jak manhattan
			double v7[2]{ 0,0 };
			double v8[2]{ 1,1 };
			result = d.dist(2, v7, v8);
			expected = 4;
			Assert::IsTrue(result - expected < epsilon);
		}


	};
}