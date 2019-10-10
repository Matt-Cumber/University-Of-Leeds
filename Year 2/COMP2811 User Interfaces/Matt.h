/*******************************************************************************
                        HEADER FILE FOR *****
*******************************************************************************/

#include <QObject>
#include <iostream>
#include <QLabel>
#include <QString>
#include <QSignalMapper>
#include "gitpp7.h"
#include "globals.h"

//class for my own slots
class CheckOutBranch : public QObject {

	Q_OBJECT

public:
	CheckOutBranch() : QObject() {}
	~CheckOutBranch() {};

public slots:

	//run when checkout button pressed
	void clicked(const QString &branch) {

    GITPP::REPO repo;

		//convert QSstring to an std::string
		std::string branchstd = branch.toLocal8Bit().constData();

		//Debug code
		// std::cout << "pressed\n";
		// std::cout << branchstd + "\n";

		//checkout to selected branch
    repo.checkout(branchstd);
	}

	//run when combo box updated to ensure signal mapper is up to date
	void myslot() {

		//remove previous mappings
		signalmapper->removeMappings(button);

		//recreate mapping with new label text
		signalmapper->setMapping(button,label->text());
	}
};
