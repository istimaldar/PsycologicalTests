// PsycologicalTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Application.h"

using namespace PTests::Infrastructure;
using namespace std;

int main() {
	return Application::getInstance().run();
}