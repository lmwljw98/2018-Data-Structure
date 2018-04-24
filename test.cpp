#include <iostream>
#include <fstream>
using namespace std;
const int m = 1;
const int n = 6;


double array[m + 1][n + 1] = {};

int main()
{
  ifstream in;
  in.open("lab2-2.txt");

  string shape;
  int a, b;
  double base, height;
  double side1, side2;
  double radius;

  for (int i = 0; i < 7; i++)
  {
    in >> shape;
    if (shape == "triangle")
    {
      in >> a >> b;
      base = a;
      height = b;
      array[i][0] = base;
      array[i][1] = height;
      printf("triangle %f %f %f\n", array[i][0], array[i][1], (array[i][0] * array[i][1]) / 2);
      // cout << "triangle " << array[i][0] << " " << array[i][1] << " " << (array[i][0] * array[i][1]) / 2 << endl;
    }
    else if (shape == "rectangle")
    {
      in >> a >> b;
      side1 = a;
      side2 = b;
      array[i][0] = side1;
      array[i][1] = side2;
      printf("rectangle %f %f %f\n", array[i][0], array[i][1], (array[i][0] * array[i][1]));
      //cout << "rectangle " << array[i][0] << " " << array[i][1] << " " << (array[i][0] * array[i][1]) << endl;
    }
    else
    {
      in >> a;
      radius = a;
      array[i][0] = radius;
      printf("circle %f %f\n", array[i][0], (array[i][0] * array[i][0] * 3.14));
      //cout << "circle " << array[i][0] << "      " << (array[i][0] * array[i][0] * 3.14) <<  endl;
    }

  }
  return 0;

}
