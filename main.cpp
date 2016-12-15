#include <QCoreApplication>
#include "answersobjects.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Teramind::compareScalar();
    // Teramind::stackOverflow();
    // Teramind::segmentationFault();
    // Teramind::memoryLeaks();
    // Teramind::loopedLinkedList();
    Teramind::fiboPrint(20);
    Teramind::reversePrint("The reversed string");
    Teramind::functionalStyle();

    return a.exec();
}
