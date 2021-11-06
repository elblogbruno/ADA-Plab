// AssertsMaximFluxe.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#pragma once

#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>

// =============================================================================
// UTILITATS ===================================================================
// =============================================================================

extern ofstream LogOut; // Stream del fichero de log

void OpenLog();
void CloseLog();
void PrintLog(const char* Format, ...);