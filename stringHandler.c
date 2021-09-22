/* Filename        file.c
 * Date            02/13/21
 * Author          Preston Glenn
 * Email           ptg170030@utdallas.edu
 * Course          CS 3377.0W6 Spring 2021
 * Version         1.0
 * Copyright       2021, All Rights Reserved
 *
 * Description
 *   Provides function to convert a string to boolean values and vice versa.
 *
 */

#include <iostream>

using namespace std;

string booleanToString(bool val){
  return val ? "true" : "false";
}

bool stringToBoolean(string val){
  return val == "true";
}
