/*******************************************************************************
                        MAIN FILE FOR *****
*******************************************************************************/

#include "globals.h"
#include "gitpp.h"
#include "ll16m23c.h"
#pragma once

#include <QLabel>
#include <QHBoxLayout>
#include <QComboBox>
#include <QString>
#include <QPushButton>
#include <QSignalMapper>
#include <QLabel>
#include <QMessageBox>

#include <sstream>

namespace{

class HelloWorldLabel : public QWidget{

public:
	HelloWorldLabel() : QWidget(){

		// set object name for styling
		setObjectName("label");
		//create a new layout
		QVBoxLayout* v=new QVBoxLayout;

		//init variables
		GITPP::REPO repo;
		std::ostringstream branches_stream;
		std::string branches;
		std::string out_branches; // string to print out branches in a label

		//Get all branches
		for(GITPP::BRANCH i : repo.branches()) {
			branches_stream << i;
			branches =  branches_stream.str();

			//add new line to split up later
			branches_stream << "\n";
		}

		//Init Combo Box
		QComboBox *combo = new QComboBox(this);
		combo->setObjectName("label");

		//init variables to split branches up
		std::istringstream ibranch(branches);
		std::string token;
		int i = 1;

		//Add each branch as a new item in combo box
		while(std::getline(ibranch,token, '\n')){
			combo->addItem(QString::fromStdString(token));
			out_branches += "	" + std::to_string(i) + ". " + token + "\n";
			++i;
		}

		//create the instance of button
		button = new QPushButton("Checkout",this);

		//create the instance of label
		label = new QLabel("*Chosen branch shown here*", this);
		label->setObjectName("label");

		//create instance of CheckOutBranch
		checkoutbranch = new CheckOutBranch();

		//create instance of signalmap
		signalmapper = new QSignalMapper(checkoutbranch);

		//add all widgets to layout in order
		v->addWidget(new QLabel("These are the found branches :\n"));
		v->addWidget(new QLabel(QString::fromStdString(out_branches)));
		v->addWidget(new QLabel("Chosen branch to checkout too:"));
		v->addWidget(label);
		v->addWidget(new QLabel()); // space label
		v->addWidget(new QLabel("Choose a branch to change into"));
		v->addWidget(combo);
		v->addWidget(button);
		v->addWidget(label);

		setLayout(v);

/*******************************************************************************
                CODE FOR ALL CONNECTIONS AND SIGNAL MAPPING
*******************************************************************************/

		//connect combo box and label so label changes when the combo box changes
		QObject::connect(combo, SIGNAL(activated(QString)), label,
			SLOT(setText(QString)));

		//connect combo box and checkoutbranch so myslot is run on activation
		QObject::connect(combo, SIGNAL(activated(QString)), checkoutbranch,
			SLOT(myslot()));

		//connect signal mapper to button on click
		QObject::connect(button, SIGNAL(clicked()), signalmapper,
			SLOT(map()));

		// init signalmapper to button
		signalmapper->setMapping(button,label->text());

		//finalise signalmap to run my slot "clicked" when button clicked
		QObject::connect(signalmapper, SIGNAL(mapped(QString)), checkoutbranch,
			SLOT(clicked(QString)));

		//connect button with success message
		QObject::connect(button, &QPushButton::clicked, [this](){
			success();
		});
	}

	//function to show message to user
	void success(){
		QMessageBox *msg = new QMessageBox();
		msg->setText("switched to " + label->text());
		msg->exec();
	}
};

INSTALL_TAB(HelloWorldLabel, "Branch Navigation");

}
