#include <stdio.h>
#include <cs50.h>
int main()
{
    string name = get_string("What is your name?");  //get_string is created by CS50
    string location = get_string("What is your location?");
    printf("Hello,%s from %s!\n",name,location);
}