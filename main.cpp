#include "term_project.h"

int main() 
{
    dataSet myDataSet;
    myDataSet.import_and_save();
    myDataSet.printSaved();
    
    return 0;
}
