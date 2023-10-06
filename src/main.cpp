#include <iostream>

#include "Node.h"
//#include "Insert.h" //Currently out of use in this build, unnecessary but recall if needed
#include "functions.cpp"

using namespace std;

int main() {
    BST call;
    call.masterFunction();

    /* call.insert("Brandon", 4567);
    call.insert("Brian", 3545);
    call.insert("Briana", 8787);
    call.insert("Bella", 9546);
    //call.insert("E", 9547);
    call.printInorder();
    call.remove(4567);
    call.removeInorder(2);
    call.printInorder(); */


    /*TO COPY FOR TESTING/INITIAL DEBUG
    8
    insert "Brandon" 45679999
    insert "Brian" 35459999
    insert "Briana" 87879999
    insert "Bella" 95469999
    printInorder
    remove 45679999
    removeInorder 2
    printInorder


    9
    insert "Brandon" 45679999
    insert "Brian" 35459999
    insert "Briana" 87879999
    insert "Bella" 95469999
    insert "Aaron" 47899999
    insert "Benson" 34549999
    insert "Beno" 89999999
    insert "Bert" 91019999
    insert "Bellern" 91019999

     */

    return 0;
}
