//Hasita Kode
//Dr. Steinberg
//COP 3223 Section 00343
//Small Program 1

#include <stdio.h>
#include <math.h>
	int main()
	{
		//Problem 1: Create a Big X Beginning
		printf("XX      XX\n");
		printf(" XX    XX\n");
		printf("  XX  XX\n");
		printf("   XXXX\n");
		printf("  XX  XX\n");
		printf(" XX    XX\n");
		printf("XX      XX\n");
		//Problem 1: Create a Big X Ending
		printf("********************************************\n");
		
		//Problem 2: Chicken Inventory Beginning
		
		//collect input from user for the number of eggs
		double chicken1, chicken2, chicken3, chicken4, chicken5;
		printf("Enter the amount of eggs laid for each of the 5 chickens.\n");
		printf("Chicken 1: ");
		scanf("%lf", &chicken1);
		printf("Chicken 2: ");
		scanf("%lf", &chicken2);
		printf("Chicken 3: ");
		scanf("%lf", &chicken3);
		printf("Chicken 4: ");
		scanf("%lf", &chicken4);
		printf("Chicken 5: ");
		scanf("%lf", &chicken5);
		
		//add up all the chicken eggs, and then use math library's remainder to find remainder and also divide to get the dozen. 
		int totalEggs = (int)(chicken1 + chicken2 + chicken3 + chicken4 + chicken5);
		int dozenEggs = totalEggs/12;
		int singleEggs = totalEggs%12;
		
		printf("There are %d dozen(s) and %d egg(s) total.\n", dozenEggs, singleEggs);
		//Problem 2: Chicken Inventory Ending
		printf("********************************************\n");
		
		//Problem 3: Physics Kinematic Equation Beginning
		
		double velocity, time, acceleration;
		
		//collect values for velocity, time, and acceleration
		printf("Let's calculate the distance traveled for some motor vehicle.\n");
		printf("I will need some information to collect from you.\n");
		printf("Enter the initial velocity: ");
		scanf("%lf", &velocity);
		printf("Enter the time: ");
		scanf("%lf", &time);
		printf("Enter the acceleration: ");
		scanf("%lf", &acceleration);
		
		
		//start to use the variables to create the formula
		double finalDistance = (velocity * time) + (time * time * acceleration * 0.5);
		
		printf("The distance traveled for the motor vehicle was %.3lf meters.\n", finalDistance);
		//Problem 3: Physics Kinematic Equation Ending
		printf("********************************************\n");
		
		//Problem 4: 2D Train Drawing Beginning
		
		double radius;  
		double baseNoWindow1, heightNoWindow1, baseNoWindow2, heightNoWindow2, baseWindowRectangle, heightWindowRectangle, lengthWindowSqr;
		double baseTriangle1, heightTriangle1, baseTriangle2, heightTriangle2, baseTriangle3, heightTriangle3;
		//Shape: Circle
		
		printf("Let's calculate the area of the 2D train.\n");
		printf("Let's start with the 5 circles.\n");
		printf("Enter the radius: ");
		scanf("%lf", &radius);
		double circleArea = 5 * (3.14159 * radius * radius);
		
		
		printf("Now let's get the info on the three rectangles.\n");
		//Shape: No Window Rectangle 1
		printf("Let's start with the rectangle with no window.\n");
		printf("Enter the base: ");
		scanf("%lf", &baseNoWindow1);
		printf("Enter the height: ");
		scanf("%lf", &heightNoWindow1);
		double noWindow1Area = baseNoWindow1 * heightNoWindow1;		
		
		//Shape: No Window Rectangle 2
		printf("Let's now get the other rectangle with no window.\n");
		printf("Enter the base: ");
		scanf("%lf", &baseNoWindow2);
		printf("Enter the height: ");
		scanf("%lf", &heightNoWindow2);
		double noWindow2Area = baseNoWindow2 * heightNoWindow2;
		
		//Shape: Window Rectangle
		printf("Let's now get the last rectangle with the opening space.\n");
		printf("Enter the base: ");
		scanf("%lf", &baseWindowRectangle);
		printf("Enter the height: ");
		scanf("%lf", &heightWindowRectangle);
		double noGapWindowArea = baseWindowRectangle * heightWindowRectangle;
		
		printf("Enter the length of the window: ");
		scanf("%lf", &lengthWindowSqr);
		double windowGapArea = lengthWindowSqr * lengthWindowSqr;
		
		double windowArea = noGapWindowArea - windowGapArea;
		
		//Shape: 3 Triangles		
		printf("Now let's get the info on the three triangles.\n");
		
		//Shape: Triangle 1
		printf("Enter the base for triangle 1: ");
		scanf("%lf", &baseTriangle1);
		printf("Enter the height for triangle 1: ");
		scanf("%lf", &heightTriangle1);
		double areaTriangle1 = (baseTriangle1 * heightTriangle1) / 2;
		//Shape: Triangle 2
		printf("Enter the base for triangle 2: ");
		scanf("%lf", &baseTriangle2);		
		printf("Enter the height for triangle 2: ");
		scanf("%lf", &heightTriangle2);
		double areaTriangle2 = (baseTriangle2 * heightTriangle2) / 2;
		//Shape: Triangle 3
		printf("Enter the base for triangle 3: ");
		scanf("%lf", &baseTriangle3);	
		printf("Enter the height for triangle 3: ");
		scanf("%lf", &heightTriangle3);
		double areaTriangle3 = (baseTriangle3 * heightTriangle3) / 2;
		
		double totalTrainArea = circleArea + noWindow1Area + noWindow2Area + windowArea + areaTriangle1 + areaTriangle2 + areaTriangle3;
		
		printf("The area of the 2D train is %.5lf units.", totalTrainArea);
		
		return 0;
	}