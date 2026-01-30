// Hasita Kode
// Dr. Steinberg
// COP 3223 Section 00343
// Small Program 2
#include <stdio.h>
#include <math.h>


double calcHypotenuse(double a, double b);
void rentalPrices();
void timeDisplay(int seconds);
double mathFunction(int n);

int main()
{	
    // Problem 1
	//declare the variables and use scan f to get them from the user
    double a, b;
    printf("Enter the value for a: ");
    scanf("%lf", &a);
    printf("Enter the value for b: ");
    scanf("%lf", &b);

    double hypotenuse = calcHypotenuse(a, b);
    printf("If a = %.3lf and b = %.3lf, then that means the hypotenuse is %.3lf.\n",
           a, b, hypotenuse);

    // Problem 2
    rentalPrices();

    // Problem 3
	//declare variable
    int seconds;
	//use print statement and use scanner to get seconds
    printf("Enter the seconds: ");
    scanf("%d", &seconds);
	//call the function
    timeDisplay(seconds);

    // Problem 4
	//declare n and get input of n from the user
    int n;
    printf("Enter the value for n: ");
    scanf("%d", &n);
	//display the result
    double result = mathFunction(n);
    printf("The function computes the value %.3lf.\n", result);

    return 0;
}


double calcHypotenuse(double a, double b)
{
	//take the square root of a squared and b squared
    double hypotenuse = sqrt(a * a + b * b);
	//return the hypotenuse value back to the main function
    return hypotenuse;
}

// Problem 2
void rentalPrices()
{	
	//declare the variables and assign the cars per day values
    int days;
    double tesla = 46.48;
    double chevrolet = 49.53;
    double nissan = 50.72;
	
	//print statement paragraph
    printf("Hello Luis!\n");
    printf("Thank you for considering Hertz for your car rental needs.\n");
    printf("You have asked to compare prices for three vehicles.\n");
	
	//get value of days from the user
    printf("Please enter the number of days you plan to rent the vehicle: ");
    scanf("%d", &days);
    printf("Here are the prices excluding tax.\n");
	
	//multiply the per day value by the amount of days inputted by the user
    double finalTesla = tesla * days;
    double finalChevrolet = chevrolet * days;
    double finalNissan = nissan * days;
	
	//print the results
    printf("Tesla Model 3 Standard Range: $%.2lf\n", finalTesla);
    printf("Chevrolet Malibu: $%.2lf\n", finalChevrolet);
    printf("Nissan Rogue: $%.2lf\n", finalNissan);
}

// Problem 3
void timeDisplay(int seconds)
{
	
    int hours = seconds / 3600;
	
	//use modulus to find the remainder of the hours to get minutes
    int remainderHours = seconds % 3600;
    int minutes = remainderHours / 60;
	
	//now get remainder of remainder of hours and 60 (1 min = 60 sec)
    int finalSeconds = remainderHours % 60;

    printf("%d seconds is %d hours, %d minutes, and %d seconds.\n",
           seconds, hours, minutes, finalSeconds);
}

// Problem 4
double mathFunction(int n)
{
	//Split into numerator and denominator
    double numerator = pow(n, n) - pow(2, n);
	
	//Split denominator into denomNumerator and denomDenominator
    double denomNumerator = sqrt(n) * pow(n, 4);
    double denomDenominator = exp(n - 2) + 9;
    double denominator = denomNumerator / denomDenominator;
	
	//combine them
    double result = (numerator / denominator) - (8 * n);
    return result;
}
